/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	Created by Norbert Gerberg.
======================================================*/
#ifndef NETDATA_HPP_
#define NETDATA_HPP_
#include <WinSock2.h>
#include <ws2tcpip.h>

#define GAMEENGINE_NET_TCP_DISCONNECTED	0
#define GAMEENGINE_NET_TCP_NOTHING		-1
#define GAMEENGINE_NET_UDP_NOTHING		-1

namespace GameEngine
{
	struct NetClientDataTCP
	{
		SOCKET	Socket;
		uint16	Port;
		strg	IP;
	};

	struct NetClientDataUDP
	{
		uint16		Port;
		strg		IP;
		sockaddr_in SocketAddr;
		socklen_t	SocketLen;
	};

	enum class ENetClientStatus
	{
		READY,		// ready to connect
		BUSY,		// already connected
		DEAD		// connection terminated
	};
}
#endif