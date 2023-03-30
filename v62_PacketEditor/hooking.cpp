#include "pch.h"

DWORD* Pointer(DWORD base_address, DWORD static_offset, std::vector<DWORD> offsets)
{
	// program base address + static offset
	auto p = reinterpret_cast<DWORD*>(base_address + static_offset);

	// loop though the offsets
	for (const DWORD& offset : offsets)
	{
		// add the offset to the dereferenced pointer
		if (IsBadReadPtr(p, sizeof(DWORD*)))
			return 0;
		p = reinterpret_cast<DWORD*>(*p + offset);
	}

	return p;
}

void detour(void* src, void* dest, int len)
{
	DWORD  curProtection;
	VirtualProtect(src, len, PAGE_EXECUTE_READWRITE, &curProtection);

	DWORD how_far = (DWORD)dest - (DWORD)src - 5;
	memset(src, 0x90, len);
	*(char*)src = (char)'\xE9';
	*(DWORD*)((DWORD)src + 1) = how_far;
	VirtualProtect(src, len, curProtection, &curProtection);
}

void detourcall(void* src, void* dest, int len)
{
	DWORD  curProtection;
	VirtualProtect(src, len, PAGE_EXECUTE_READWRITE, &curProtection);

	DWORD how_far = (DWORD)dest - (DWORD)src - 5;
	memset(src, 0x90, len);
	*(char*)src = (char)'\xE8';
	*(DWORD*)((DWORD)src + 1) = how_far;
	VirtualProtect(src, len, curProtection, &curProtection);
}
