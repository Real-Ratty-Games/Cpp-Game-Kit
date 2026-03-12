/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	Created by Norbert Gerberg.
======================================================*/
#ifndef NETWORK_HPP_
#define NETWORK_HPP_
#include "SystemTypes.hpp"
#include "NetData.hpp"
#ifdef _WIN32
#include <winsock2.h>
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif

namespace GameEngine::Network
{
	void Initialize();
	void Release();

    void SetSocketNB(NetSocket& socket);
    void CloseSocket(NetSocket& socket);
    int GetError();

    void InetPton(sockaddr_in& service, strgv ip);
}
#endif
