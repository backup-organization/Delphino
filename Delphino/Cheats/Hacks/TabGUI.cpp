#include "pch.h"
#include "TabGUI.h"
#include "../../Utils/RenderUtils.h"
#include <iostream>
#include <gl/GL.h>
#include "../CategoryManager.h"

using namespace std;

TabGUI* instance;
void onRender() 
{
	if (instance->enabled) {
		vector<Category*>* categories = CategoryManager::getInstance()->getItems();

		glPushMatrix();
		float guiScale = RenderUtils::getGuiScale();
		glScalef(guiScale*2, guiScale*2, guiScale*2);
		int textWid = RenderUtils::measureText("Delphino");
		RenderUtils::drawRect(Vector4f(0, 5, textWid, 10+(categories->size()*5)), Color(0, 0, 0, .4));
		RenderUtils::drawText("Delphino", 0, 5, 0xFFFFFFFF, true);
		glPopMatrix();
		glPushMatrix();
		glScalef(guiScale, guiScale, guiScale);
		for (int i = 0; i < categories->size(); i++) {
			Category* category = categories->at(i);
			string name = category->getName();
			float y = 30 + (i * 10);
			int nameWid = RenderUtils::measureText(name);
			RenderUtils::drawRect(Vector4f(0, 0, 100, 9), Color(1, 1, 1, .3));
			RenderUtils::drawText(name, 0, y, 0xFFFFFFFF, true);
		}
		glPopMatrix();
	}
}

TabGUI::TabGUI() : Cheat("TabGUI")
{
	instance = this;
	RenderUtils::onRender(&onRender);
	cout << "Instantiated TabGUI" << endl;
}
