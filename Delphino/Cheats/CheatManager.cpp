#include "pch.h"
#include "CheatManager.h"

CheatManager* instance;
CheatManager::CheatManager() : Manager<Cheat>("CheatManager")
{
	instance = this;
}
CheatManager* CheatManager::getInstance() {
	return instance;
}