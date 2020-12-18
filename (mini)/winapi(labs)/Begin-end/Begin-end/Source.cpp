#include <stdio.h>
#include <stdlib.h>

#define _WIN32_WINNT 0x0A00

#include <Windows.h>

#define ARR_SIZE 30

RECT arr[ARR_SIZE];
RECT client;
HWND button_2;
HWND static_text;
HWND list_combobox;

VOID FillArr(VOID);
VOID WinMove(VOID);
VOID WindShow(HDC);

VOID WinShow(HDC dc)
{
	HDC mem_dc = CreateCompatibleDC(dc);
	HBITMAP mem_bm = CreateCompatibleBitmap(dc, client.right - client.left, client.bottom - client.top);
	SelectObject(mem_dc, mem_bm);

		SelectObject(mem_dc, GetStockObject(DC_BRUSH));
		SetDCBrushColor(mem_dc, RGB(255, 255, 255));
		Rectangle(mem_dc, 0, 0, 640, 480);

		SelectObject(mem_dc, GetStockObject(DC_BRUSH));
		SetDCBrushColor(mem_dc, RGB(0, 255, 0));
		SelectObject(mem_dc, GetStockObject(DC_PEN));
		SetDCPenColor(mem_dc, RGB(255, 0, 0));

		for (int i = 0; i < ARR_SIZE; ++i)
			Rectangle(mem_dc, (arr + i)->left, (arr + i)->top, (arr + i)->right, (arr + i)->bottom);

	BitBlt(dc, 0, 0, client.right - client.left, client.bottom - client.top, mem_dc, 0, 0, SRCCOPY);
	DeleteDC(mem_dc);
	DeleteObject(mem_bm);
}

VOID FillArr()
{
	srand(5);
	for (int i = 0; i < ARR_SIZE; ++i)
	{
		(arr + i)->left = rand() % 300 - 50;
		(arr + i)->top = rand() % 200;
		(arr + i)->right = arr->left + 50;
		(arr + i)->bottom = arr->top + 100;
	}
}

VOID WinMove()
{
	for (int i = 0; i < ARR_SIZE; ++i)
	{
		(arr + i)->left += 3;
		if ((arr + i)->left > 700) (arr + i)->left = -100;
		(arr + i)->right = arr->left + 100;
		(arr + i)->bottom = arr->top + 100;
	}
}

LRESULT WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	printf("WNDPROC inside :: message -> %d, wParam -> %d\n", message, wparam);

	if (message == WM_DESTROY)
		PostQuitMessage(0);

	else if (message == WM_KEYDOWN)
		printf("code = %d\n", wparam);

	else if (message == WM_CHAR)
		printf("char = %c\n", wparam);

	else if (message == WM_MOUSEMOVE)
	{
		int xpos = LOWORD(lparam);
		int ypos = HIWORD(lparam);
		printf("mouse [%d, %d]\n", xpos, ypos);
	}

	else if (message == WM_SIZE)
		GetClientRect(hwnd, &client);

	else if (message == WM_COMMAND)
	{
		printf("WM_COMMAND\n");
		if ((LPARAM)button_2 == lparam)
			PostQuitMessage(0);

		if (LOWORD(wparam) == 10)
			printf("first button is processed\n");

		if (LOWORD(wparam) == 3)
		{
			int command_number = HIWORD(wparam);
			char c[100];

			GetWindowTextA((HWND)lparam, c, 100);
			if (command_number == EN_UPDATE)
			{
				printf("EN_UPDATE\n");
				SetWindowTextA(static_text, c);
			}

			if (command_number == EN_CHANGE)
				printf("EN_CHANGE\n");
		}

		if (LOWORD(wparam) == 4)
		{
			if (HIWORD(wparam) == CBN_SELCHANGE)
			{
				int id = SendMessage((HWND)lparam, CB_GETCURSEL, 0, 0);
				printf("id selected: %d", id);
			}
		}
	}

	else if (message == WM_LBUTTONDOWN)
		printf("move left button down\n");

	else return DefWindowProc(hwnd, message, wparam, lparam);
}

