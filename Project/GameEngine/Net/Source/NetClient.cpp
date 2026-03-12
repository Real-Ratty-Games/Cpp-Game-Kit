/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	Created by Norbert Gerberg.
======================================================*/
#include "NetClient.hpp"
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

void NetClient::Initialize(uint16 port, strgv ip)
{
    mPort    = port;
    mIP        = ip;

    if (mSocket == GAMEENGINE_NET_SOCKET_INVALID)
        throw BigError("Failed creating client socket: " + std::to_string(Network::GetError()));
    
    Network::SetSocketNB(mSocket);
    Network::InetPton(mService, ip);

    mService.sin_family = AF_INET;
    mService.sin_port = htons(port);
}

void NetClient::Release()
{
    Network::CloseSocket(mSocket);
}
