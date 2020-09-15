#pragma once
#include <jni.h>
#include "../../../../Utils/Utils.h"
#include "settings/GameSettings.h"
#include "gui/ScaledResolution.h"

class Minecraft : public _jobject
{
public:
	class GameSettings* getGameSettings();
	class ScaledResolution* getScaledResolution();
};

