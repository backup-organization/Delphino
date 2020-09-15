#include "pch.h"
#include "ScaledResolution.h"
#include <iostream>

int ScaledResolution::getScaledWidth()
{
    JNIEnv* env = Utils::getJNI();
    jmethodID scaleWidField = env->GetMethodID(env->GetObjectClass(this), "func_78326_a", "()I");
    return env->CallIntMethod(this, scaleWidField);
}

int ScaledResolution::getScaledHeight()
{
    JNIEnv* env = Utils::getJNI();
    jmethodID scaleHeightField = env->GetMethodID(env->GetObjectClass(this), "func_78328_b", "()I");
    return env->CallIntMethod(this, scaleHeightField);
}

int ScaledResolution::getGuiScale()
{
    JNIEnv* env = Utils::getJNI();
    jmethodID scaleMethod = env->GetMethodID(env->GetObjectClass(this), "func_78325_e", "()I");
    return env->CallIntMethod(this, scaleMethod);
}
