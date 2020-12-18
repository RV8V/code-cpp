#include <Windows.h>
#include <stdio.h>
#include <Commdlg.h>

#pragma comment(lib, "comctl32.lib")
#pragma warning(disable : 4996)

#define OPEN_FILE_BUTTON 1
#define SAVE_FILE_BUTTON 2

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

void AddControls(HWND);
void open_file(HWND);

HWND HMainWindow, hEdit;

INT CALLBACK wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, INT)
{
	WNDCLASSW wc = { 0 };

	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WindowProcedure;
	wc.lpszClassName = L"myWindowClass";

	if (!RegisterClassW(&wc))
	{
		return -1;
	}

	HMainWindow = CreateWindowW(L"myWindowClass", L"My Window", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 500, 500,
		                        NULL, NULL, NULL, NULL);

	MSG msg = { 0 };

	while (GetMessage(&msg, NULL, NULL, NULL))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

void display_file(char* file_name)
{
	if (file_name == nullptr)
	{
		return;
	}

	FILE* file;
	file = fopen(file_name, "rb");
	fseek(file, 0, SEEK_END);
	int _size = ftell(file);
	rewind(file);
	char* data = new char[_size + 1];
	fread(data, _size, 1, file);
	data[_size] = '\0';

	SetWindowText(hEdit, data);

	fclose(file);
}

void open_file(HWND hWnd)
{
	OPENFILENAME ofn;

	char file_name[100];

	ZeroMemory(&ofn, sizeof(OPENFILENAME));

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hWnd;
	ofn.lpstrFile = file_name;
	ofn.lpstrFile = '\0';
	ofn.nMaxFile = 100;

    /*
	*
	* "All files\0*.*Source Files\0*.CPP\0Text Files\0*.TXT\0"
	*
	*/

	ofn.lpstrFilter = "All files\0*.*\0Source Files\0*.CPP\0Text Files\0*.TXT\0";
	ofn.nFilterIndex = 1;

	//MessageBoxW(NULL, L"enter", L"here", MB_OK);

	GetOpenFileName(&ofn);

	//MessageBox(NULL, ofn.lpstrFile, "", MB_OK);

	display_file(ofn.lpstrFile);
}

void write_file(char* path)
{
	if (path == nullptr)
	{
		return;
	}

	FILE* file;
	file = fopen(path, "w");

	int _size = GetWindowTextLength(hEdit);
	char* data = new char[_size + 1];
	GetWindowText(hEdit, data, _size + 1);

	fwrite(data, _size + 1, 1, file);
	fclose(file);
}

void save_file(HWND hWnd)
{
	OPENFILENAME ofn;

	char file_name[100];

	ZeroMemory(&ofn, sizeof(OPENFILENAME));

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hWnd;
	ofn.lpstrFile = file_name;
	ofn.lpstrFile = '\0';
	ofn.nMaxFile = 100;
	ofn.lpstrFilter = "All files\0*.*\0Source Files\0*.CPP\0Text Files\0*.TXT\0";
	ofn.nFilterIndex = 1;

	GetSaveFileName(&ofn);

	write_file(ofn.lpstrFile);
}

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{

	case WM_COMMAND:
		switch (wp)
		{
		case OPEN_FILE_BUTTON:
			open_file(hWnd);
			break;

		case SAVE_FILE_BUTTON:
			save_file(hWnd);
			break;
		}
		break;

	case WM_CREATE:
		AddControls(hWnd);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProcW(hWnd, msg, wp, lp);
	}
}

void AddControls(HWND hWnd)
{
	CreateWindowW(L"button", L"open", WS_VISIBLE | WS_CHILD, 10, 10, 150, 36,
		          hWnd, (HMENU)OPEN_FILE_BUTTON, NULL, NULL);

	CreateWindowW(L"button", L"save data", WS_VISIBLE | WS_CHILD, 170, 10, 150, 36,
		hWnd, (HMENU)SAVE_FILE_BUTTON, NULL, NULL);

	hEdit = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL, 10, 50, 400, 300,
		          hWnd, NULL, NULL, NULL);
}