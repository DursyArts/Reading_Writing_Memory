#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include "SlimMem.h"

SlimUtils::SlimMem mem;



struct Offset {
	DWORD dwLocalPlayer = 0xCBD6A4;
	DWORD m_fFlags = 0x104;
	DWORD dwForceJump = 0x5170DF0;
}O;
struct Values {
	DWORD localPlayer;
	DWORD mod;
	BYTE flag;
}V;

int main()
{
	DWORD pid;
	mem.GetPID(L"csgo.exe", &pid);
	mem.Open(pid, SlimUtils::ProcessAccess::Full);
	auto mod = mem.GetModule(L"client_panorama.dll");
	//std::cout << mod << std::endl;
	V.localPlayer = mem.Read<DWORD>(O.dwLocalPlayer);

	while (true)
	{
		V.flag = mem.Read<BYTE>(O.dwLocalPlayer + O.m_fFlags);
		if (GetAsyncKeyState(VK_SPACE) && O.m_fFlags & (1 << 0)) // if on ground then jump
		{
			
			//mem.Write<DWORD>(mod + O.dwForceJump, 6); 
		}
	}
	return 0;
}
