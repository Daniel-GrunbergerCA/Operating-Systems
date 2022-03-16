#include "Windows.h"
#define DLL_EXPORT
#include "injection.h"
extern "C"
{
	DECLDIR void Share()
	{
		int msgboxID = MessageBoxA(NULL,
			(LPCSTR)"Hacked by Daniel Grunberger\n",
			(LPCSTR)"DLL Injection Hack",
			MB_DEFBUTTON2);
	}
}
BOOL APIENTRY DllMain(
	HANDLE hModule, 
	DWORD ul_reason_for_call,
	LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		Share();
		break;
	}


	return TRUE;
}
