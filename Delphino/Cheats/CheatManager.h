#pragma once

#include "Manager.h"
#include "Cheat.h"

class CheatManager : public Manager<Cheat>
{
public:
	CheatManager();
	static CheatManager* getInstance();
};

