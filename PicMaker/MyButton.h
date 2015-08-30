#pragma once
#include "hge.h"
#include "hgesprite.h"
#include "hgefont.h"
#include "hgegui.h"

class CMyButton : public hgeGUIObject
{
private:
    bool m_bDown, m_bHover;
    hgeSprite *Up, *Hover, *Down;
    float height, width;
    char text[512];
    hgeFont *fnt;

public:
    CMyButton(int _id, hgeSprite *up, hgeSprite *hover, hgeSprite *down, hgeFont *f, float x, float y, float w, float h, char *t);
    ~CMyButton(void);

    virtual bool MouseLButton(bool bDown);
    virtual void MouseOver(bool bOver);
    virtual void Render();
};
