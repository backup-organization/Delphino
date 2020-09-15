#pragma once
#include <string>
using namespace std;
class ManagedItem {
	string name;
public:
	ManagedItem(string name) {
		this->name = name;
	}
	string getName() {
		return this->name;
	}
};