#include "pch.h"
#include "WndProcHook.h"

using namespace std;

WNDPROC oriWndProc;
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_KEYDOWN:
		CategoryManager* cats = CategoryManager::getInstance();
		for (int i = 0; i < cats->getItems()->size(); i++) {
			Category* cat = cats->getItems()->at(i);
			for (int c = 0; c < cat->getItems()->size(); c++) {
				Cheat* cheat = cat->getItems()->at(c);
				cheat->onKey(wParam);
			}
		}
		break;
	}
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
bool WndProcHook::installHook()
{
	EnumWindows(EnumWindowsProc, 0);
	if (window != nullptr) {
		oriWndProc = (WNDPROC)SetWindowLongPtrA(window, -4, (LONG_PTR)&WndProc);
		char wnd_title[MAX_PATH];
		GetWindowTextA(window, wnd_title, MAX_PATH);
		cout << "Hooked window with title: " << wnd_title << endl;
		return true;
	}
	else {
		cout << "Failed to hook wndProc! (Unknown Window)" << endl;
		return false;
	}
}

bool WndProcHook::removeHook()
{
	SetWindowLongPtr(window, -4, (LONG)(LONG_PTR)oriWndProc);
	return true;
}
