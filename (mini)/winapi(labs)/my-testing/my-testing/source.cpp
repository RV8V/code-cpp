#pragma comment(lib, "Ws2_32.lib")

#include <Windows.h>
#include <string>
#include <algorithm>
#include <exception>
#include <bitset>

using namespace std;

class App
{
	enum class CONTROLS_IDS
	{
		CALCULATE_BUTTON_ID,
		RESULT_BUTTON_ID
	};

public:
	explicit App(VOID);
	~App(VOID);

	int run(VOID);

private:
	void init_initial_window_obj();
	static LRESULT CALLBACK application_proced(HWND, UINT, WPARAM, LPARAM);
	LRESULT CALLBACK window_proced(HWND, UINT, WPARAM, LPARAM);

	void create_control_elements();

private:
	const wstring app_name{L"bin-value-viewer" }, class_name{L"window-class" };
	const int window_height{ 350 }, window_length{ 250 };
	HWND member_hwnd{}, member_hwnd_button{}, member_hwnd_edit{};
};

App::App(VOID)
{
	using std::string;
	using std::wstring;
	using std::exception;
	try
	{
		this->init_initial_window_obj();
		this->create_control_elements();
	}
	catch (const exception& ex)
	{
		string message = ex.what();
		MessageBox(nullptr, std::wstring(begin(message), end(message)).c_str(), L"ERROR", MB_ICONERROR | MB_OK);
		ExitProcess(EXIT_FAILURE);
	}
}

App::~App(VOID)
{

}

void App::init_initial_window_obj()
{
	using std::runtime_error;
	using namespace std::string_literals;

	WNDCLASSEX _wc{ sizeof(WNDCLASSEX) };
	_wc.cbClsExtra = _wc.cbWndExtra = 0;
	_wc.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	_wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	_wc.hIcon = LoadCursor(nullptr, IDI_APPLICATION);
	_wc.hIconSm = LoadCursor(nullptr, IDI_APPLICATION);
	_wc.hInstance = GetModuleHandle(nullptr);
	_wc.lpfnWndProc = App::application_proced;
	_wc.lpszClassName = this->class_name.c_str();
	_wc.lpszMenuName = nullptr;
	_wc.style = CS_VREDRAW | CS_HREDRAW;

	if (!RegisterClassEx(&_wc))
		throw runtime_error("error while registering main window");

	RECT _window_rectang{ 0, 0, this->window_length, this->window_height };
	AdjustWindowRect(&_window_rectang, WS_OVERLAPPEDWINDOW, false);

	if (this->member_hwnd = CreateWindowEx(
		0,
		this->class_name.c_str(),
		this->app_name.c_str(),
		WS_DLGFRAME | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZE,
		(GetSystemMetrics(SM_CXSCREEN) - _window_rectang.right) / 2,
		(GetSystemMetrics(SM_CYSCREEN) - _window_rectang.bottom) / 2,
		_window_rectang.right, _window_rectang.bottom, nullptr, nullptr, nullptr, this
	); !this->member_hwnd)
		throw runtime_error("can not create main window handler");
}

void App::create_control_elements()
{
	using std::runtime_error;
	//ing std::string_literals;

	if (this->member_hwnd_button = CreateWindowEx(
		0,
		L"BUTTON",
		L"CONVERT",
		WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE,
		50, 100, 230, 37, this->member_hwnd, reinterpret_cast<HMENU>(App::CONTROLS_IDS::CALCULATE_BUTTON_ID), nullptr, nullptr
	); this->member_hwnd_button)
		throw runtime_error("cannot create button constol element");

	if (this->member_hwnd_edit = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		L"EDIT",
		L"256",
		WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
		56, 66, 230, 24, this->member_hwnd, reinterpret_cast<HMENU>(App::CONTROLS_IDS::RESULT_BUTTON_ID), nullptr, nullptr
	); this->member_hwnd_edit)
		throw runtime_error("can not create edit controll element");

	HFONT handle_font = CreateFont(10, 0, 0, 0, FW_REGULAR, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH,L"Roboto");
	SendMessage(this->member_hwnd_edit, WM_SETFONT, reinterpret_cast<WPARAM>(handle_font), TRUE);
	SendMessage(this->member_hwnd_button, WM_SETFONT, reinterpret_cast<WPARAM>(handle_font), TRUE);
}

int App::run(VOID)
{
	MSG msg{};
	ShowWindow(this->member_hwnd, SW_SHOWDEFAULT);
	UpdateWindow(this->member_hwnd);
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;//nterpret_cast<int>(msg.wParam);
}

LRESULT App::application_proced(HWND hWnd, UINT uMsg, WPARAM lParam, LPARAM wParam)
{
	App* app;
	if (uMsg == WM_NCCREATE) {
		
	app = static_cast<App*>(reinterpret_cast<CREATESTRUCT*>(lParam)->lpCreateParams);
		SetLastError(0);
		if (!SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(app)))
		{
			if (GetLastError() != 0)
				return false;
		}
		}
		else
			{
		app = reinterpret_cast<App*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
		}
	

	if(app)
	{
		app->member_hwnd = hWnd;
		return app->window_proced(hWnd, uMsg, lParam, wParam);
	}
	return DefWindowProc(hWnd, uMsg, lParam, wParam);
}

LRESULT App::window_proced(HWND hWnd, UINT uMsg, WPARAM lParam, LPARAM wParam)
{

	using std::wstring;
	using std::string;
	using std::bitset;
	using std::stoi;

	switch (uMsg)
	{
	case WM_COMMAND:
	{
		switch (static_cast<App::CONTROLS_IDS>(LOWORD(lParam)))
		{
		case App::CONTROLS_IDS::CALCULATE_BUTTON_ID:
		{
			try
			{
				wstring text{};
				text.resize(MAX_PATH);
				GetWindowText(this->member_hwnd_edit, &text[0], MAX_PATH);
				text.erase(remove(begin(text), end(text), 0), end(text));

				if (text.empty())
				{
					MessageBox(this->member_hwnd,L"Enter value",L"INFORMATION", MB_ICONWARNING | MB_OK);
					return 0;
				}

			//tring binary = bitset<16>(stoi(text)).to_string();
			//ext = wstring(begin(binary), end(binary));
				SetWindowText(this->member_hwnd_edit, text.c_str());
			}
			catch (...)
			{
				MessageBox(this->member_hwnd,L"Number is bigger than 2 bytes",L"WARNING", MB_ICONWARNING | MB_OK);
			}
		}
		return 0;
		}
	}
	return 0;

	case WM_DESTROY:
	{
		PostQuitMessage(EXIT_SUCCESS);
	}
	return 0;
	}
	return DefWindowProc(hWnd, uMsg, lParam, wParam);
}

INT CALLBACK wWinMain(HINSTANCE, HINSTANCE, PWSTR, INT) {
	App app{};
	return app.run();
}