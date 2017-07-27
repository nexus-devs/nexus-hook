#pragma once

#include "Includes.h"


class VMTHook {
	public:
		VMTHook();
		VMTHook(PDWORD* ppdwClassBase);

		DWORD Hook(DWORD newFunc, int index);
		void UnHook();
		void ReHook();


	private:
		int iGetVMTCount(PDWORD pBase);

		int m_iVMTCount;
		PDWORD* m_ppdwClassBase;
		PDWORD m_pdwOldVMT;
		PDWORD m_pdwNewVMT;
};