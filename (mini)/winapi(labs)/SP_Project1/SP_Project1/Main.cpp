#include <Windows.h>

INT CALLBACK wWinMain(HINSTANCE hInstance, HINSTANCE prehInstance, PWSTR args, INT show)
{
	MSG msg{};
	HWND hwnd;
	WNDCLASSEX wc{ sizeof(WNDCLASSEX) };

	wc.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.lpfnWndProc = [](HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) -> LRESULT
	{
		/*switch (uMsg)
		{
			case WM_DESTROY:
			{
				PostQuitMessage(EXIT_SUCCESS);
			}
			return 0;
		}*/
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	};
	wc.lpszClassName = "MyAppClassName";
	wc.lpszMenuName = nullptr;
	wc.style = CS_VREDRAW | CS_HREDRAW;

	if (!RegisterClassEx(&wc))
	{
		return EXIT_FAILURE;
	}

	if (hwnd = CreateWindow(wc.lpszClassName, "Title", WS_OVERLAPPEDWINDOW, 0, 0, 600, 600, nullptr, nullptr, wc.hInstance, nullptr); hwnd == INVALID_HANDLE_VALUE)
	{
		return EXIT_FAILURE;
	}

	ShowWindow(hwnd, show);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return static_cast<int>(msg.wParam); //reinterpret_cast<int>(msg.wParam);
}