int main()
{
	WNDCLASSA wcl;
	     memset(&wcl, 0, sizeof(WNDCLASSA));
		 wcl.lpszClassName = "my window";
		 wcl.lpfnWndProc = (WNDPROC)WndProc;
	RegisterClassA(&wcl);

	HWND hWnd = CreateWindowA("my window", "window name", WS_OVERLAPPEDWINDOW, 10, 10, 640, 480, NULL, NULL, NULL, NULL);
	HDC dc = GetDC(hWnd);

	ShowWindow(hWnd, SW_SHOWNORMAL);

	HWND button = CreateWindowA("button", "quit", WS_VISIBLE | WS_CHILD, 10, 10, 100, 50, hWnd, (HMENU)10, NULL, NULL);

	button_2 = CreateWindowA("button", "quit second", WS_VISIBLE | WS_CHILD, 110, 10, 100, 50, hWnd, NULL, NULL, NULL);

	HWND edit = CreateWindowA("edit", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | ES_RIGHT | ES_NUMBER, 50, 80, 60, 20, hWnd, (HMENU)3, NULL, NULL);

	static_text = CreateWindowA("static", "NULL", WS_VISIBLE | WS_CHILD, 200, 80, 120, 20, hWnd, NULL, NULL, NULL);

    list_combobox = CreateWindowA("combobox", "NULL", WS_VISIBLE | WS_CHILD | CBS_DROPDOWN, 210, 10, 100, 150, hWnd, (HMENU)4, NULL, NULL);

	SendMessage(list_combobox, CB_ADDSTRING, 0, (LPARAM)"hello world");
	SendMessage(list_combobox, CB_ADDSTRING, 0, (LPARAM)"here is");
	SendMessage(list_combobox, CB_ADDSTRING, 0, (LPARAM)"test mode");
	SendMessage(list_combobox, CB_ADDSTRING, 0, (LPARAM)"not real maybe");

	FillArr();

	MSG msg;
	while (1)
	{
		if (PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_DESTROY)
				return 0;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			WinMove();
			WinShow(dc);
			Sleep(5);
		}
		printf("message -> %d, wParam -> %d\n", msg.message, msg.wParam);
		if (msg.message == 161 && msg.wParam == 20)
			return 0;
	}

	HWND handle_desktop = GetDesktopWindow();
	HWND handle_calcul = FindWindow(NULL, "calculator");
	HWND handle_console = GetConsoleWindow();

	LPPOINT p_point = (LPPOINT)malloc(sizeof(LPPOINT));
	LPRECT p_rect = (LPRECT)malloc(sizeof(LPRECT));

	GetClientRect(handle_console, p_rect);

	LPRECT p_screen = (LPRECT)malloc(sizeof(LPRECT));
	GetClientRect(GetDesktopWindow(), p_screen);

	do
	{
		system("cls");

		GetCursorPos(p_point);
		printf("\tglobal cursor position: %d, %d\n", p_point->x, p_point->y);

		ScreenToClient(handle_console, p_point);
		printf("\tlocal cursor position: %d, %d\n", p_point->x, p_point->y);

		printf("\tclient size of console: %d, %d\n", p_rect->right, p_rect->bottom);
		printf("\tclient size of screen: %d, %d\n", p_screen->right, p_screen->bottom);

		if (GetKeyState(VK_LBUTTON) < 0)
			printf("\nleft button was clicked");

		Sleep(100);

	} while (GetKeyState(VK_ESCAPE) >= 0);

	free(p_point); free(p_rect);

	HDC handle_device = GetDC(handle_console);

	int i = 0;
	char str[1024];

	do
	{
		i++;
		SelectObject(handle_device, GetStockObject(DC_BRUSH));
		SetDCBrushColor(handle_device, RGB(255, 255, 255));
		SelectObject(handle_device, GetStockObject(DC_PEN));
		SetDCPenColor(handle_device, RGB(255, 0, 255));
		Rectangle(handle_device, 0, 0, 640, 300);

		SelectObject(handle_device, GetStockObject(DC_BRUSH));
		SetDCBrushColor(handle_device, RGB(0, 255, 0));
		Rectangle(handle_device, 0 + i, 0, 100 + i, 100);

		sprintf_s(str, "some text is here");
		TextOutA(handle_device, 20, 50, str, strlen(str) + 1);

		Sleep(10);

	} while (GetKeyState(VK_ESCAPE) >= 0);

	SelectObject(handle_device, GetStockObject(DC_BRUSH));
	SetDCBrushColor(handle_device, RGB(255, 0, 255));

	Rectangle(handle_device, 10, 10, 110, 110);
	Ellipse(handle_device, 1000, 100, 1100, 200);

	system("pause");

	return 0;
}