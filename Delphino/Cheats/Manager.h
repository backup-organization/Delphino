#pragma once
#include <vector>
#include "ManagedItem.h"

using namespace std;
template<class T>
class Manager : public ManagedItem {
	vector<T*>* items;
public:
	Manager<T>(string name) : ManagedItem(name) {
		items = new vector<T*>();
	}
	void addItem(T* item) {
		items->push_back(item);
	}
	void removeItem(int index) {
		items->erase(items->begin() + index);
	}
	vector<T*>* getItems() {
		return items;
	}
};