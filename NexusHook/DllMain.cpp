#include "Includes.h"
#include "SwapChainManager.h"
#include "VMTHook.h"
#include "Dx11Indexes.h"


// Typedefs
typedef HRESULT(__stdcall *D3D11PresentHook) (IDXGISwapChain* This, UINT SyncInterval, UINT Flags);
D3D11PresentHook oPresent = NULL;

// Variables
SwapChainManager hMngr;
VMTHook hkPresent;

// Present hook
HRESULT __stdcall SwapChainPresentHook(IDXGISwapChain* pThis, UINT SyncInterval, UINT Flags) {
	std::cout << "Hook called!" << std::endl;
	return oPresent(pThis, SyncInterval, Flags);
}

void InitDll()
{
	// Set up console
	AllocConsole();
	AttachConsole(GetCurrentProcessId());
	freopen("CON", "w", stdout);
	std::cout << "Dll attached" << std::endl;

	// Get SwapChain
	hMngr.CreateDeviceAndSwapChain();
	hMngr.FindSwapChain();

	// Set up hook
	hkPresent = VMTHook((PDWORD*)hMngr.pSwapChain);

	// Hook present
	oPresent = (D3D11PresentHook)hkPresent.Hook((DWORD_PTR)SwapChainPresentHook, SC_PRESENT);
	std::cout << "Present hooked" << std::endl;
}

BOOL WINAPI DllMain(HINSTANCE hModule, DWORD fwdReason, LPVOID lpvReserved) {

	if (fwdReason == DLL_PROCESS_ATTACH) {
		// Create new thread
		DisableThreadLibraryCalls(hModule);
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)InitDll, NULL, NULL, NULL);
	}

	return true;
}