#include<Windows.h>
#include <iostream>
#include<string>
#define NUMBER_OF_MEALS 1000000


int main(size_t argc, char* argv[])
{
    if (argc != 2)
    {
        std::cout << "Requires one parameter" << std::endl;

        return 1;
    }


    INT chop1 = atoi(argv[1]);
    INT chop2 = chop1 + 1;

    if (chop2 == NUMBER_OF_MEALS) {
        chop2 = 0;
    }
    HANDLE chopstick1 = CreateMutexA(NULL, FALSE, ("chopstick" + std::to_string(chop1)).c_str());
    HANDLE chopstick2 = CreateMutexA(NULL, FALSE, ("chopstick" + std::to_string(chop2)).c_str());

    for (int i = 0; i < NUMBER_OF_MEALS; i++) {
        DWORD waitResult = WaitForSingleObject(chopstick1, INFINITE);
        waitResult = WaitForSingleObject(chopstick2, 0);
        if (waitResult != WAIT_OBJECT_0)
        {
            ReleaseMutex(chopstick1);
            i = i - 1;
            continue;
        }
        else {
            if (!ReleaseMutex(chopstick1)) {
                std::cout << "Error: " << GetLastError() << std::endl;
            }
            if (!ReleaseMutex(chopstick2)) {
                std::cout << "Error: " << GetLastError() << std::endl;
            }
        }
    }
    CloseHandle(chopstick1);
    CloseHandle(chopstick2);

    return 1;
}