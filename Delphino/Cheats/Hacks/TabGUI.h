#pragma once
#include "../Cheat.h"

class TabGUI : public Cheat
{
public:
	TabGUI();
	void onKey(char key) override;
};

