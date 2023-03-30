#pragma once
#include <Windows.h>
#include <vector>
DWORD* Pointer(DWORD base_address, DWORD static_offset, std::vector<DWORD> offsets);
void detour(void* src, void* dest, int len);
void detourcall(void* src, void* dest, int len);