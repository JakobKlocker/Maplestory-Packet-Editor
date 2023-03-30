#pragma once
#include<winsock2.h>
#include<ws2tcpip.h>
#include <iostream>
#include "sendPacket.h"
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib,"ws2_32.lib") //Winsock Library
extern SOCKET ClientSock;
extern SOCKET ClientSockRecv;
int	startServer(SOCKET &clientsock, PCSTR port);