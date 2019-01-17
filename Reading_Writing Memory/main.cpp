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
	SlimUtils::SlimMem m_Memory;
	DWORD m_dwClientDll;

	mem.GetPID(L"csgo.exe", &pid);
	std::cout << "pid: " << pid << std::endl;
	mem.Open(pid, SlimUtils::ProcessAccess::Full);
	

	const SlimUtils::SlimModule *mod;
	mod = mem.GetModule(L"client_panorama.dll");
	m_dwClientDll = mod->ptrBase;
	std::cout << m_dwClientDll << std::endl;



	Sleep(5000);
	V.localPlayer = mem.Read<DWORD>(O.dwLocalPlayer);
	std::cout << V.localPlayer << std::endl;
	while (true)
	{
		V.flag = mem.Read<BYTE>(O.dwLocalPlayer + O.m_fFlags);
		if (GetAsyncKeyState(VK_SPACE) && O.m_fFlags & (1 << 0)) // if on ground then jump
		{
			
			mem.Write<DWORD>(O.dwForceJump, 6); 
		}
		Sleep(1);
	}
	return 0;
}
