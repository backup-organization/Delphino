#include "pch.h"
#include "RenderUtils.h"
#include "Utils.h"
#include <MinHook.h>
#include <iostream>
#include <gl/GL.h>

using namespace std;

int RenderUtils::getGuiScale()
{
    return Utils::getMC()->getScaledResolution()->getGuiScale();
}

jobject RenderUtils::getFontRenderer()
{
    //Get the minecraft instance
    JNIEnv* jenv = Utils::getJNI();
    jobject mc = Utils::getMC();
    //Get the font renderer
    jfieldID fontRendererField = jenv->GetFieldID(jenv->GetObjectClass(mc), "field_71466_p", "Lnet/minecraft/client/gui/FontRenderer;");
    if (fontRendererField == NULL) {
        cout << "ERROR: Couldn't find font renderer!" << endl;
        return NULL;
    }
    return jenv->GetObjectField(mc, fontRendererField);
}

void RenderUtils::drawText(string text, float x, float y, int color, bool shadow)
{
    JNIEnv* jenv = Utils::getJNI();
    jobject fontRenderer = getFontRenderer();
    if (fontRenderer == NULL) {
        cout << "Coudn't draw text because fontRenderer was NULL!" << endl;
        return;
    }
    jmethodID drawText = jenv->GetMethodID(jenv->GetObjectClass(fontRenderer), "func_175065_a", "(Ljava/lang/String;FFIZ)I");

    jstring text_jstr = jenv->NewStringUTF(text.c_str());
    jfloat x_jfloat = x;
    jfloat y_jfloat = y;
    jint color_jint = color;
    jboolean shadow_jbool = shadow;

    jenv->CallIntMethod(fontRenderer, drawText, text_jstr, x_jfloat, y_jfloat, color_jint, shadow_jbool);
}

void RenderUtils::drawRect(Vector4f rect, Color color)
{
    RenderUtils::drawRect(rect.x,
        rect.y,
        rect.z,
        rect.w,
        color.x,
        color.y,
        color.z,
        color.w);
}

void RenderUtils::drawRect(float x, float y, float z, float w, float r, float g, float b, float a)
{
    //glPushMatrix();

    glBegin(GL_QUADS);
        glColor4f(r, g, b, a);
        glVertex2f(x, y);
        glVertex2f(z, y);
        glVertex2f(z, w);
        glVertex2f(x, w);
    glEnd();

    //glPopMatrix();
}




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

    //RenderUtils::drawRect(Vector4f(0, 10, 100, 40), Color(1.0f, 1.0f, 1.0f, 1.0f));

    glBegin(GL_QUADS);
    glLineWidth(10);
    glColor4f(1, 1, 1, 1);
    glVertex2f(0, 0);
    glVertex2f(100, 0);
    glVertex2f(100, 100);
    glVertex2f(0, 100);
    glEnd();

    /*int guiScale = RenderUtils::getGuiScale();
    glScalef(guiScale, guiScale, guiScale);
    RenderUtils::drawText("Delphino", 0, 10, 0xFFFFFFFF, true);*/

    glEnable(GL_DEPTH_TEST);

    glPopMatrix();


    return owglSwapLayerBuffers(hdc, uint);
}

bool RenderUtils::initRenderHook()
{
    HMODULE oGlHandle = GetModuleHandleA("OPENGL32.dll");
    FARPROC fp = GetProcAddress(oGlHandle, "wglSwapBuffers");

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

void RenderUtils::removeRenderHook()
{
    HMODULE oGlHandle = GetModuleHandleA("OPENGL32.dll");
    FARPROC fp = GetProcAddress(oGlHandle, "wglSwapBuffers");

    MH_DisableHook(fp);
}