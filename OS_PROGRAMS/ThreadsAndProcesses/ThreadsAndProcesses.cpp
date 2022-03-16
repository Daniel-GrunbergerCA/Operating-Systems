#include <Windows.h>
#include <iostream>

#define NUMBER_OF_PRINTS 1000
#define NUMBER_OF_THREADS 4

struct ThreadStruct
{
    INT serialNumber;
};

DWORD WINAPI functionToExecute(LPVOID lparam)
{
    ThreadStruct *paramStruct  = (ThreadStruct*)lparam;
    for (int i = 0; i <= NUMBER_OF_PRINTS; i++) {    
        printf("Thread : %d var: %d\n", paramStruct->serialNumber, i);
    }
    return 0;
}

int main()
{
    HANDLE handlesArray[NUMBER_OF_THREADS];
    for (int i = 0; i < NUMBER_OF_THREADS; i++) {
        ThreadStruct* tmp  = (ThreadStruct*)malloc(sizeof(ThreadStruct));
        tmp->serialNumber = i + 1;
      
        HANDLE hThread = CreateThread(NULL, NULL, functionToExecute, tmp, NULL, NULL);
        if (hThread == INVALID_HANDLE_VALUE)
            printf("Failed to create thread number %d. Error: %d\n", i + 1, GetLastError());
        else {
            handlesArray[i] = hThread;
        }
    }

    if (WaitForMultipleObjects(NUMBER_OF_THREADS, handlesArray, TRUE, INFINITE) == WAIT_FAILED) {
        printf("Wait error: %d\n", GetLastError());
         ExitProcess(0);
    }

    for (int i = 0; i < NUMBER_OF_THREADS; i++) {
         if (!CloseHandle(handlesArray[i]))
             printf("Error closing handle: %d\n", GetLastError());
    }
  
	return 0;
}

