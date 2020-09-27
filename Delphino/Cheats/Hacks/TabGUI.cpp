#include "pch.h"
#include "TabGUI.h"
#include "../../Utils/RenderUtils.h"
#include <iostream>
#include <gl/GL.h>

using namespace std;

TabGUI* instance;
void onRender() 
{
	if (instance->enabled) {
		glPushMatrix();
		float guiScale = RenderUtils::getGuiScale();
		glScalef(guiScale*2, guiScale*2, guiScale*2);
		int textWid = RenderUtils::measureText("Delphino");
		RenderUtils::drawRect(Vector4f(0, 5, textWid, 10), Color(1, 1, 1, .5));
		RenderUtils::drawText("Delphino", 0, 5, 0xFFFFFFFF, true);
		glPopMatrix();
		glPushMatrix();
		glScalef(guiScale, guiScale, guiScale);
		glPopMatrix();
	}
}

TabGUI::TabGUI() : Cheat("TabGUI")
{
	instance = this;
	RenderUtils::onRender(&onRender);
	cout << "Instantiated TabGUI" << endl;
}
