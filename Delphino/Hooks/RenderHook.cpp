#include "pch.h"
#include "RenderHook.h"

using namespace std;
typedef BOOL(*type_wglSwapLayerBuffers)(HDC, UINT);
type_wglSwapLayerBuffers owglSwapLayerBuffers;


BOOL oglHook(HDC hdc, UINT uint) {
    glPushMatrix();

    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    glViewport(0, 0, viewport[2], viewport[3]);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, viewport[2], viewport[3], 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glDisable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    for (auto&& fn : RenderUtils::callbacks)
        fn();

    glEnable(GL_DEPTH_TEST);

    glPopMatrix();


    return owglSwapLayerBuffers(hdc, uint);
}


bool RenderHook::installHook()
{
    HMODULE oGlHandle = GetModuleHandleA("OPENGL32.dll");
    FARPROC fp = GetProcAddress(oGlHandle, "wglSwapBuffers");

    RenderUtils::callbacks = vector<void(*)()>();

    if (MH_Initialize() == MH_OK) {
        cout << "Initialized MinHook" << endl;
        if (MH_CreateHook(fp, &oglHook, (LPVOID*)&owglSwapLayerBuffers) == MH_OK) {
            cout << "Created opengl hook!" << endl;
            if (MH_EnableHook(fp) == MH_OK) {
                cout << "Enabled opengl hook!" << endl;
                return true;
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
    return false;
}

bool RenderHook::removeHook()
{
    HMODULE oGlHandle = GetModuleHandleA("OPENGL32.dll");
    FARPROC fp = GetProcAddress(oGlHandle, "wglSwapBuffers");

    MH_DisableHook(fp);
    return true;
}