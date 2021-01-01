#pragma once
#include "ManagedItem.h"
class Cheat : public ManagedItem
{
	bool wasEnabled;
public:
	bool enabled;
	Cheat(string name) : ManagedItem(name) {};
	virtual void onEnable() {};
	virtual void onDisable() {};
	virtual void onTick() {};
	virtual void onKey(char key) {};
	void onLoop() {
		if (!enabled) {
			if (wasEnabled) {
				onDisable();
			}
		}
		else {
			if (!wasEnabled) {
				onEnable();
			}
			onTick();
		}
	}
};

