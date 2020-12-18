#include <Windows.h>
#include <stdlib.h>
#pragma warning(disable  : 4996)

#define FILE_MENU_NEW 1
#define FILE_MENU_OPEN 2
#define FILE_MENU_EXIT 3
#define CHANGE_TITLE 4
#define CHANGE_TITLE_BUTTON 5
#define GENERATE_BUTTON 6

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK DialogProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);

void registerDialogClass(HINSTANCE hInstance);

void AddMenus(HWND);
void AddControls(HWND);
void displayDialog(HWND);

HWND hName, hAge, hOut;
HMENU hMenu;
//HWND hEdit;

INT CALLBACK wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, INT)
{
	//MessageBox(NULL, "HELLO", "My first GUI", MB_OK);
	WNDCLASSW wc = { 0 };

	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hInstance = hInstance;
	wc.lpszClassName = L"myWindowClass";
	wc.lpfnWndProc = WindowProcedure;

	if (!RegisterClassW(&wc))
	{
		return -1;
	}

	registerDialogClass(hInstance);

	CreateWindowW(L"myWindowClass", L"My Window", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 500, 500,
		          NULL, NULL, NULL, NULL);

	MSG msg = { 0 };

	while (GetMessage(&msg, NULL, NULL, NULL))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	int value;
	switch (msg)
	{
	case WM_COMMAND:

		switch (wp)
		{

		/*case 1:
			MessageBeep(MB_OK);
			break;*/

		case FILE_MENU_EXIT:
			value = MessageBoxW(hWnd, L"Are you sure?", L"Wait", MB_YESNO);
			if (value == IDYES)
			{
				DestroyWindow(hWnd);
			}

			else if (value == IDNO)
			{

			}
			break;

		case FILE_MENU_NEW:
			displayDialog(hWnd);
			MessageBeep(MB_ICONINFORMATION);
			break;

		/*case CHANGE_TITLE:

			wchar_t text[100];

			GetWindowTextW(hEdit, text, 100);

			SetWindowTextW(hWnd, text);
			break;

		case CHANGE_TITLE_BUTTON:

			wchar_t _text[100];

			GetWindowTextW(hEdit, _text, 100);

			SetWindowTextW(hWnd, _text);
			break;*/

		case GENERATE_BUTTON:

			char name[20], age[10], out[50];

			GetWindowText(hName, name, 20);
			GetWindowText(hAge, age, 10);

			if (strcmp(name, "") == 0 || strcmp(age, "") == 0)
			{
				value = MessageBoxW(hWnd, L"You did not enter anything!", NULL, MB_ABORTRETRYIGNORE);

				switch (value)
				{
				case IDABORT:
					DestroyWindow(hWnd);
					break;

				case IDRETRY:
					return 0;

				case IDIGNORE:
					break;
				}
			}

			strcpy(out, name);
			strcat(out, " is ");
			strcat(out, age);
			strcat(out, " years old");

			SetWindowText(hOut, out);

			break;
		}



		break;
	case WM_CREATE:
		displayDialog(hWnd);
		AddMenus(hWnd);
		AddControls(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProcW(hWnd, msg, wp, lp);
	}
}

void AddMenus(HWND hWnd)
{
	hMenu = CreateMenu();
	HMENU hFileMenu, hSubMenu;
	
	hFileMenu = CreateMenu();
	hSubMenu = CreateMenu();

	AppendMenu(hSubMenu, MF_STRING, CHANGE_TITLE, "Change Title");

	AppendMenu(hFileMenu, MF_STRING, FILE_MENU_NEW, "New");
	AppendMenu(hFileMenu, MF_POPUP, (UINT_PTR)hSubMenu, "Open SubMenu");
	AppendMenu(hFileMenu, MF_SEPARATOR, NULL, NULL);
	AppendMenu(hFileMenu, MF_STRING, FILE_MENU_EXIT, "Exit");

	AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, "File");
	AppendMenu(hMenu, MF_STRING, NULL, "Help");

	SetMenu(hWnd, hMenu);
}

void AddControls(HWND hWnd)
{
	/*CreateWindowW(L"static", L"Enter text here: ", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 200, 100, 100, 50, hWnd,
		          NULL, NULL, NULL);
	hEdit = CreateWindowW(L"edit", L"...", WS_VISIBLE | WS_CHILD | ES_AUTOVSCROLL | ES_AUTOHSCROLL, 200, 152, 100, 50, hWnd,
		          NULL, NULL, NULL);
	CreateWindowW(L"button", L"Change Title", WS_VISIBLE | WS_CHILD, 200, 204, 100, 50, hWnd,
		          (HMENU)CHANGE_TITLE_BUTTON, NULL, NULL);*/

	CreateWindowW(L"Static", L"Name: ", WS_VISIBLE | WS_CHILD, 100, 50, 98, 38, hWnd, NULL, NULL, NULL);
	hName = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 200, 50, 98, 38, hWnd, NULL, NULL, NULL);

	CreateWindowW(L"Static", L"Age: ", WS_VISIBLE | WS_CHILD, 100, 90, 98, 38, hWnd, NULL, NULL, NULL);
	hAge = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 200, 90, 98, 38, hWnd, NULL, NULL, NULL);

	CreateWindowW(L"Button", L"Generate", WS_VISIBLE | WS_CHILD, 150, 140, 98, 38, hWnd, (HMENU)GENERATE_BUTTON, NULL, NULL);

	hOut = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 100, 200, 300, 200, hWnd, NULL, NULL, NULL);
}

LRESULT CALLBACK DialogProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_COMMAND:
		switch (wp)
		{
		case 1:
			DestroyWindow(hWnd);
			break;
		}
		break;
		
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	default:
		return DefWindowProc(hWnd, msg, wp, lp);
	}
}

void registerDialogClass(HINSTANCE hInstance)
{
	WNDCLASSW dialog = { 0 };

	dialog.hbrBackground = (HBRUSH)COLOR_WINDOW;
	dialog.hCursor = LoadCursor(NULL, IDC_CROSS);
	dialog.hInstance = hInstance;
	dialog.lpszClassName = L"myDialogClass";
	dialog.lpfnWndProc = DialogProcedure;

	RegisterClassW(&dialog);
}

void displayDialog(HWND hWnd)
{
	HWND hDialog = CreateWindowW(L"myDialogClass", L"Dialog", WS_VISIBLE | WS_OVERLAPPEDWINDOW, 400, 400, 200, 200,
		          hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Button", L"Close", WS_VISIBLE | WS_CHILD, 20, 20, 100, 40, hDialog, (HMENU)1, NULL, NULL);
}