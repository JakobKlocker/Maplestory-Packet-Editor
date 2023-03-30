#pragma once
#include "socket.h"
#include "addresses.h"

extern BYTE tmp[64];

struct COutPacket {
	int zero;
	void* data;
	int Size;
	int	pad;
	int pad_1;
};

typedef void(__thiscall* PacketSend)(PVOID clientSocket, COutPacket* packet);

inline void sendPacketToClient();
inline void printPacket();
std::string randoomizeStar(std::string str);
void callSendPacket(BYTE packet[], int size);
void logHook();
void AddrRetHookSend();

inline void createByteForNDFMA();

extern void* sendHook;
extern void* sendHookRet;
extern ULONG clientSocketAddr;



extern PVOID* ClientSocket;
 //Send packet from client to server
extern PacketSend Send;