// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "Main.h"

DWORD WINAPI HackThread(HMODULE hModule)
{
	//Create Console
	AllocConsole();
	FILE* f;
	freopen_s(&f, "CONOUT$", "w+", stdout);
	freopen_s(&f, "CONIN$", "r", stdin);

	moduleBase = (uintptr_t)GetModuleHandle(NULL);

	detour((char*)(moduleBase + 0x2ECB3B), (char*)logHook, 6);
	detourcall((char*)(moduleBase + 0x9661A), (char*)logrecvHook, 5);
	detour((char*)sendHook, (char*)AddrRetHookSend, 5);
	//detour((char*)recvHook, (char*)AddrRetHookRecv, 5);
	std::thread thread_packetHacks(mainHackingThread);

	while (true)
	{
		std::thread t(startServer, std::ref(ClientSock), "2020");
		startServer(ClientSockRecv, "2021");
		Sleep(100);
	}
	fclose(f);
	FreeConsole();
	FreeLibraryAndExitThread(hModule, 0);
	return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)HackThread, hModule, 0, nullptr));
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}
