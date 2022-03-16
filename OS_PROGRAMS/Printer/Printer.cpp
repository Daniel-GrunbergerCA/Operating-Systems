
#include "Windows.h"
#include <iostream>

int main(size_t argc, char* argv[])
{
    HANDLE hMutex = CreateMutexA(NULL, FALSE, "Mutex_hw_mutex");
    DWORD waitResult = WaitForSingleObject(hMutex, INFINITE);
    if (waitResult == WAIT_OBJECT_0) {
        std::cout << "Number is " << argv[1] << std::endl;
        Sleep(5000);
    }
    ReleaseMutex(hMutex);     
    CloseHandle(hMutex);
}

