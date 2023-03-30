#include "pch.h"
#include "recvPacket.h"
#include <iostream>
void* recvHook = (void*)0x0049637B;
void* recvHookRet = (void*)(0x0049637B + 5);
DWORD pLength = 0;

/*
void __declspec(naked) AddrRetHookRecv()
{
	__asm {
		mov eax, [esp + 0]
		mov [recvRetAddr], eax
		mov eax, 0x00A8126C
		jmp [recvHookRet]
	}
}
*/

void __declspec(naked) logrecvHook()
{
	__asm {
		push ebp
		mov ebp, esp
		push ecx
		mov edx, [ecx + 0x14]
		mov eax, [ecx + 0x08]
		push esi
		movzx esi, word ptr[ecx + 0x0C]
		sub esi, edx
		add eax, edx
		cmp esi, 02
		push eax
		movzx eax, word ptr[ecx + 0x0C]
		sub eax, edx
		mov[pLength],eax
		pop eax
		pop esi
		jae jaelab
		push 0x00B44EE0
		lea eax, [ebp - 0x04]
		push eax
		mov[ebp - 0x04], 00000026
		push eax
		mov eax, 0x00A60BB7
		call eax
		pop eax
		jaelab:
		mov[recvBuffPtr], eax
		pushad
	}
	sendPacketToClientRecv();
	__asm {
		popad
		mov ax, [eax]
		add edx, 02
		mov[ecx + 0x14], edx
		leave
		ret
	}
}

inline void sendPacketToClientRecv()
{
	if (ClientSockRecv != INVALID_SOCKET && recvBuffPtr != 0 && pLength != 0)
	{
		char* buf = new char[pLength + 4]();
		memset(buf, 0, 4);
		memcpy(buf + 4, recvBuffPtr, pLength);
		send(ClientSockRecv, buf, pLength + 4, 0);
		delete[] buf;
	}
}

inline void printPacket() {
	unsigned int count;
	if (recvBuffPtr == 0 || pLength == 0)
		return;
	for (count = 0; count < pLength; count++) {
		printf("%.2x ", recvBuffPtr[count]);
	}
	printf("\n");
}