#pragma once
#include "socket.h"
#include "addresses.h"
void logrecvHook();
extern void* recvHook;
extern void* recvHookRet;
extern void* buffer;
extern DWORD pLength;
inline void sendPacketToClientRecv();
void	AddrRetHookRecv();