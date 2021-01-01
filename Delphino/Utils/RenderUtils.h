#pragma once
#include <string>
#include <jni.h>
#include "Maths.h"
#include <functional>
#include <vector>

using namespace std;
class RenderUtils
{
public:
	static vector<void(*)()> callbacks;

	static void onRender(void(*func)());

	static int getGuiScale();
	static jobject getFontRenderer();
	static int measureText(string text);
	static void drawText(string text, float x, float y, int color, bool shadow);
	static void drawRect(Vector4f rect, Color color);
	static void drawRect(float x, float y, float wid, float height, float r, float g, float b, float a);
};

