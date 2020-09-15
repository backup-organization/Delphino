#include "pch.h"
#include "Minecraft.h"
#include <iostream>

GameSettings* Minecraft::getGameSettings()
{
	JNIEnv* env = Utils::getJNI();
	jfieldID settingsField = env->GetFieldID(env->GetObjectClass(this), "field_71474_y", "Lnet/minecraft/client/settings/GameSettings;");
	return (GameSettings*)env->GetObjectField(this, settingsField);
}

ScaledResolution* Minecraft::getScaledResolution()
{
	JNIEnv* env = Utils::getJNI();
	jclass srClass = Utils::getObject(env, "net.minecraft.client.gui.ScaledResolution");
	jmethodID srConst = env->GetMethodID(srClass, "<init>", "(Lnet/minecraft/client/Minecraft;)V");
	return (ScaledResolution*)env->NewObject(srClass, srConst, this);
}
