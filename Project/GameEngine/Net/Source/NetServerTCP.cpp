/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	Created by Norbert Gerberg.
======================================================*/
#include "NetServerTCP.hpp"
#include "BigError.hpp"
#include <algorithm>
#include <ranges>
#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#endif

using namespace GameEngine;

// 55555, "127.0.0.1"
void NetServerTCP::Initialize(uint16 port, strgv ip)
{
#if _WIN32
    mSocket = INVALID_SOCKET;
#else
	mSocket = -1;
#endif
	mSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	NetServer::Initialize(port, ip);
#if _WIN32
    if (listen(mSocket, SOMAXCONN) == SOCKET_ERROR)
#else
	if (listen(mSocket, SOMAXCONN) == -1)
#endif
#if _WIN32
		throw BigError("Failed to listen server: " + std::to_string(WSAGetLastError()));
#else
		throw BigError("Failed to listen server: " + std::to_string(errno));
#endif
}

void NetServerTCP::Release()
{
	for (auto& client : mClients)
		Disconnect(client);
	mClients.clear();
	
#if _WIN32
	closesocket(mSocket);
#else
	close(mSocket);
#endif
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

    NetSocket client = accept(mSocket, (sockaddr*)&clientAddr, &clientLen);
    
#if _WIN32
    if (client == INVALID_SOCKET)
        return WSAGetLastError();
#else
    if (client == -1)
        return errno;
#endif

	char ip[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &clientAddr.sin_addr, ip, sizeof(ip));

	const uint16 cport = ntohs(clientAddr.sin_port);

	if (!std::ranges::any_of(mClients, [=](const NetClientDataTCP& c) {
		return (c.IP == ip) && (c.Port == cport);
		}))
	{
		ulong nb = 1;
#if _WIN32
		ioctlsocket(client, FIONBIO, &nb); // set non-blocking
#else
        ioctl(mSocket, FIONBIO, &nb);
#endif
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
#if _WIN32
			else if (code == GAMEENGINE_NET_TCP_NOTHING && WSAGetLastError() == WSAECONNRESET)
#else
			else if (code == GAMEENGINE_NET_TCP_NOTHING && errno == ENETRESET)
#endif
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
#if _WIN32
    closesocket(client.Socket);
#else
    close(client.Socket);
#endif
}
