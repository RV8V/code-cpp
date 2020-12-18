/*
#pragma once

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
	static LRESULT CALLBACK application_proced(HWND, UINT, LPARAM, WPARAM);
	LRESULT CALLBACK window_proced(HWND, UINT, LPARAM, WPARAM);

	void create_control_elements();

private:
	const wstring app_name{ L"bin-value-viewer" }, class_name{ L"window-class" };
	const int window_height{ 350 }, window_length{ 250 };
	HWND member_hwnd{}, member_hwnd_button{}, member_hwnd_edit{};
};
*/