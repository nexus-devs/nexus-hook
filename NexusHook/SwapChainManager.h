#pragma once

#include "Includes.h"


// Class for finding current Dx11 swapchain
class SwapChainManager {
	public:
		~SwapChainManager();

		bool _stdcall CreateDeviceAndSwapChain();
		bool FindSwapChain();

		IDXGISwapChain* pSwapChain = nullptr;


	private:
		IDXGISwapChain* pTempSwapChain = nullptr;
		ID3D11Device* pTempDevice = nullptr;
		ID3D11DeviceContext* pTempContext = nullptr;
		DWORD_PTR* pSwapChainVtable = nullptr;
};