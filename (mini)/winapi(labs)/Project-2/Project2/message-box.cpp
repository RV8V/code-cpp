#include <stdafx.h>
#include <Windows.h>
#include <stdio.h>
#include <malloc.h>

#define COUNT_THREADS 3

VOID multi_thread(VOID);
VOID messages(VOID);

DWORD WINAPI work_thread_a(LPVOID);
DWORD WINAPI work_thread_b(LPVOID);
DWORD WINAPI work_thread_c(LPVOID);

int main(int argc, const char** argv)
{
	messages();
	return 0;
}

VOID messages(VOID)
{
	INT i = MessageBox(NULL, L"Process started!",
		L"Info", MB_ICONINFORMATION | MB_OKCANCEL);
	wprintf(L"%d\n", i);
	HANDLE hIO = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD i_count = 0;
	WriteConsole(hIO, L"Hello world!\n", 13, &i_count, NULL);
	CloseHandle(hIO);

	hIO = GetStdHandle(STD_OUTPUT_HANDLE);
	LPWSTR arr = (LPWSTR)calloc(255, sizeof(WCHAR));
	ReadConsole(hIO, arr, 255, &i_count, NULL);
	MessageBox(NULL, arr, NULL, MB_ICONEXCLAMATION);

	CloseHandle(hIO);
	free(arr);
}

VOID multi_thread(VOID)
{
	HANDLE h_arr[COUNT_THREADS];
	INT i = 0;
	do
	{
		*(h_arr + i) = CreateThread(NULL, 0, work_thread_a, NULL, 0, 0);
	} while (i++ < COUNT_THREADS);

	WaitForMultipleObjects(COUNT_THREADS, h_arr, TRUE, INFINITE);
	for (DWORD i = 0; i < COUNT_THREADS; ++i)
		CloseHandle(*(h_arr + i);
}

DWORD WINAPI work_thread_a(LPVOID)
{
	INT i = 0;
	do
	{
		wprintf(L"message 0: %d\n", i);
	} while (++i < 100);
}

DWORD WINAPI work_thread_b(LPVOID)
{
	INT i = 0;
	do
	{
		wprintf(L"message 1: %d\n", i);
	} while (++i < 100);
}

DWORD WINAPI work_thread_c(LPVOID)
{
	INT i = 0;
	do
	{
		wprintf(L"message 2: %d\n", i);
	} while (++i < 100);
}
