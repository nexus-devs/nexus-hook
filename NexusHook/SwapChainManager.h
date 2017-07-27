#pragma once

#include "Includes.h"


// Class for finding current Dx11 swapchain
class SwapChainManager {
	public:
		bool _stdcall CreateDeviceAndSwapChain();
		bool FindSwapChain();
		void ReleaseTempDevices();

		IDXGISwapChain* pSwapChain = nullptr;
		ID3D11Device* pDevice = nullptr;
		ID3D11DeviceContext* pContext = nullptr;


	private:
		IDXGISwapChain* pTempSwapChain = nullptr;
		ID3D11Device* pTempDevice = nullptr;
		ID3D11DeviceContext* pTempContext = nullptr;
		DWORD_PTR* pSwapChainVtable = nullptr;
};