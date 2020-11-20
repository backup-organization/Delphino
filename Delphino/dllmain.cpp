// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <Windows.h>
#include <iostream>
#include <string>
#include "Utils/Utils.h"
#include "Utils/RenderUtils.h"
#include "Cheats/CategoryManager.h"
#include "Hooks/WndProcHook.h"
#include "MCJAPI/net/minecraft/client/Minecraft.h"

using namespace std;

int __stdcall StartDelphino(HMODULE thisModule) {
    //MessageBoxA(nullptr, "Delphino has injected! Click OK to execute the dll.", "DELPHINO", MB_OK);

    FreeConsole();
    AllocConsole();
    SetConsoleTitleA("Delphino Console");
    freopen("CONOUT$", "w", stdout);
    freopen("CONIN$", "r", stdin);
    freopen("CONOUT$", "w", stderr);
    cout << "Delphino is injected!" << endl;

    JNIEnv* jenv = Utils::getJNI();

    if (jenv != nullptr) {
        cout << "Found JVM & JEnv!" << endl;
        
        if (!RenderUtils::initRenderHook()) {
            cout << "Failed to create render hook!" << endl;
            return 1;
        }

        Minecraft* mc = Utils::getMC();
        cout << "Found Minecraft instance at: " << mc << endl;

        WndProcHook::install();
        cout << "Installed wndProc hook" << endl;
    }
    else {
        cout << "Failed to find JVM & JEnv!" << endl;
    }

    new CategoryManager();

    string line;
    while (true) {
        getline(cin, line);
        if (line == "detach") {
            RenderUtils::removeRenderHook();
            WndProcHook::uninstall();
            FreeConsole();
            FreeLibraryAndExitThread(thisModule, 0);
        }
    }

    return 0;
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

