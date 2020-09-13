// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include <jni.h>
#include <gl/GL.h>
#include <wingdi.h>
#include <MinHook.h>

using namespace std;

typedef jint(*hJNI_GetCreatedJavaVMs)(JavaVM** vmBuf, jsize bufLen, jsize* nVMs);
hJNI_GetCreatedJavaVMs oJNI_GetCreatedJavaVMs;

typedef BOOL (*type_wglSwapLayerBuffers)(HDC, UINT);
type_wglSwapLayerBuffers owglSwapLayerBuffers;

BOOL oglHook(HDC hdc, UINT uint) {
    cout << "Render!" << endl;

    glBegin(GL_LINES);
    glLineWidth(4);
    glVertex2f(0, 0);
    glVertex2f(100, 100);
    glEnd();

    //Sleep(100);

    return owglSwapLayerBuffers(hdc, uint);
}

JavaVM* jvm;
JNIEnv* jenv;

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
        HMODULE oGlHandle = GetModuleHandleA("OPENGL32.dll");
        FARPROC fp = GetProcAddress(oGlHandle, "wglSwapBuffers");

        if (MH_Initialize() == MH_OK) {
            cout << "Initialized MinHook" << endl;
            if (MH_CreateHook(fp, &oglHook, (LPVOID*)&owglSwapLayerBuffers) == MH_OK) {
                cout << "Created opengl hook!" << endl;
                if (MH_EnableHook(fp) == MH_OK) {
                    cout << "Enabled opengl hook!" << endl;
                }
                else {
                    cout << "Failed to enable opengl hook!" << endl;
                }
            }
            else {
                cout << "Failed to create opengl hook!" << endl;
            }
        }
        else {
            cout << "Failed to initialized MinHook!" << endl;
        }
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

