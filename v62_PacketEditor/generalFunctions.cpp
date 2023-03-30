#include "pch.h"
#include "generalFunctions.h"

//Convert Ascii to Hex
static PUCHAR atohx(PUCHAR szDestination, LPCSTR szSource) {
	const PUCHAR szReturn = szDestination;
	for (int lsb, msb; *szSource; szSource += 2) {
		msb = tolower(*szSource);
		lsb = tolower(*(szSource + 1));
		msb -= isdigit(msb) ? 0x30 : 0x57;
		lsb -= isdigit(lsb) ? 0x30 : 0x57;
		if ((msb < 0x0 || msb > 0xf) || (lsb < 0x0 || lsb > 0xf)) {
			*szReturn = 0;
			return nullptr;
		}
		*szDestination++ = static_cast<char>(lsb | (msb << 4));
	}
	*szDestination = 0;
	return szReturn;
}
