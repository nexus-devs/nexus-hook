[![NexusHook](/banner.png)](https://github.com/nexus-devs)
<p align="center">SwapChain hooking functionality for DirectX11 applications.</p>

##

<br>

## Installation
Download the latest release, include `NexusHook.h` and link the `.lib` against your project.

<br>

## Usage
```cpp
#include "NexusHook.h"
#pragma comment(lib, "NexusHook.lib")

typedef HRESULT(__stdcall *D3D11PresentHook) (IDXGISwapChain* pThis, UINT SyncInterval, UINT Flags);
NexusHook hkMngr;

// Present hook
HRESULT __stdcall SwapChainPresentHook(IDXGISwapChain* pThis, UINT SyncInterval, UINT Flags) {
    std::cout << "Hook called!" << std::endl;
    return (D3D11PresentHook)hkMngr.oFunctions[SC_PRESENT];
}

void main() {
	// Init hook manager
	hkMngr.Init();

	// Hook present
	hkMngr.HookSwapChain((DWORD_PTR)SwapChainPresentHook, SC_PRESENT);
}
```

<br>
<br>

## API

### Methods
```cpp
bool Init();
```
>Initializes the hook manager. Returns true on success, false otherwise.

| Argument | Description | Default |
|:------------- |:------------- |:------------- |
| None | None | None |

<br>

```cpp
bool HookSwapChain(DWORD_PTR newFunc, int index);
```
>Hooks the specified function of the current SwapChain. Returns true on success, false otherwise.

| Argument | Description | Default |
|:------------- |:------------- |:------------- |
| newFunc | Pointer to your replacement function. | None |
| url | Vtable index of the function you want to hook. | None |

<br>

### Fields
```cpp
const static int iHookNumber = SC_GETLASTPRESENTCOUNT + 1;
```
>Number of functions you can hook. Specified in Dx11Indexes.h

<br>

```cpp
VMTHook hkHooks[iHookNumber];
```
>All hooks stored in their respecting index number.

<br>

```cpp
DWORD oFunctions[iHookNumber] = { NULL };;
```
>All original functions from the original SwapChain.

<br>

```cpp
SwapChainManager hMngr;
```
>SwapChainManager, you shouldn't need to access this.

<br>

## License
[MIT](https://github.com/nexus-devs/nexus-hook/blob/master/LICENSE.md)