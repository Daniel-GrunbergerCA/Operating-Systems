#include "Windows.h"
#include <iostream>
#define DLL_PATH "C:/Users/DanielGrunberger/source/repos/OperatingSystems/Debug/Injection.dll"
#define PID 14364

void PrintLastError()
{
	std::cout << GetLastError() << std::endl;
}

int main()
{

	PVOID loadLribaryAddr = (PVOID)GetProcAddress(GetModuleHandle(L"kernel32.dll"), "LoadLibraryA");
	if (loadLribaryAddr == NULL) {
		PrintLastError();
		return 1;
	}
	
	HANDLE proc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, PID);
	if (proc == NULL) {
		PrintLastError();
		return 1;	
	}


	LPVOID allocatedMem = VirtualAllocEx(proc, NULL, strlen(DLL_PATH), MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (allocatedMem == NULL) {
		PrintLastError();
		return 1;
	}

	if (!WriteProcessMemory(proc, allocatedMem, DLL_PATH, strlen(DLL_PATH), NULL))
	{
		PrintLastError();
	}
	HANDLE hRemote = CreateRemoteThread(proc, NULL, NULL, (LPTHREAD_START_ROUTINE)loadLribaryAddr, allocatedMem, NULL, NULL);
	if (hRemote == NULL) {
		PrintLastError();
		return 1;
	}
	
	WaitForSingleObject(proc, INFINITE);
	CloseHandle(hRemote);
	return 0;
}