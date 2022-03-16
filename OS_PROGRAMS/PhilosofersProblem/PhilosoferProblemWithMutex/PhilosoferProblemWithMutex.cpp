#include "Windows.h";
#include <iostream>
#include <string>

#define NUMBER_OF_PHILOSOFERS 5

int main() {
    DWORD startTime = GetTickCount();
    STARTUPINFOA startupInfo;
    PROCESS_INFORMATION processInfo[NUMBER_OF_PHILOSOFERS];
    ZeroMemory(&startupInfo, sizeof(startupInfo));
    startupInfo.cb = sizeof(startupInfo.cb);
    int array[] = { 0, 1, 2, 3, 4 };

    for (int i = 0; i < NUMBER_OF_PHILOSOFERS; i++)
    {
        ZeroMemory(&processInfo[i], sizeof(processInfo[i]));
        if (!CreateProcessA(NULL,(LPSTR)("../Debug/SinglePhilosopher.exe " + std::to_string(array[i])).c_str(), NULL, NULL, false, NORMAL_PRIORITY_CLASS, NULL, NULL, &startupInfo, &processInfo[i])) {
            std::cout << GetLastError();
        }
    }

    for (int i = 0; i < NUMBER_OF_PHILOSOFERS; i++)
    {
        WaitForSingleObject(processInfo[i].hProcess, INFINITE);
    }

    for (int i = 0; i < NUMBER_OF_PHILOSOFERS; i++)
    {
        CloseHandle(processInfo[i].hProcess);
    }


    std::cout << "The program took " << GetTickCount() - startTime << " miliseconds to run." << std::endl;
	return 0;
}

