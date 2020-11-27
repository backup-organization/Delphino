#include "pch.h"
#include "ImGuiHook.h"
#include <iostream>
#include "../ImGUI/imgui.h"
#include "../ImGUI/imgui_impl_win32.h"
#include <gl/GL.h>

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

WNDPROC oriWndProc;
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	using namespace std;
	if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam) && GetAsyncKeyState(VK_NUMPAD1) == 1)
	{
		//std::cout << "Called New Handler" << std::endl;
		return 1;
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
void ImGuiHook::install()
{
	using namespace std;
	EnumWindows(EnumWindowsProc, 0);
	if (window != nullptr) {
		oriWndProc = (WNDPROC)SetWindowLongPtrA(window, -4, (LONG_PTR)&WndProc);
		char wnd_title[MAX_PATH];
		GetWindowTextA(window, wnd_title, MAX_PATH);
		cout << "Hooked window with title: " << wnd_title << endl;
	}
	else {
		cout << "Failed to hook wndProc! (Unknown Window)" << endl;
	}

	cout << "Starting IMGUI" << endl;
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::SetCurrentContext(ImGui::CreateContext());
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
	//io.ConfigViewportsNoAutoMerge = true;
	//io.ConfigViewportsNoTaskBarIcon = true;

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}
	// Setup Platform/Renderer backends
	ImGui_ImplWin32_Init(window);
}
void ImGuiHook::uninstall() {
	SetWindowLongPtr(window, -4, (LONG)(LONG_PTR)oriWndProc);
}