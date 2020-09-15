#pragma once
#include <jni.h>
#include "../../../../../Utils/Utils.h"

class GameSettings : public _jobject
{
public:
	int get_guiScale();
};

