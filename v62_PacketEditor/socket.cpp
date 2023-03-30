#include "pch.h"
#include "socket.h"

extern SOCKET ClientSock = INVALID_SOCKET;
extern SOCKET ClientSockRecv = INVALID_SOCKET;

int	startServer(SOCKET &clientsock, PCSTR port)
{
	WSADATA wsaData;
	int iResult;

	SOCKET ListenSocket = INVALID_SOCKET;

	struct addrinfo* result = NULL;
	struct addrinfo hints;

	char recvbuf[4096];

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
		return -1;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	// Resolve the server address and port
	iResult = getaddrinfo(NULL, port, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed with error: %d\n", iResult);
		WSACleanup();
		return -1;
	}

	// Create a SOCKET for the server to listen for client connections.
	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (ListenSocket == INVALID_SOCKET) {
		printf("socket failed with error: %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return -1;
	}

	// Setup the TCP listening socket
	iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		printf("bind failed with error: %d\n", WSAGetLastError());
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
		return -1;
	}

	freeaddrinfo(result);

	iResult = listen(ListenSocket, SOMAXCONN);
	if (iResult == SOCKET_ERROR) {
		printf("listen failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return -1;
	}

	// Accept a client socket
	clientsock = accept(ListenSocket, NULL, NULL);
	if (clientsock == INVALID_SOCKET) {
		printf("accept failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	std::cout << "Client connected to Server\n";

	// No longer need server socket
	closesocket(ListenSocket);
	ZeroMemory(recvbuf, 4096);
	do {
		iResult = recv(clientsock, recvbuf, 4096, 0);
		/*
		if (iResult >= 0 && iResult < 4096)
			recvbuf[iResult] = '\0';
		if (recvbuf[0] != '\0')
		*/
		if (iResult != 0 && iResult < 4096 && iResult > 0)
			callSendPacket((BYTE*)recvbuf, iResult);
		Sleep(10);
	} while (iResult != 0 && iResult != 0xffffffff); // If Connection lost iResult = 0xffffffff
	std::cout << "Connection to Client lost.\n";
	return (0);
}
