#include <Windows.h>
#include <stdlib.h>

#define FILE_MENU_NEW 1
#define FILE_MENU_OPEN 2
#define FILE_MENU_EXIT 3
#define CHANGE_TITLE 4
#define CHANGE_TITLE_VIA_BUTTON 5
#define GENERATE_BUTTON 6
#define ID_DIALOGBOX 7

#define INPUT_TEXT_SIZE 100
#define NAME_SIZE 30
#define AGE_SIZE 10
#define OUT_SIZE 50

LRESULT CALLBACK windowProcedure(HWND, UINT, WPARAM, LPARAM);

VOID addMenus(HWND);
VOID addControls(HWND);

VOID addControls_app(HWND);
VOID loadImages();
VOID registerDialogClass(HINSTANCE);
VOID displayDialog(HWND);

HMENU handle_menu;
HWND handle_edit, handle_main_window;
HBITMAP handle_image_load, handle_image_load_generate;

HWND handle_name, handle_age, handle_out, handle_image_logo;

LRESULT CALLBACK dialogProcedure(HWND, UINT, WPARAM, LPARAM);

INT CALLBACK wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, INT)
{
	WNDCLASSW wc = { 0 };
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hInstance = hInstance;
	wc.lpszClassName = L"myclassname";
	wc.lpfnWndProc = windowProcedure;

	if (!RegisterClassW(&wc))
		return -1;

	registerDialogClass(hInstance);

	handle_main_window = CreateWindowW(L"myclassname", L"windowname", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 500, 500, NULL, NULL, NULL, NULL);

	//MessageBoxW(NULL, L"HELLO", L"HI", MB_OK);

	MSG msg = { 0 };
	while (GetMessage(&msg, NULL, NULL, NULL))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}

LRESULT CALLBACK windowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	INT value;
	switch (msg)
	{
		case WM_CREATE:
			loadImages();
			addMenus(hWnd);
			addControls_app(hWnd);
		return 0;

		case WM_COMMAND:
			switch (wp)
			{
				case FILE_MENU_NEW:
					displayDialog(hWnd);
					MessageBeep(MB_ICONINFORMATION);
				return 0;

				case CHANGE_TITLE:
					wchar_t text[INPUT_TEXT_SIZE];
					GetWindowTextW(handle_edit, text, INPUT_TEXT_SIZE);
					SetWindowTextW(hWnd, text);
				return 0;

				case CHANGE_TITLE_VIA_BUTTON:
					wchar_t input_text[INPUT_TEXT_SIZE];
					GetWindowTextW(handle_edit, input_text, INPUT_TEXT_SIZE);
					SetWindowTextW(hWnd, input_text);
				return 0;

				case GENERATE_BUTTON:
					char name[NAME_SIZE], age[AGE_SIZE], out[OUT_SIZE];
					GetWindowTextA(handle_name, name, NAME_SIZE);
					GetWindowTextA(handle_age, age, AGE_SIZE);

					if (strcmp(name, "") == 0 || strcmp(age, "") == 0)
					{
						value = MessageBoxW(hWnd, L"You did not enter name or age", NULL, MB_ABORTRETRYIGNORE);
						switch (value)
						{
							case IDABORT:
								DestroyWindow(hWnd);
							return 0;

							case IDRETRY:
							return 0;

							case IDIGNORE:
							break;
						}
					}

					strcpy_s(out, name);
					strcat_s(out, " is ");
					strcat_s(out, age);
					strcat_s(out, " years old");

					SetWindowTextA(handle_out, out);
				return 0;

				case FILE_MENU_EXIT:
					value = MessageBoxW(hWnd, L"Are you sure?", L"Wait!", MB_YESNO | MB_ICONEXCLAMATION | MB_ICONERROR);
					if (value == IDYES)
						DestroyWindow(hWnd);

					else if (value == IDNO)
					{
					}
				return 0;
			}
		return 0;

		case WM_DESTROY:
			PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, msg, wp, lp);
}

