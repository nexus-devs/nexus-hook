#include "SwapChainManager.h"


// Creates a temponary swapchain for later use
bool _stdcall SwapChainManager::CreateDeviceAndSwapChain() {

}

// Finds the current swapchain using our temporary one
bool SwapChainManager::FindSwapChain() {

}

// Release used resources
SwapChainManager::~SwapChainManager() {
	this->pTempSwapChain->Release();
	this->pTempDevice->Release();
	this->pTempContext->Release();
}