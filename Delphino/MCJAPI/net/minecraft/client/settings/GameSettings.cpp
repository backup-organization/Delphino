#include "pch.h"
#include "GameSettings.h"

int GameSettings::get_guiScale()
{
    JNIEnv* env = Utils::getJNI();
    jfieldID guiScaleField = env->GetFieldID(env->GetObjectClass(this), "field_74335_Z", "I");
    return env->GetIntField(this, guiScaleField);
}
