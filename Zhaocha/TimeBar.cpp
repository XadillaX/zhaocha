#include "TimeBar.h"

/**
 * @brief 构造函数
 * 将相应的资源赋值到相应变量中，并初始化。
 */
CTimeBar::CTimeBar(int _id, HGE *pEngine, hgeSprite *pBackground, hgeSprite *pSpriteLeft, hgeSprite *pSpriteCenter, hgeSprite *pSpriteRight, hgeSprite *pSpriteWood,
                   float fMargin_top, float fMargin_left, float _width, float _height)
                   : m_fTotTime(MAX_PLAY_TIME)
                   , m_fNowTime(0.0f)
{
    _id = id;

    m_pEngine = pEngine;
    m_pSpriteBackground = new hgeSprite(*pBackground);
    m_pSpriteLeft = new hgeSprite(*pSpriteLeft);
    m_pSpriteCenter = new hgeSprite(*pSpriteCenter);
    m_pSpriteRight = new hgeSprite(*pSpriteRight);
    m_pSpriteWood = new hgeSprite(*pSpriteWood);

    margin_left = fMargin_left;
    margin_top = fMargin_top;
    height = _height;
    width = _width;

    m_bRunning = false;

    m_Target = m_pEngine->Target_Create(width, height, true);
    m_pTargetSpr = new hgeSprite(m_pEngine->Target_GetTexture(m_Target), 0, 0, width, height);

    bVisible = true, bEnabled = true, bStatic = true;
    rect.Set(margin_left, margin_top, margin_left + width, margin_top + height);

    m_bTimeUp = false;
}

/**
 * @brief 析构函数
 */
CTimeBar::~CTimeBar(void)
{
}

void CTimeBar::Update(float dt)
{
    m_pEngine->Gfx_BeginScene(m_Target);
    m_pEngine->Gfx_Clear(0x00000000);
    
    m_pSpriteBackground->Render(-margin_left, -margin_top);
    if(m_bRunning)
    {
        m_fNowTime += dt;
        if(m_fNowTime > m_fTotTime)
        {
            m_bTimeUp = true;
            m_fNowTime = m_fTotTime;
        }

        float fRealWidth = (m_fNowTime / m_fTotTime) * (width - 17 - 25);

        m_pSpriteLeft->RenderStretch(0, 0 + 10, 13, height);
        m_pSpriteCenter->RenderStretch(13, 0 + 10, 13 + fRealWidth, height);
        m_pSpriteWood->RenderStretch(13 + fRealWidth, 0, 13 + fRealWidth + 17, height);
        m_pSpriteRight->RenderStretch(13 + fRealWidth + 17, 0 + 10, 13 + fRealWidth + 17 + 12, height);
    }

    m_pEngine->Gfx_EndScene();
}

void CTimeBar::Render()
{
    m_pTargetSpr->Render(rect.x1, rect.y1);
}

void CTimeBar::Start()
{
    m_bRunning = true;
}

void CTimeBar::Stop()
{
    m_fNowTime = 0.0f;
    m_bRunning = false;
    m_bTimeUp = false;
}

void CTimeBar::Pause()
{
    m_bRunning = false;
}

void CTimeBar::DecTime(float t)
{
    m_fNowTime -= t;
    if(m_fNowTime < 0.0f) m_fNowTime = 0.0f;
}

float CTimeBar::GetTime()
{
    return m_fNowTime;
}