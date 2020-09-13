// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include <jni.h>
#include <gl/GL.h>

typedef jint(*hJNI_GetCreatedJavaVMs)(JavaVM** vmBuf, jsize bufLen, jsize* nVMs);
hJNI_GetCreatedJavaVMs oJNI_GetCreatedJavaVMs;

JavaVM* jvm;
JNIEnv* jenv;

using namespace std;

int __stdcall StartDelphino() {
    MessageBoxA(nullptr, "Delphino has injected!", "DELPHINO", MB_OK);

    FreeConsole();
    AllocConsole();
    SetConsoleTitleA("Delphino Console");
    freopen("CONOUT$", "w", stdout);
    freopen("CONIN$", "r", stdin);
    freopen("CONOUT$", "w", stderr);

    cout << "Delphino is injected!" << endl;

    HMODULE jvmHandle = GetModuleHandleA("jvm.dll");
    hJNI_GetCreatedJavaVMs oJNI_GetCreatedJavaVMs = (hJNI_GetCreatedJavaVMs)GetProcAddress(jvmHandle, "JNI_GetCreatedJavaVMs");
    oJNI_GetCreatedJavaVMs(&jvm, 1, nullptr);
    jvm->AttachCurrentThread((void**)&jenv, NULL);

    if (jenv != nullptr) {
        cout << "Found JVM & JEnv!" << endl;




    }
    else {
        cout << "Failed to find JVM & JEnv!" << endl;
    }

    return 1;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)StartDelphino, hModule, NULL, NULL);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

