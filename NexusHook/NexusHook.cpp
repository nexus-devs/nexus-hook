#include "NexusHook.h"


// Initialization
bool NexusHook::Init() {

	// Setup SwapChain
	if (!hMngr.CreateDeviceAndSwapChain()) return false;
	if (!hMngr.FindSwapChain()) return false;

	return true;
}

// Hooking
bool NexusHook::HookSwapChain(DWORD_PTR newFunc, int index) {

	// Set up VMTHook
	hkHooks[index] = VMTHook((PDWORD*)hMngr.pSwapChain);

	// Hook function
	if (oFunctions[index] = hkHooks[index].Hook(newFunc, SC_PRESENT) == NULL) return false;

	return true;
}