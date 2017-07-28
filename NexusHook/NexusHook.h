#pragma once

#include "Includes.h"
#include "Dx11Indexes.h"
#include "SwapChainManager.h"
#include "VMTHook.h"


// Main hooking class
class NexusHook {
	public:
		bool Init();
		bool HookSwapChain(DWORD_PTR newFunc, int index);

		SwapChainManager hMngr;

		const static int iHookNumber = SC_GETLASTPRESENTCOUNT + 1;
		VMTHook hkHooks[iHookNumber];
		DWORD oFunctions[iHookNumber] = { NULL };
};