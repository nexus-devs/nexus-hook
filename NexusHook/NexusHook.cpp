#include "NexusHook.h"


// Initialization
bool NexusHook::Init() {

	// Setup SwapChain
	if (!hMngr.CreateDeviceAndSwapChain()) return false;
	if (!hMngr.FindSwapChain()) return false;

	return true;
}

// Hooking
bool NexusHook::HookSwapChain(DWORD newFunc, int index) {


	return true;
}