#pragma once
#include "../Utils/RenderUtils.h"
#include <Windows.h>
#include <MinHook.h>
#include <iostream>
#include <gl/GL.h>

class RenderHook
{
public:
	static bool installHook();
	static bool removeHook();
};

