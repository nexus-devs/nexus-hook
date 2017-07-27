#include "Includes.h"


void InitDll()
{
	// Set up console
	AllocConsole();
	AttachConsole(GetCurrentProcessId());
	freopen("CON", "w", stdout);
	std::cout << "DLL attached" << std::endl;

	// Call hook
}

BOOL WINAPI DllMain(HINSTANCE hModule, DWORD fwdReason, LPVOID lpvReserved) {

	if (fwdReason == DLL_PROCESS_ATTACH) {
		// Create new thread
		DisableThreadLibraryCalls(hModule);
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)InitDll, NULL, NULL, NULL);
	}

	return true;
}