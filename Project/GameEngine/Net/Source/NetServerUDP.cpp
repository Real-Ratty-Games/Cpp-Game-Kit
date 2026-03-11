/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	Created by Norbert Gerberg.
======================================================*/
#include "NetServerUDP.hpp"
#include "BigError.hpp"
#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#endif

using namespace GameEngine;

void NetServerUDP::Initialize(uint16 port, strgv ip)
{
#if _WIN32
    mSocket = INVALID_SOCKET;
#else
	mSocket = -1;
#endif
	mSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	NetServer::Initialize(port, ip);
}

void NetServerUDP::Release()
{
#if _WIN32
	closesocket(mSocket);
#else
	close(mSocket);
#endif
}

int NetServerUDP::Run()
{
	return ListenToClient();
}

int NetServerUDP::Recv(NetClientDataUDP& client, char* buffer, int size, int flags)
{
	sockaddr_in clientAddr;
	socklen_t	clientLen = sizeof(clientAddr);

#if _WIN32
    int bytes = recvfrom(mSocket, buffer, size, flags, (SOCKADDR*)&clientAddr, &clientLen);
#else
    int bytes = recvfrom(mSocket, buffer, size, flags, (sockaddr*)&clientAddr, &clientLen);
#endif

#if _WIN32
    if (bytes == SOCKET_ERROR)
#else
	if (bytes == -1)
#endif
		return GAMEENGINE_NET_UDP_NOTHING; // return WSAGetLastError()

	char ip[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &clientAddr.sin_addr, ip, sizeof(ip));

	const uint16 cport = ntohs(clientAddr.sin_port);

	client.IP			= ip;
	client.Port			= cport;
	client.SocketAddr	= clientAddr;
	client.SocketLen	= clientLen;

	return bytes;
}

int NetServerUDP::Send(const NetClientDataUDP& client, const char* buffer, int size, int flags)
{
#if _WIN32
    return sendto(mSocket, buffer, size, flags, (SOCKADDR*)&client.SocketAddr, client.SocketLen);
#else
    return sendto(mSocket, buffer, size, flags, (sockaddr*)&client.SocketAddr, client.SocketLen);
#endif
}
