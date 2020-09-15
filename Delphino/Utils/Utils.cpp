#include "pch.h"
#include "Utils.h"

#ifndef hJNI_GetCreatedJavaVMs
typedef jint(*hJNI_GetCreatedJavaVMs)(JavaVM** vmBuf, jsize bufLen, jsize* nVMs);
hJNI_GetCreatedJavaVMs oJNI_GetCreatedJavaVMs;
#endif

jobject Utils::getClassLoader(JNIEnv* env)
{
	jclass launch = env->FindClass("net/minecraft/launchwrapper/Launch");
	jfieldID sfid = env->GetStaticFieldID(launch, "classLoader", "Lnet/minecraft/launchwrapper/LaunchClassLoader;");
	jobject classLoader = env->GetStaticObjectField(launch, sfid);

	return classLoader;
}

jclass Utils::getObject(JNIEnv* env, const char* className)
{
	jstring name = env->NewStringUTF(className);
	jobject classLoader = getClassLoader(env);
	jmethodID mid = env->GetMethodID(env->GetObjectClass(classLoader), "findClass", "(Ljava/lang/String;)Ljava/lang/Class;");
	return (jclass)env->CallObjectMethod(classLoader, mid, name);
	env->DeleteLocalRef(name);
}

Minecraft* Utils::getMC()
{
	JNIEnv* env = Utils::getJNI();
	jclass mcClass = Utils::getObject(env, "net.minecraft.client.Minecraft");
	jmethodID smid = env->GetStaticMethodID(mcClass, "func_71410_x", "()Lnet/minecraft/client/Minecraft;");
	_jobject* mcjobj = env->CallStaticObjectMethod(mcClass, smid);
	return (Minecraft*)mcjobj;
}

JNIEnv* Utils::getJNI()
{
	JavaVM* jvm;
	JNIEnv* jenv;

	HMODULE jvmHandle = GetModuleHandleA("jvm.dll");
	hJNI_GetCreatedJavaVMs oJNI_GetCreatedJavaVMs = (hJNI_GetCreatedJavaVMs)GetProcAddress(jvmHandle, "JNI_GetCreatedJavaVMs");
	oJNI_GetCreatedJavaVMs(&jvm, 1, nullptr);
	jvm->AttachCurrentThread((void**)&jenv, NULL);
	return jenv;
}
