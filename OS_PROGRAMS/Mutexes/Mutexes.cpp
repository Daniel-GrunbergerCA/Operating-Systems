#include "Windows.h";
#include <iostream>
#include <string>

#define EXE1  "C:/Users/DanielGrunberger/Documents/CyberIlit/WindowsAPI/MessageBox/Debug/Printer.exe 5"
#define EXE2  "C:/Users/DanielGrunberger/Documents/CyberIlit/WindowsAPI/MessageBox/Debug/Printer.exe 7"
#define NUM_PROCESSES 2


int main() {
    HANDLE hMutex = CreateMutexA(NULL, FALSE, "Mutex_hw_mutex");

    PCHAR param = (PCHAR)EXE1;
    STARTUPINFOA startupInfo;
    PROCESS_INFORMATION processInfo1;
    ZeroMemory(&startupInfo, sizeof(startupInfo));
    ZeroMemory(&processInfo1, sizeof(processInfo1));
    if (!CreateProcessA(NULL, param, NULL, NULL, false, NORMAL_PRIORITY_CLASS, NULL, NULL, &startupInfo, &processInfo1)){

        std::cout<<GetLastError();
    }
     param = (PCHAR)EXE2;
     PROCESS_INFORMATION processInfo2;
     ZeroMemory(&processInfo2, sizeof(processInfo2));
    if (!CreateProcessA(NULL, param, NULL, NULL, false, NORMAL_PRIORITY_CLASS, NULL, NULL, &startupInfo, &processInfo2)) {

        std::cout << GetLastError();
    }

    WaitForSingleObject(processInfo1.hProcess, INFINITE);
    WaitForSingleObject(processInfo2.hProcess, INFINITE);

    ReleaseMutex(hMutex);
    CloseHandle(processInfo1.hProcess);
    CloseHandle(processInfo2.hProcess);
	return 0;
}


