#pragma once
#include <jni.h>
#include "../../../../../Utils/Utils.h"

class ScaledResolution : public _jobject
{
public:
	int getScaledWidth() {
		JNIEnv* env = Utils::getJNI();
		jmethodID scaleWidField = env->GetMethodID(env->GetObjectClass(this), "func_78326_a", "()I");
		return env->CallIntMethod(this, scaleWidField);
	}
	int getScaledHeight() {
		JNIEnv* env = Utils::getJNI();
		jmethodID scaleHeightField = env->GetMethodID(env->GetObjectClass(this), "func_78328_b", "()I");
		return env->CallIntMethod(this, scaleHeightField);
	}
	int getGuiScale() {
		JNIEnv* env = Utils::getJNI();
		jmethodID scaleMethod = env->GetMethodID(env->GetObjectClass(this), "func_78325_e", "()I");
		return env->CallIntMethod(this, scaleMethod);
	}
};

