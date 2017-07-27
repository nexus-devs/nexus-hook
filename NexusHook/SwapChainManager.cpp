#include "SwapChainManager.h"


// Creates a temponary swapchain for later use
bool _stdcall SwapChainManager::CreateDeviceAndSwapChain() {

	// Get handle of game
	HWND hWnd = FindWindow(NULL, "WARFRAME");
	if (hWnd == NULL) return false;

	// Create SwapChain description
	DXGI_SWAP_CHAIN_DESC SwapChainDesc;
	memset(&SwapChainDesc, 0, sizeof(struct DXGI_SWAP_CHAIN_DESC));
	SwapChainDesc.BufferCount = 1;
	SwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	SwapChainDesc.OutputWindow = hWnd;
	SwapChainDesc.SampleDesc.Count = 1;
	SwapChainDesc.Windowed = (GetWindowLong(hWnd, GWL_STYLE) & WS_POPUP) != 0 ? FALSE : TRUE;
	SwapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	SwapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	// Create SwapChain feature level
	D3D_FEATURE_LEVEL SwapChainFeatureLevel[1];
	SwapChainFeatureLevel[0] = D3D_FEATURE_LEVEL_11_0;

	// Create SwapChain
	HRESULT SwapChainResult = D3D11CreateDeviceAndSwapChain(
		NULL,                       // Adapter
		D3D_DRIVER_TYPE_HARDWARE,   // Driver
		NULL,                       // Software
		D3D11_CREATE_DEVICE_DEBUG,  // Flags
		SwapChainFeatureLevel,      // Feature level
		1,                          // Number of feature levels
		D3D11_SDK_VERSION,          // SDK Version
		&SwapChainDesc,				// SwapChain description
		&pTempSwapChain,            // SwapChain output
		&pTempDevice,               // Device output
		NULL,                       // Discard feature level result
		&pTempContext               // Context output
	);

	// Error handling
	if (FAILED(SwapChainResult)) {
		_com_error err(SwapChainResult);
		std::cout << "SwapChain creation failed: " << err.ErrorMessage() << std::endl;

		return false;
	}

	// Get Vtable
	pSwapChainVtable = (DWORD_PTR*)pTempSwapChain;
	pSwapChainVtable = (DWORD_PTR*)pSwapChainVtable[0];
	std::cout << "SwapChain created. Vtable: 0x" << std::hex << pSwapChainVtable << std::endl;

	return true;
}

// Finds the current swapchain using our temporary one
// Main code by smallC from UC
bool SwapChainManager::FindSwapChain() {
	
	// Create SwapChain if it isn't created already
	if (pSwapChainVtable == nullptr)
		if (!CreateDeviceAndSwapChain()) return false;

	#ifdef _AMD64_
	#define _PTR_MAX_VALUE 0x7FFFFFFEFFFF
		MEMORY_BASIC_INFORMATION64 mbi = { 0 };
	#else
	#define _PTR_MAX_VALUE 0xFFE00000
		MEMORY_BASIC_INFORMATION32 mbi = { 0 };
	#endif

	// Iterate through memory, For x64 -> 0x10000 ->  0x7FFFFFFEFFFF
	DWORD_PTR pVtableAddress = NULL;
	for (DWORD_PTR pMem = 0x10000; pMem < _PTR_MAX_VALUE; pMem = mbi.BaseAddress + mbi.RegionSize) {

		// Iterate memory by using VirtualQuery
		if (!VirtualQuery(reinterpret_cast<LPCVOID>(pMem), reinterpret_cast<PMEMORY_BASIC_INFORMATION>(&mbi), sizeof(MEMORY_BASIC_INFORMATION)))
			continue;

		// Filter Regions
		if (mbi.State != MEM_COMMIT || mbi.Protect == PAGE_NOACCESS || mbi.Protect & PAGE_GUARD)
			continue;

		// Get length
		DWORD_PTR len = mbi.BaseAddress + mbi.RegionSize;

		// Iterate through region
		for (DWORD_PTR pCurrent = mbi.BaseAddress; pCurrent < len; ++pCurrent) {
			
			// Try to cast current pointer to Vtable address
			__try { 
				pVtableAddress = *(DWORD_PTR*)pCurrent;
			}
			__except (1) {
				continue;
			}

			// Check if Vtables match
			if (pVtableAddress == (DWORD_PTR)pSwapChainVtable) {

				// Skip if its our temporary SwapChain
				if (pCurrent == (DWORD_PTR)pTempSwapChain)
					continue;

				// Otherwise, set SwapChain
				pSwapChain = (IDXGISwapChain*)pCurrent;
				std::cout << "Found SwapChain: 0x" << std::hex << pSwapChain << std::endl;

				// Get device
				if (FAILED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (LPVOID*)&pDevice))) {
					std::cout << "Failed to get device" << std::endl;
					return false;
				}

				// Get Context
				pDevice->GetImmediateContext(&pContext);
				if (!pContext) {
					std::cout << "Failed to get device context" << std::endl;
					return false;
				}

				// Release temporary devices
				ReleaseTempDevices();

				return true;
			}
		}
	}

	std::cout << "Couldn't find SwapChain" << std::endl;
	return false;
}

// Release used resources
void SwapChainManager::ReleaseTempDevices() {
	pTempSwapChain->Release();
	pTempDevice->Release();
	pTempContext->Release();
}