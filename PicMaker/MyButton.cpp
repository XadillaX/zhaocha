#include "MyButton.h"

CMyButton::CMyButton(int _id, hgeSprite *up, hgeSprite *hover, hgeSprite *down, hgeFont *f, float x, float y, float w, float h, char *t)
: m_bDown(false)
, m_bHover(false)
{
    id = _id;
    Up = new hgeSprite(*up);
    Hover = new hgeSprite(*hover);
    Down = new hgeSprite(*down);

    height = h;
    width = w;

    rect.Set(x, y, x + w, y + h);

    fnt = f;
    memcpy(text, t, sizeof(text));

    bStatic = true, bVisible = true, bEnabled = true;
}

bool CMyButton::MouseLButton(bool bDown)
{
    m_bDown = bDown;

    return m_bDown ^ 0;
}

void CMyButton::MouseOver(bool bOver)
{
    m_bHover = bOver;
}

void CMyButton::Render()
{
    if(m_bDown) Down->Render(rect.x1, rect.y1);
    else
    if(m_bHover) Hover->Render(rect.x1, rect.y1);
    else Up->Render(rect.x1, rect.y1);

    if(m_bDown) fnt->SetColor(0xffffffff);
    else
    if(m_bHover) fnt->SetColor(0xff002c50);
    else fnt->SetColor(0xffd5fe62);

    fnt->Render(rect.x1 + 3, rect.y1 + 3, HGETEXT_LEFT, text);
}

CMyButton::~CMyButton(void)
{
}
