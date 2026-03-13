/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	Created by Norbert Gerberg.
======================================================*/
#ifndef NETWORK_HPP_
#define NETWORK_HPP_
#include "SystemTypes.hpp"
#include "NetData.hpp"

namespace GameEngine::Network
{
	void Initialize();
	void Release();

    void SetSocketNB(NetSocket& socket);
    void CloseSocket(NetSocket& socket);
    int GetError();

    void Pton(sockaddr_in& service, strgv ip);
}
#endif
