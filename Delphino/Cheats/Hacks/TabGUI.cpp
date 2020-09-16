#include "pch.h"
#include "TabGUI.h"
#include "../../Utils/RenderUtils.h"


TabGUI* instance;
void onRender() 
{
	if (instance->enabled) {
		RenderUtils::drawText("Delphino", 0, 10, 0xFFFFFFFF, true);
	}
}

TabGUI::TabGUI() : Cheat("TabGUI")
{
	instance = this;
	RenderUtils::onRender(&onRender);
}
