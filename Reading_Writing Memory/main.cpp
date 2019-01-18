#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <thread>
#include "SlimMem.h"

SlimUtils::SlimMem mem;
DWORD pid;
DWORD m_dwClientDll;

struct Offset {
	DWORD dwLocalPlayer = 0xCBD6A4;
	DWORD m_fFlags = 0x104;
	DWORD dwForceJump = 0x5170DF0;
}O;
struct Values {
	DWORD localPlayer;
	DWORD gameModule;
	DWORD mod;
	BYTE flag;
}V;

bool GetMod()
{
	if (!mem.HasProcessHandle())
		return false;
	if (!mem.ParseModules())
		return false;

	const SlimUtils::SlimModule *mod;
	if ((mod = mem.GetModule(L"client_panorama.dll")) == nullptr)
	{
		mem.ParseModules();
		return false;
	}
		
	V.gameModule = mod->ptrBase;

	return true;
}
bool GetPlayer()
{
	V.localPlayer = mem.Read<DWORD>(V.gameModule + O.dwLocalPlayer);
	

	if (V.localPlayer = NULL) {
		V.localPlayer = mem.Read<DWORD>(V.gameModule + O.dwLocalPlayer);
		//std::cout << V.localPlayer << std::endl;
		return false;
	}
	return true;
}

void bhop()
{
	
}

int main()
{
	

	mem.GetPID(L"csgo.exe", &pid);
	if (pid == NULL) {
		return false;
	}
	std::cout << "pid: " << pid << std::endl;

	if (mem.Open(pid, SlimUtils::ProcessAccess::Full) == NULL)
	{
		return false;
	}
	
	GetMod();
	GetPlayer();

	std::cout << "player found" << V.localPlayer << std::endl;

	while (true)
	{
		GetPlayer();
		V.flag = mem.Read<BYTE>(V.localPlayer + O.m_fFlags);
		//std::cout << V.flag << std::endl;
		if (GetAsyncKeyState(VK_SPACE) && V.flag & (1 << 0)) // if on ground then jump
		{
			mem.Write<DWORD>(V.gameModule + O.dwForceJump, 6);
		}
	}
	
	std::cout << "test";

	
	
	return 0;
}

