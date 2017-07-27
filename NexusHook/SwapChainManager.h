#pragma once

#include <Windows.h>
#include <iostream>

#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")


// Class for finding current Dx11 swapchain
class SwapChainManager {
	public:
		SwapChainManager();
		~SwapChainManager();

		bool CreateDeviceAndSwapChain();
		bool FindSwapChain();

		IDXGISwapChain* pSwapChain = nullptr;


	private:
		IDXGISwapChain* pTempSwapChain = nullptr;
		ID3D11Device* pTempDevice = nullptr;
		ID3D11DeviceContext* pTempContext = nullptr;
		DWORD_PTR* pSwapChainVtable = nullptr;
};