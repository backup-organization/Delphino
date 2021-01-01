#pragma once
#include <iostream>
#include <string>
#include "../Cheats/CategoryManager.h"

class WndProcHook
{
public:
	static bool installHook();
	static bool removeHook();
};

