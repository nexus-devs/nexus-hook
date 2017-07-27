#include "VMTHook.h"


// Default constructor, init memory
VMTHook::VMTHook() {
	memset(this, 0, sizeof(VMTHook));
}

// Constructor with base class
VMTHook::VMTHook(PDWORD* ppdwClassBase) {
	m_ppdwClassBase = ppdwClassBase;
	m_pdwOldVMT = *ppdwClassBase;
	m_iVMTCount = iGetVMTCount(m_pdwOldVMT);
	m_pdwNewVMT = new DWORD[m_iVMTCount];
	memcpy(m_pdwNewVMT, m_pdwOldVMT, 0x4 * m_iVMTCount);
	*ppdwClassBase = m_pdwNewVMT;
}

// Hooks the base class
DWORD VMTHook::Hook(DWORD newFunc, int index) {
	if (index <= m_iVMTCount && index >= 0 &&
		m_pdwNewVMT && m_pdwOldVMT)
	{
		DWORD ret = m_pdwOldVMT[index];
		m_pdwNewVMT[index] = newFunc;
		return ret;
	}
	else
		return NULL;
}

// Unhooks the base class
void VMTHook::UnHook() {
	if (m_ppdwClassBase)
	{
		*m_ppdwClassBase = m_pdwOldVMT;
	}
}

// Rehooks the base class
void VMTHook::ReHook() {
	if (m_ppdwClassBase)
	{
		*m_ppdwClassBase = m_pdwNewVMT;
	}
}

// Gets VMT count
int VMTHook::iGetVMTCount(PDWORD pBase) {
	int iCount = 0;

	for (; pBase[iCount]; ++iCount);

	return iCount;
}