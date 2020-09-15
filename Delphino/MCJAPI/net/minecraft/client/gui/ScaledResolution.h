#pragma once
#include <jni.h>
#include "../../../../../Utils/Utils.h"

class ScaledResolution : public _jobject
{
public:
	int getScaledWidth();
	int getScaledHeight();
	int getGuiScale();
};

