/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	Created by Norbert Gerberg.
======================================================*/
#include "NetClient.hpp"
#include "BigError.hpp"
#include <ws2tcpip.h>

using namespace GameEngine;

void NetClient::Initialize(uint16 port, strgv ip)
{
	mPort	= port;
	mIP		= ip;

	if (mSocket == INVALID_SOCKET)
		throw BigError("Failed creating client socket: " + std::to_string(WSAGetLastError()));

	ulong nb = 1;
	ioctlsocket(mSocket, FIONBIO, &nb); // set non-blocking

	mService.sin_family = AF_INET;
	InetPton(AF_INET, ip.data(), &mService.sin_addr.s_addr);
	mService.sin_port = htons(port);
}

void NetClient::Release()
{
	closesocket(mSocket);
}
