#pragma once
#include "Manager.h"
#include "Cheat.h"

class Category : public Manager<Cheat>
{
public:
	Category(string name) : Manager<Cheat>(name){}
};

