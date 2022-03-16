#include "Windows.h"
#include<iostream>
#define FILENAME "C:/Users/DanielGrunberger/Documents/CyberIlit/Operating Systems/gibrish.bin"
#define NEWCHAR '*'

INT GetSystemAlignmentGranularity()
{
	SYSTEM_INFO sys_info;
	GetSystemInfo(&sys_info);
	return sys_info.dwAllocationGranularity;
}

void PrintLastError() {
	std::cout << "Error: " << GetLastError() << std::endl;
}


int main() {

	INT mem_buffer_size = GetSystemAlignmentGranularity();

	HANDLE hMappedFile = OpenFileMappingA(FILE_MAP_WRITE, FALSE, "shared_mem");

	// Mapped mem exists
	if (hMappedFile != NULL)
	{
		// Read first page
		LPSTR  lpMMFile = (char*)MapViewOfFile(hMappedFile,
			FILE_MAP_WRITE,
			0,
			0, // first page
			1);
		if (lpMMFile == NULL) {
			PrintLastError();
			return 1;
		}
		lpMMFile[0] = NEWCHAR;
		std::cout << "Memory changed to " << lpMMFile[0] << std::endl;
	}
	else
	{
		HANDLE hFile = CreateFileA(FILENAME, GENERIC_WRITE | GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, NULL, NULL);
		if (hFile == INVALID_HANDLE_VALUE) {
			PrintLastError();
			return 1;
		}
		hMappedFile = CreateFileMappingA(hFile, NULL, PAGE_READWRITE, NULL, NULL, "shared_mem");
		if (hMappedFile == NULL) {
			PrintLastError();
			return 1;
		}
		LPSTR lpMMFile = (char*)MapViewOfFile(hMappedFile,
			FILE_MAP_READ,
			0,
			0, // first page
			1);
		if (lpMMFile == NULL) {
			PrintLastError();
			return 1;
		}
		while (lpMMFile[0] != NEWCHAR) {
			std::cout << "Memory is : '" << lpMMFile[0] << "' ... not good!" << std::endl;
			Sleep(500);
			lpMMFile = (char*)MapViewOfFile(hMappedFile,
				FILE_MAP_READ,
				0,
				0, // first page
				1);
			if (lpMMFile == NULL) {
				PrintLastError();
				return 1;
			}
		}
		std::cout << "Memory is: '" << lpMMFile[0] << "' ...nice!" << std::endl;
		CloseHandle(hFile);
	}

	CloseHandle(hMappedFile);

	return 0;
}