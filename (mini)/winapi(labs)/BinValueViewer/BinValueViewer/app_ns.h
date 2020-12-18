#pragma once

#include <Windows.h>
#include <string.h>
#include <exception>
#include <algorithm>
#include <bitset>

#define APP_WIDTH 350
#define APP_HEIGHT 250

class c_app
{
	enum class CTL_ID
	{
		CALCBUTTON_ID,
		RESULTEDIT_ID
	};

public:
	explicit c_app(VOID);
	~c_app(VOID);
	INT run(VOID) CONST;

private:
	VOID init_native_window_obj(VOID);
	VOID create_native_controls(VOID);
	static LRESULT CALLBACK application_proc(HWND, UINT, WPARAM, LPARAM);
	LRESULT CALLBACK window_proc(HWND, UINT, WPARAM, LPARAM);

private:
	CONST std::wstring m_sz_appname{ L"Bin-W" }, m_sz_classname{ L"Bin-W_Window_class" };
	HWND m_hWnd{}, m_hWndButton{}, m_hWndEdit{};
	CONST INT m_app_width{ APP_WIDTH }, m_app_height{ APP_HEIGHT };
};