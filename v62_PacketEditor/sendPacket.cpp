#include "pch.h"
#include "sendPacket.h"

void* sendRetAddr = 0;
void* sendHook = (void*)0x0049637B;
void* sendHookRet = (void*)(0x0049637B + 5);
ULONG clientSocketAddr = 0x00BE7914;
PVOID* ClientSocket = reinterpret_cast<PVOID*>(clientSocketAddr);
PacketSend Send = reinterpret_cast<PacketSend>(sendHook);
BYTE tmp[64] = { 0 };

void __declspec(naked) AddrRetHookSend()
{
	__asm {
		mov eax, [esp + 0]
		mov[sendRetAddr], eax
		mov eax, 0x00A8126C
		jmp [sendHookRet]
	}
}

void __declspec(naked) logHook()
{
	__asm {
		mov eax, [ebx + 0x08]
		lea ecx, [eax + 0x04]
		pushad
		mov eax, [ebx + 0x04]
		mov[bytePtr], eax
		mov eax, [ebx + 0x08]
		mov[logLength], eax
	}
	sendPacketToClient();
	createByteForNDFMA();
	__asm {
		test al, al
		popad
		jmp[packetLogHookret]
	}
}


inline void sendPacketToClient()
{
	if (ClientSock != INVALID_SOCKET && bytePtr != 0 && logLength != 0)
	{
		char buf[4096];
		*(int*)buf = (int)sendRetAddr;
		memcpy(buf + 4, bytePtr, logLength);
		send(ClientSock, buf, logLength + 4, 0);
	}
}

inline void createByteForNDFMA()
{
	if (*(unsigned char*)bytePtr == 0xbc)
	{
		BYTE tmp1[] = { 0x2D, 0x00, 0x01, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16, 
			0x80, 0x03, 0x06, 0x29, 0x4C, 0x1A, 0x0B, 0x03, 0x00, 0x00, 0x00, 0x1E, 0x12, 0xCA, 0x9A, 0x3B, 0x06, 0x81, 0x0A, 0x05, 
			0x95, 0xFE, 0xCF, 0xFF, 0x95, 0xFE, 0xCF, 0xFF, 0xE9, 0x02, 0x53, 0x09, 0x00, 0x00, 0x92, 0x0F, 0x09, 0xB5, 0x7A, 0xFF, 
			0xB0, 0xFF, 0x5C, 0xFF, 0x94, 0xFF };
		memcpy(tmp1 + 30, bytePtr + 2, 4);
		memcpy(tmp, tmp1, 64);
	}
}

inline void printPacket() {
	unsigned int count;
	if (bytePtr == 0 || logLength == 0)
		return;
	for (count = 0; count < logLength; count++) {
		printf("%.2x ", bytePtr[count]);
	}
	printf("\n");
}

std::string randoomizeStar(std::string str)
{
	char base[17] = "0123456789abcdef";
	int i = 0;
	while (str[i])
	{
		if (str[i] == '*')
			str[i] = base[rand() % 15];
		i++;
	}
	return str;
}

void callSendPacket(BYTE packet[], int size)
{
	COutPacket Packet;
	SecureZeroMemory(&Packet, sizeof(COutPacket));
	Packet.Size = size;
	Packet.data = (void*)packet;
	Send(*ClientSocket, &Packet);
}
