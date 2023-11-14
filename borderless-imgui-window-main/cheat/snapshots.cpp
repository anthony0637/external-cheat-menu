#include "snapshots.h"
#include <Windows.h>
#include <iostream>
#include <TlHelp32.h>

DWORD GetProcId(const wchar_t* procName)
{
	DWORD procId = 0;

	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (hSnap != INVALID_HANDLE_VALUE)
	{
		PROCESSENTRY32W procEntry;
		procEntry.dwSize = sizeof(procEntry);

		if (Process32FirstW(hSnap, &procEntry))
		{
			do
			{
				if (_wcsicmp(procEntry.szExeFile, procName))
				{
					procId = procEntry.th32ProcessID;
					break;
				}

			} while (Process32NextW(hSnap, &procEntry));
		}
	}
	else
	{
		return EXIT_FAILURE;
	}
	CloseHandle(hSnap);
	return procId;
}

uintptr_t GetModuleBaseAddress(DWORD procId, const wchar_t* modName)
{
	uintptr_t module = 0;

	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE and TH32CS_SNAPMODULE32, procId);

	if (hSnap != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32W modEntry;
		modEntry.dwSize = sizeof(modEntry);

		if (Module32FirstW(hSnap, &modEntry))
		{
			do
			{
				if (!_wcsicmp(modEntry.szModule, modName))
				{
					MODULEENTRY32 modEntry;
					modEntry.dwSize = sizeof(modEntry);
				}

			} while (Module32NextW(hSnap, &modEntry));
		}
	}
	else
	{
		return EXIT_FAILURE;
	}
	CloseHandle(hSnap);
	return module;
}

