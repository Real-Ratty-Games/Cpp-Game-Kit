/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	Created by Norbert Gerberg.
======================================================*/
#include "NetServerTCP.hpp"
#include "BigError.hpp"
#include <algorithm>
#include <ranges>
#include <ws2tcpip.h>

using namespace GameEngine;

// 55555, "127.0.0.1"
void NetServerTCP::Initialize(uint16 port, strgv ip)
{
	mSocket = INVALID_SOCKET;
	mSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	NetServer::Initialize(port, ip);
	if (listen(mSocket, SOMAXCONN) == SOCKET_ERROR)
		throw BigError("Failed to listen server: " + std::to_string(WSAGetLastError()));
}

void NetServerTCP::Release()
{
	for (auto& client : mClients)
		Disconnect(client);
	closesocket(mSocket);
}

int NetServerTCP::Run()
{
	int code = Connect();
	code = Listen();
	return code;
}

const std::vector<NetClientDataTCP>& NetServerTCP::Clients()
{
	return mClients;
}

int NetServerTCP::Connect()
{
	sockaddr_in clientAddr;
	socklen_t	clientLen = sizeof(clientAddr);

	SOCKET client = accept(mSocket, (sockaddr*)&clientAddr, &clientLen);
	if (client == INVALID_SOCKET)
		return WSAGetLastError();

	char ip[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &clientAddr.sin_addr, ip, sizeof(ip));

	const uint16 cport = ntohs(clientAddr.sin_port);

	if (!std::ranges::any_of(mClients, [=](const NetClientDataTCP& c) {
		return (c.IP == ip) && (c.Port == cport);
		}))
	{
		ulong nb = 1;
		ioctlsocket(client, FIONBIO, &nb); // set non-blocking
		mClients.push_back({ client, cport, ip });
	}
	return GAMEENGINE_NET_TCP_NOTHING;
}

int NetServerTCP::Listen()
{
	int code = 0;
	std::erase_if(mClients, [&](auto& client)
		{
			bool remv = false;
			code = ListenToClient(client);
			if (code == GAMEENGINE_NET_TCP_DISCONNECTED) remv = true;
			else if (code == GAMEENGINE_NET_TCP_NOTHING && WSAGetLastError() == WSAECONNRESET)
				remv = true;

			if (remv) Disconnect(client);
			return remv;
		});
	return code;
}

int NetServerTCP::Recv(const NetClientDataTCP& client, char* buffer, int size, int flags)
{
	return recv(client.Socket, buffer, size, flags);
}

int NetServerTCP::Send(const NetClientDataTCP& client, const char* buffer, int size, int flags)
{
	return send(client.Socket, buffer, size, flags);
}

void NetServerTCP::Disconnect(const NetClientDataTCP& client)
{
	closesocket(client.Socket);
}
