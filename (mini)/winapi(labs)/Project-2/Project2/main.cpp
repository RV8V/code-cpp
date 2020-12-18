#include <Windows.h>
#include <string.h>
#include <malloc.h>

#define SIZE_BUFFER 255
#define PATH (LPCSTR)"C:/Users/Administrator/source/1"

FLOAT c_exception(FLOAT, FLOAT);
VOID infinity_cycle(VOID);
INT winapi_exception(INT);

INT __cdecl cdecl_call(VOID);
INT __fastcall fast_call(VOID);
INT __stdcall std_call(VOID);
INT __vectorcall vector_call(VOID);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR pCmdLine, int nCmdShow)
{
	INT i, j = 10; j = i;

	LPCSTR new_dir = "C:/Users/Administrator/source/2";
	LPCSTR move_dir = "C:/Users/Administrator/source/3";
	if (!CreateDirectory(new_dir, NULL))
		return 1;

	LPSTR str_temp = (LPSTR)calloc(SIZE_BUFFER + 1, sizeof(WCHAR));
	DWORD value = GetCurrentDirectory(SIZE_BUFFER, str_temp);
	if (!SetCurrentDirectory(PATH))
		return 2;
	GetCurrentDirectory(SIZE_BUFFER, str_temp);

	if (!MoveFile(new_dir, move_dir))
		return 3;
	if (!RemoveDirectory(move_dir))
		return 4;

	value = GetSystemDirectory(str_temp, SIZE_BUFFER);
	value = GetSystemWindowsDirectory(str_temp, SIZE_BUFFER);
	value = GetWindowsDirectory(str_temp, SIZE_BUFFER);
	value = GetSystemWow64Directory(str_temp, SIZE_BUFFER);

	LPSTR c_string = (LPSTR)"hello world";
	const char* c_str = "hello world";
	LPWSTR w_string = (LPWSTR)L"hello world";
	const wchar_t* w_str = (wchar_t*)L"hello world";
	LPTSTR t_string = (LPTSTR)"hello world";

	CHAR ch = 0;
	WCHAR wh = 0;
	TCHAR th = 0;
	BOOL b = 0;
	BOOLEAN b_true = 0;
	BYTE byte = 0;
	INT i = 0;
	UINT ui = 0;
	DWORD dw = 0;
	FLOAT f = 0.;
	LPVOID ptr = NULL;
	PVOID p_void = nullptr;
	HANDLE h = NULL;

	INT WideCharToMultiByte(
		UINT                               CodePage,
		DWORD                              dwFlags,
		_In_NLS_string_(cchWideChar)LPCWCH lpWideCharStr,
		INT                                cchWideChar,
		LPSTR                              lpMultiByteStr,
		INT                                cbMultiByte
	);

	LPCWSTR LPWSTR_TMP = L"test message";
	INT size_str = wcslen(LPWSTR_TMP) + 1;
	LPSTR lpStr_tmp = (PCHAR)calloc(size_str, sizeof(CHAR));

	DWORD result = WideCharToMultiByte(
		CP_ACP,
		WC_NO_BEST_FIT_CHARS,
		LPWSTR_TMP,
		INFINITE,
		lpStr_tmp,
		size_str
	);

	INT MultiByteToWideChar(
		             _In_      UINT   CodePage,
		             _In_      DWORD  dwFlags,
		             _In_      LPCSTR lpMultiByteStr,
		             _In_      INT    cbMultiByte,
		             _Out_opt_ LPWSTR lpWideCharStr,
		             _In_      INT    cchWideChar,
	  );

	LPCSTR LPCSTR_TEST = "test message";
	DWORD size_string = strlen(LPCSTR_TEST) + 1;
	LPWSTR lpWstr_tmp = (LPWSTR)calloc(size_string, sizeof(WCHAR));

	DWORD res = (DWORD)MultiByteToWideChar(
	    CP_ACP,
	    MB_PRECOMPOSED,
	    LPCSTR_TEST,
	    INFINITE,
	    lpWstr_tmp,
	    size_string
	);

	LPCWSTR PATH = (const WCHAR*)L"C:/Users/Administrator/Documents/file.txt";

	HANDLE hFile = CreateFileW(
	    PATH,
		GENERIC_READ | GENERIC_WRITE,
		NULL,
		NULL,
		OPEN_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);

	CloseHandle(hFile);
	return 0;
}

FLOAT c_exception(FLOAT v1, FLOAT v2)
{
	if (v2 == 0)
		goto div_zero;
	return v1 / v2;
div_zero:
	return 0.;
}

VOID infinity_cycle(VOID)
{
	CHAR i = 0;
	while (i++)
	{
		if (i >= 100)
			goto end;
	}
end:
	return;
}

INT winapi_exception(INT index)
{
	CHAR* p_ch = NULL;
	__try
	{
		return *(p_ch + index);
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		return 0;
	}
}