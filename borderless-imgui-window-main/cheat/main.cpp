#include "gui.h"
#include "snapshots.h"
#include <thread>
#include <Windows.h>
#include <iostream>
#include "off.h"

int __stdcall wWinMain(
	HINSTANCE instance,
	HINSTANCE previousInstance,
	PWSTR arguments,
	int commandShow)
{
	DWORD procId = GetProcId(L"ac_client.exe");

	uintptr_t module = GetModuleBaseAddress(procId, L"ac_client.exe");

	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procId);

	if (out::godhealth == true)
	{
		uintptr_t localPlayerAddress = 0;

		DWORD newValue = 1337;

		ReadProcessMemory(hProcess, (LPVOID)(module + offsets::localPlayer), &localPlayerAddress, sizeof(localPlayerAddress), 0);

		WriteProcessMemory(hProcess, (LPVOID)(localPlayerAddress + offsets::dwHeath), &newValue, sizeof(newValue), 0);
	}
	
	// create gui
	gui::CreateHWindow("Cheat Menu");
	gui::CreateDevice();
	gui::CreateImGui();

	while (gui::isRunning)
	{
		
		gui::BeginRender();
		gui::Render();
		gui::EndRender();

		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}

	// destroy gui
	gui::DestroyImGui();
	gui::DestroyDevice();
	gui::DestroyHWindow();

	return EXIT_SUCCESS;
}
