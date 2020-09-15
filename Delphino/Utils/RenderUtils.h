#pragma once
#include <string>
#include <jni.h>
#include "Maths.h"

using namespace std;
class RenderUtils
{
public:
	static bool initRenderHook();
	static void removeRenderHook();

	static int getGuiScale();
	static jobject getFontRenderer();
	static void drawText(string text, float x, float y, int color, bool shadow);
	static void drawRect(Vector4f rect, Color color);
	static void drawRect(float x, float y, float wid, float height, float r, float g, float b, float a);
};

