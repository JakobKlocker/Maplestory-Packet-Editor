#include "pch.h"
#include "packetHacks.h"

void mainHackingThread()
{
	std::string onOff;
	onOff = "off";
	std::thread NDFMA(rangedAttackNDFMA, std::ref(onOff));
	while (1)
	{
		std::cin >> onOff;
		if (onOff == "on")
			std::cout << "Ranged Attack ND FMA turned on\nType off to disable\n";
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

void rangedAttackNDFMA(std::string& onOff)
{
	while (1)
	{
		if (onOff == "on")
		{
			if (tmp[0] != 0)
			{
				callSendPacket(tmp, sizeof(tmp));
				tmp[0] = 0;
			}
		}
		//std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}
