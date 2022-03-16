#include "Windows.h";
#include <iostream>

#define NUMBER_OF_PHILOSOFERS 5
#define NUMBER_OF_CHOPSTICKS 5
#define NUMBER_OF_MEALS 1000000

HANDLE hThread[NUMBER_OF_PHILOSOFERS];

CRITICAL_SECTION chopsticks[NUMBER_OF_CHOPSTICKS];


DWORD WINAPI Eat(LPVOID id)
{
	INT chop1 = *(PINT)id;
	INT chop2 = chop1 + 1;

	if (chop2 == NUMBER_OF_CHOPSTICKS)
		chop2 = 0;

	for (int j = 0; j < NUMBER_OF_MEALS; j++)
	{
		EnterCriticalSection(&(chopsticks[chop1]));
		if (!TryEnterCriticalSection(&(chopsticks[chop2]))) {
			LeaveCriticalSection(&(chopsticks[chop1]));
			j = j - 1;
			continue;
		}
		else {
			LeaveCriticalSection(&(chopsticks[chop1]));
			LeaveCriticalSection(&(chopsticks[chop2]));
		}
	}
	return 0;
}


int main()
{
	int arr[] = { 0, 1, 2, 3, 4 };
	DWORD startTime = GetTickCount();
	for (int i = 0; i < NUMBER_OF_CHOPSTICKS; i++)
	{
		InitializeCriticalSection(&chopsticks[i]);
	}

	for (int i = 0; i < NUMBER_OF_PHILOSOFERS; i++)
	{
			hThread[i] = CreateThread(NULL, 0, Eat, arr + i, 0, NULL);
			if (hThread[i] == NULL) {
				std::cout << "Error: " << GetLastError() << std::endl;
			}
	}

	WaitForMultipleObjects(NUMBER_OF_PHILOSOFERS, hThread, TRUE, INFINITE);
	for (int i = 0; i < NUMBER_OF_PHILOSOFERS; i++)
	{
		DeleteCriticalSection(&chopsticks[i]);
	}

	for (int i = 0; i < NUMBER_OF_PHILOSOFERS; i++)
	{
		CloseHandle(hThread[i]);
	}

	std::cout << "The program took " << GetTickCount() - startTime <<  " miliseconds to run." << std::endl;
	return 0;
}

