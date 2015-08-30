#include "GUIButton.h"

CGUIButton::CGUIButton(int _id, HGE *pEngine, HTEXTURE Texture, float _x, float _y, HEFFECT snd1, HEFFECT snd2)
{
    m_bDown = false;
    m_bHover = false;

    id = _id;
    m_pEngine = pEngine;

    width = m_pEngine->Texture_GetWidth(Texture) / 3;
    height = m_pEngine->Texture_GetHeight(Texture);

    Up = new hgeSprite(Texture, 0, 0, width, height);
    Hover = new hgeSprite(Texture, width, 0, width, height);
    Down = new hgeSprite(Texture, width + width, 0, width, height);

    x = _x, y = _y;

    rect.Set(x, y, x + width, y + height);

    sndReady = snd1;
    sndGo = snd2;

    CanStart = false;
    ReadyPlayed = false;
    GoPlayed = false;
}

void CGUIButton::Render()
{
    if(m_bDown) Down->Render(rect.x1, rect.y1);
    else
    if(m_bHover) Hover->Render(rect.x1, rect.y1);
    else Up->Render(rect.x1, rect.y1);
}

void CGUIButton::Update(float dt)
{
    if(ReadyPlayed && !m_pEngine->Channel_IsPlaying(chnReady))
    {
        ReadyPlayed = false;
        GoPlayed = true;
        chnGo = m_pEngine->Effect_Play(sndGo);
    }
    else
    if(GoPlayed && !m_pEngine->Channel_IsPlaying(chnGo))
    {
        CanStart = true;
    }
}

bool CGUIButton::MouseLButton(bool bDown)
{
    if(bDown) 
    {
        m_bDown = true;
        chnReady = m_pEngine->Effect_Play(sndReady);
        ReadyPlayed = true;
        GoPlayed = false;
        CanStart = false;
    }
    else m_bDown = false;

    return m_bDown ^ 0;
}

void CGUIButton::MouseOver(bool bOver)
{
    if(bOver) m_bHover = true;
    else m_bHover = false;
}

CGUIButton::~CGUIButton(void)
{
    m_pEngine->Texture_Free(Up->GetTexture());
}
