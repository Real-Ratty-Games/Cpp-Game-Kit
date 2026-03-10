/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	Created by Norbert Gerberg.
======================================================*/
#include "NetServer.hpp"
#include "BigError.hpp"
#include <ws2tcpip.h>

using namespace GameEngine;

void NetServer::Initialize(uint16 port, strgv ip)
{
	mPort	= port;
	mIP		= ip;

	if (mSocket == INVALID_SOCKET)
		throw BigError("Failed creating server socket: " + std::to_string(WSAGetLastError()));

	ulong nb = 1;
	ioctlsocket(mSocket, FIONBIO, &nb); // set non-blocking

	sockaddr_in service;
	service.sin_family = AF_INET;
	InetPton(AF_INET, ip.data(), &service.sin_addr.s_addr);
	service.sin_port = htons(port);
	if (bind(mSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR)
		throw BigError("Failed binding server: " + std::to_string(WSAGetLastError()));
}
