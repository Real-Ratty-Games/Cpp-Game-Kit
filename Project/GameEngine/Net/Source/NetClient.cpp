/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	Created by Norbert Gerberg.
======================================================*/
#include "NetClient.hpp"
#include "BigError.hpp"
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

void NetClient::Initialize(uint16 port, strgv ip)
{
	mPort	= port;
	mIP		= ip;

#if _WIN32
    if (mSocket == INVALID_SOCKET)
		throw BigError("Failed creating client socket: " + std::to_string(WSAGetLastError()));
#else
    if (mSocket == -1)
		throw BigError("Failed creating client socket: " + std::to_string(errno));
#endif

	ulong nb = 1;
#if _WIN32
	ioctlsocket(mSocket, FIONBIO, &nb); // set non-blocking
#else
    ioctl(mSocket, FIONBIO, &nb);
#endif

	mService.sin_family = AF_INET;
#if _WIN32
    InetPton(AF_INET, ip.data(), &mService.sin_addr.s_addr);
#else
	inet_pton(AF_INET, ip.data(), &mService.sin_addr.s_addr);
#endif
	mService.sin_port = htons(port);
}

void NetClient::Release()
{
#if _WIN32
	closesocket(mSocket);
#else
	close(mSocket);
#endif
}
