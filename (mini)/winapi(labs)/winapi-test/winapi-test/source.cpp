#include <Windows.h>

INT width{}, height{};

INT CALLBACK wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR	szCmdLine, INT nCmdShow)
{
	MSG msg{};
	HWND hwnd{};
	WNDCLASSEX wc{ sizeof(WNDCLASSEX) };
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hIcon = LoadCursor(nullptr, IDI_APPLICATION);
	wc.hIconSm = LoadCursor(nullptr, IDI_APPLICATION);
	wc.hInstance = hInstance;
	wc.lpfnWndProc = [](HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)->LRESULT
	{
		switch (uMsg)
		{
			case WM_CREATE:
			{
				HWND hButton = CreateWindow(
					L"BUTTON",
					L"OK!",
					WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
					0, 0, 300, 30, hWnd, reinterpret_cast<HMENU>(1337), nullptr, nullptr
				);

				HWND hButton_b = CreateWindow(
					L"BUTTON",
					L"OK!",
					WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
					0, 200, 300, 30, hWnd, reinterpret_cast<HMENU>(1339), nullptr, nullptr
				);
			}
			return 0;

			case WM_COMMAND:
			{
				switch (LOWORD(lParam))
				{
					case 1337:
					{
						MessageBox(hWnd, L"DO", L"NO", MB_ICONINFORMATION);
					}
					break;
				}
			}
			return 0;

			case WM_SIZE:
			{
				width = LOWORD(lParam);
				height = HIWORD(lParam);
			}
			return 0;

			case WM_DESTROY:
			{
				PostQuitMessage(EXIT_SUCCESS);
			}
			return 0;
		}
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	};
	wc.lpszClassName = L"MyAppClass";
	wc.lpszMenuName = nullptr;
	wc.style = CS_VREDRAW | CS_HREDRAW;

	if (!RegisterClassEx(&wc))
		return EXIT_FAILURE;

	if (hwnd = CreateWindow(wc.lpszClassName, L"Title", WS_OVERLAPPEDWINDOW, 0, 0, 600, 600, nullptr, nullptr, wc.hInstance, nullptr); hwnd == INVALID_HANDLE_VALUE)
		return EXIT_FAILURE;

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return static_cast<int>(msg.wParam);
}