#pragma once
#include <jni.h>

using namespace std;

class Utils
{
public:
	static jobject getClassLoader(JNIEnv* env);
	static jclass getObject(JNIEnv* env, const char* className);
	static JNIEnv* getJNI();
	static class Minecraft* getMC();
};

