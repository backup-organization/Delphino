#include "pch.h"
#include "WndProcHook.h"
#include <iostream>

WNDPROC oriWndProc;
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	using namespace std;
	cout << uMsg << endl;
	return CallWindowProc(oriWndProc, hWnd, uMsg, wParam, lParam);
}


HWND window;
BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
	using namespace std;
	if (IsWindowVisible(hwnd)) // check whether window is visible
	{
		char wnd_title[256];
		GetWindowTextA(hwnd, wnd_title, sizeof(wnd_title));
		string title = wnd_title;
		if (title.find("Minecraft") != string::npos) {
			cout << title << endl;
			window = hwnd;
			return false;
		}
	}
	return true;
}
void WndProcHook::install()
{
	using namespace std;
	EnumWindows(EnumWindowsProc, 0);
	if (window != nullptr) {
		oriWndProc = (WNDPROC)SetWindowLongPtr(window, -4, (LONG)(LONG_PTR)WndProc);
		char wnd_title[MAX_PATH];
		GetWindowTextA(window, wnd_title, MAX_PATH);
		cout << "Hooked window with title: " << wnd_title << endl;
	}
	else {
		cout << "Failed to hook wndProc! (Unknown Window)" << endl;
	}
}
void WndProcHook::uninstall() {
	SetWindowLongPtr(window, -4, (LONG)(LONG_PTR)oriWndProc);
}