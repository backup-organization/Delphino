#include "pch.h"
#include "RenderUtils.h"
#include "Utils.h"
#include <MinHook.h>
#include <iostream>
#include <gl/GL.h>
#include "../MCJAPI/net/minecraft/client/Minecraft.h"

using namespace std;

vector<void(*)()> RenderUtils::callbacks;

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

int RenderUtils::measureText(string text)
{
    JNIEnv* jenv = Utils::getJNI();
    jobject fontRenderer = getFontRenderer();
    if (fontRenderer == NULL) {
        cout << "Coudn't draw text because fontRenderer was NULL!" << endl;
        return 0.0f;
    }
    jmethodID measureText = jenv->GetMethodID(jenv->GetObjectClass(fontRenderer), "func_78256_a", "(Ljava/lang/String;)I");

    jstring text_jstr = jenv->NewStringUTF(text.c_str());

    return jenv->CallIntMethod(fontRenderer, measureText, text_jstr);
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
        rect.x+rect.z,
        rect.y+rect.w,
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
    glVertex2f(x, w);
    glVertex2f(z, w);
    glVertex2f(z, y);
    glEnd();

    //glPopMatrix();
}


void RenderUtils::onRender(void(*func)())
{
    RenderUtils::callbacks.push_back(func);
}