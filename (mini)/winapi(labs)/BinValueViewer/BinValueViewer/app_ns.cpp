#include "app_ns.h"

c_app::c_app(VOID)
{
	using std::wstring;
	using std::string;

	try
	{
		this->init_native_window_obj();
		this->create_native_controls();
	}
	catch (CONST std::exception &ex)
	{
		string expt_data = ex.what();
		MessageBox(nullptr, wstring(begin(expt_data), end(expt_data)).c_str(), L"ERROR", MB_ICONERROR | MB_OK);
		ExitProcess(EXIT_FAILURE);
	}
}

c_app::~c_app()
{

}

INT c_app::run(VOID) CONST
{
	MSG _msg{};
	ShowWindow(this->m_hWnd, SW_SHOWDEFAULT);
	UpdateWindow(this->m_hWnd);
	while (GetMessage(&_msg, nullptr, 0, 0))
	{
		TranslateMessage(&_msg);
		DispatchMessage(&_msg);
	}
	return static_cast<INT>(_msg.wParam);
}

VOID c_app::init_native_window_obj(VOID)
{
	using std::runtime_error;
	using namespace std::string_literals;

	WNDCLASSEX _wc{ sizeof(WNDCLASSEX) };
	_wc.cbClsExtra = NULL;
	_wc.cbWndExtra = NULL;
	_wc.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	_wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	_wc.hIcon = LoadCursor(nullptr, IDI_APPLICATION);
	_wc.hIconSm = LoadCursor(nullptr, IDI_APPLICATION);
	_wc.hInstance = GetModuleHandle(nullptr);
	_wc.lpfnWndProc = c_app::application_proc;
	_wc.lpszClassName = this->m_sz_classname.c_str();
	_wc.lpszMenuName = nullptr;
	_wc.style = CS_VREDRAW | CS_HREDRAW;

	if (!RegisterClassEx(&_wc))
		throw runtime_error("Error, can't register main window class!"s);

	RECT _windowRC{ 0, 0, this->m_app_width, this->m_app_height };
	AdjustWindowRect(&_windowRC, WS_DLGFRAME | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZE, false);

	if (this->m_hWnd = CreateWindowEx(
		0,
		this->m_sz_classname.c_str(),
		this->m_sz_appname.c_str(),
		WS_DLGFRAME | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZE,
		(GetSystemMetrics(SM_CXSCREEN) - _windowRC.right) / 2,
		(GetSystemMetrics(SM_CYSCREEN) - _windowRC.bottom) / 2,
		_windowRC.right, _windowRC.bottom, nullptr, nullptr, nullptr, this
	); !this->m_hWnd)
		throw runtime_error("Error, can't create main window!"s);
}

LRESULT c_app::application_proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	c_app* p_app;
	if (uMsg == WM_CREATE)
	{
		p_app = static_cast<c_app*>(reinterpret_cast<CREATESTRUCT*>(lParam)->lpCreateParams);
		SetLastError(0);
		if (!SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(p_app)))
		{
			if (GetLastError() != 0)
				return FALSE;
		}
		else
		{
			p_app = reinterpret_cast<c_app*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
		}

		if (p_app != nullptr)
		{
			p_app->m_hWnd = hWnd;
			return p_app->window_proc(hWnd, uMsg, wParam, lParam);
		}
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
}

LRESULT c_app::window_proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_COMMAND:
		{
			switch (static_cast<c_app::CTL_ID>(LOWORD(wParam)))
			{
				case c_app::CTL_ID::CALCBUTTON_ID:
				{
					try
					{
						std::wstring text{};
						text.resize(MAX_PATH);
						GetWindowText(this->m_hWndEdit, &text[0], MAX_PATH);
						text.erase(remove(begin(text), end(text), 0), end(text));

						if (text.empty())
						{
							MessageBox(this->m_hWnd, L"Enter number", L"INFORMATION", MB_ICONINFORMATION | MB_OK);
							break;
						}

						std::string binary = std::bitset<16>(std::stoi(text)).to_string();
						text = std::wstring(begin(binary), end(binary));

						SetWindowText(this->m_hWndEdit, text.c_str());
					}
					catch (...)
					{
						MessageBox(this->m_hWnd, L"Number is more than 2 bytes!", L"WARNING!", MB_ICONWARNING | MB_OK);
					}
				}
				break;
			}
		}
		return 0;

		case WM_DESTROY:
		{
			PostQuitMessage(EXIT_SUCCESS);
		}
		return 0;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

VOID c_app::create_native_controls(VOID)
{
	using std::runtime_error;
	using namespace std::string_literals;

	if (this->m_hWndButton = CreateWindowEx(
		0,
		L"BUTTON",
		L"Convert",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		56, 100, 238, 37, this->m_hWnd, reinterpret_cast<HMENU>(c_app::CTL_ID::CALCBUTTON_ID), nullptr, nullptr
	); !this->m_hWndButton)
		throw runtime_error("Error, can't create button window!"s);

	if (this->m_hWndEdit = CreateWindowEx(
		0,
		L"EDIT",
		L"255",
		WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
		56, 66, 238, 24, this->m_hWnd, reinterpret_cast<HMENU>(c_app::CTL_ID::RESULTEDIT_ID), nullptr, nullptr
	); !this->m_hWndEdit)
		throw runtime_error("Error, can't create edit(input) window!"s);

	HFONT hFont = CreateFont(18, 0, 0, 0,
		FW_REGULAR, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH, L"Roboto");
	SendMessage(this->m_hWndEdit, WM_SETFONT, reinterpret_cast<WPARAM>(hFont), TRUE);
	SendMessage(this->m_hWndButton, WM_SETFONT, reinterpret_cast<WPARAM>(hFont), TRUE);
}