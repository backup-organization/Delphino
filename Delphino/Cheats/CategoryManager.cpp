#include "pch.h"
#include "CategoryManager.h"
#include "Hacks/TabGUI.h"

CategoryManager* instance;
CategoryManager::CategoryManager() : Manager<Category>("CategoryManager")
{

	Category* combat = new Category("Combat");
	combat->addItem(new TabGUI());
	this->addItem(combat);
	this->addItem(new Category("Movement"));

	instance = this;
}
CategoryManager* CategoryManager::getInstance() {
	return instance;
}