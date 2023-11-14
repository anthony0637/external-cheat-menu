#include <Windows.h>
#include <iostream>
#include <TlHelp32.h>


DWORD GetProcId(const wchar_t* procName);

uintptr_t GetModuleBaseAddress(DWORD procId, const wchar_t* modName);

