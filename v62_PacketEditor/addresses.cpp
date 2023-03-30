#include "pch.h"

DWORD moduleBase = 0x00000000;
DWORD packetLogHook = 0x6ECB3B;
DWORD packetLogHookret = 0x6ECB3B + 6;
DWORD logLength;
unsigned char* bytePtr;
unsigned char* recvBuffPtr;

void* teax;
void* tebx;
void* tecx;
void* tedx;
void* tesi;
void* tedi;
void* tebp;
void* tesp;