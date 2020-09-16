#pragma once

#include "Manager.h"
#include "Category.h"

class CategoryManager : public Manager<Category>
{
public:
	CategoryManager();
	static CategoryManager* getInstance();
};

