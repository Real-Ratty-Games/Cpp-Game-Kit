/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	Created by Norbert Gerberg.
======================================================*/
#include "NetServer.hpp"
#include "BigError.hpp"
#include "Network.hpp"
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

void NetServer::Initialize(uint16 port, strgv ip)
{
	mPort	= port;
	mIP		= ip;

    if (mSocket == GAMEENGINE_NET_SOCKET_INVALID)
		throw BigError("Failed creating server socket: " + std::to_string(Network::GetError()));
    
    Network::SetSocketNB(mSocket);
    
	sockaddr_in service;
	service.sin_family = AF_INET;
    service.sin_port = htons(port);
    
    Network::InetPton(service, ip);

    if (bind(mSocket, (NetSockaddr*)&service, sizeof(service)) == GAMEENGINE_NET_SOCKET_INVALID)
		throw BigError("Failed binding server: " + std::to_string(Network::GetError()));
}
