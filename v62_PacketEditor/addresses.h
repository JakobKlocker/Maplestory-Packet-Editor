#pragma once

//Offsets
/*

DWORD mesosOffset = 0xE3201;
DWORD HOffset = 0xE30E4;
DWORD ztlOffset = 0xE3203;
DWORD jmp_backmesos = 0x004E3208;
DWORD callFunc = 0x004165B1;

//Stats
DWORD Mesos = 0x0000;
*/

extern DWORD moduleBase;

//Multi Level Pointer Array
//std::vector<DWORD> ExpPercentPointer = { 0xAF8, 0x24, 0xBC8 };

//Packet Stuff
extern DWORD packetLogHook;
extern DWORD packetLogHookret;
extern DWORD logLength;
extern unsigned char* bytePtr;
extern unsigned char* recvBuffPtr;

extern void* teax;
extern void* tebx;
extern void* tecx;
extern void* tedx;
extern void* tesi;
extern void* tedi;
extern void* tebp;
extern void* tesp;