VOID addMenus(HWND hWnd)
{
	handle_menu = CreateMenu();
	HMENU handle_file_menu = CreateMenu();
	HMENU handle_submenu = CreateMenu();

	AppendMenu(handle_submenu, MF_STRING, CHANGE_TITLE, "change title");

	AppendMenu(handle_file_menu, MF_STRING, FILE_MENU_NEW, "new");
	AppendMenu(handle_file_menu, MF_POPUP, (UINT)handle_submenu, "open submenu");
	AppendMenu(handle_file_menu, MF_SEPARATOR, NULL, NULL);
	AppendMenu(handle_file_menu, MF_STRING, FILE_MENU_EXIT, "exit");

	AppendMenu(handle_menu, MF_POPUP, (UINT_PTR)handle_file_menu, "File");
	AppendMenu(handle_menu, MF_STRING, NULL, "Help");

	SetMenu(hWnd, handle_menu);
}

VOID addControls(HWND hWnd)
{
	CreateWindowW(L"static", L"Enter text here:", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 200, 100, 100, 50, hWnd, NULL, NULL, NULL);
	handle_edit = CreateWindowW(L"edit", L"...", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL, 200, 152, 100, 50, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"button", L"change title via button click", WS_VISIBLE | WS_CHILD, 200, 204, 100, 50, hWnd, (HMENU)CHANGE_TITLE_VIA_BUTTON, NULL, NULL);
}

VOID addControls_app(HWND hWnd)
{
	CreateWindowW(L"static", L"name: ", WS_VISIBLE | WS_CHILD, 100, 50, 98, 38, hWnd, NULL, NULL, NULL);
	handle_name = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 200, 50, 98, 38, hWnd, NULL, NULL, NULL);

	CreateWindowW(L"static", L"age: ", WS_VISIBLE | WS_CHILD, 100, 90, 98, 38, hWnd, NULL, NULL, NULL);
	handle_age = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 200, 90, 98, 38, hWnd, NULL, NULL, NULL);

	HWND handle_button = CreateWindowW(L"button", L"generate", WS_VISIBLE | WS_CHILD | BS_BITMAP, 150, 140, 98, 38, hWnd, (HMENU)GENERATE_BUTTON, NULL, NULL);
	SendMessageW(handle_button, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)handle_image_load_generate);

	handle_out = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 100, 200, 300, 200, hWnd, NULL, NULL, NULL);
	handle_image_logo = CreateWindowW(L"static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, 350, 60, 100, 100, hWnd, NULL, NULL, NULL);
	SendMessageW(handle_image_logo, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)handle_image_load);
}

VOID loadImages()
{
	handle_image_load = (HBITMAP)LoadImageW(NULL, L" C:\\Users\\Administrator\\source\\repos\\pentamollis\\pentamollis\\IMAGE_LAND2.BMP", IMAGE_BITMAP, 100, 100, LR_LOADFROMFILE);
	handle_image_load_generate = (HBITMAP)LoadImageW(NULL, L" C:\\Users\\Administrator\\source\\repos\\pentamollis\\pentamollis\\GENERATE_LAND2.BMP", IMAGE_BITMAP, 100, 100, LR_LOADFROMFILE);
}

LRESULT CALLBACK dialogProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
		case WM_COMMAND:
			switch (wp)
			{
				case ID_DIALOGBOX:
					EnableWindow(handle_main_window, TRUE);
					DestroyWindow(hWnd);
				return 0;
			}
		return 0;

		case WM_CLOSE:
			EnableWindow(handle_main_window, TRUE);
			DestroyWindow(hWnd);
		return 0;
	}
	return DefWindowProc(hWnd, msg, wp, lp);
}

VOID registerDialogClass(HINSTANCE hInstance)
{
	WNDCLASSW dialog = { 0 };
	dialog.hbrBackground = (HBRUSH)COLOR_WINDOW;
	dialog.hCursor = LoadCursor(NULL, IDC_CROSS);
	dialog.hInstance = hInstance;
	dialog.lpszClassName = L"mydialogclassname";
	dialog.lpfnWndProc = dialogProcedure;

	RegisterClassW(&dialog);
}

VOID displayDialog(HWND hWnd)
{
	HWND handle_dialog = CreateWindowW(L"mydialogclassname", L"dialog", WS_VISIBLE | WS_OVERLAPPEDWINDOW, 400, 400, 200, 200, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"button", L"close", WS_VISIBLE | WS_CHILD, 20, 20, 100, 40, handle_dialog, (HMENU)ID_DIALOGBOX, NULL, NULL);
	EnableWindow(hWnd, FALSE);
}
