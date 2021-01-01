#include "pch.h"
#include "CategoryManager.h"
#include "Hacks/TabGUI.h"

CategoryManager* instance;
CategoryManager::CategoryManager() : Manager<Category>("CategoryManager")
{
	/*Combat*/
	Category* combat = new Category("Combat");
	this->addItem(combat);
	/*Movement*/
	Category* movement = new Category("Movement");
	this->addItem(movement);
	/*Render*/
	Category* render = new Category("Render");
	render->addItem(new TabGUI());
	this->addItem(render);

	instance = this;
}
CategoryManager* CategoryManager::getInstance() {
	return instance;
}