/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	Created by Norbert Gerberg.
======================================================*/
#include "Network.hpp"
#include "SystemTypes.hpp"
#include "BigError.hpp"
#include <WinSock2.h>

#pragma comment(lib, "Ws2_32.lib")

using namespace GameEngine;

void Network::Initialize()
{
	WSADATA wsadata;
	int		wsaerr;

	uint16 vreq = MAKEWORD(2, 2);
	wsaerr = WSAStartup(vreq, &wsadata);
	if (wsaerr != 0)
		throw BigError("Error: Winsock DLL not found!");
}

void Network::Release()
{
	WSACleanup();
}
