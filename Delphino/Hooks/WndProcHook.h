#pragma once
#include <Windows.h>
class WndProcHook
{
public:
	static void install();
	static void uninstall();
};

