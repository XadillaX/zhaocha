#include "PlayerBar.h"

CPlayerBar::CPlayerBar(int _id, HGE *pEngine, hgeSprite *pBackground, hgeSprite *pCircle, float _x, float _y,
                       float _width, float _height)
{
    bExists = false;
    m_nCircleNum = 0;

    _id = id;
    m_pEngine = pEngine;
    m_pBackground = pBackground;
    m_pCircle = pCircle;

    x = _x, y = _y;
    width = _width, height = _height;

    rect.Set(x, y, x + width, y + height);

    bVisible = true, bEnabled = true, bStatic = true;
}

CPlayerBar::~CPlayerBar(void)
{
}

void CPlayerBar::GetIn()
{
    m_nCircleNum = 0;
    bExists = true;
}

void CPlayerBar::GetOut()
{
    bExists = false;
}

int CPlayerBar::GetNum()
{
    return m_nCircleNum;
}

void CPlayerBar::SetNum(int num)
{
    m_nCircleNum = num;
}

bool CPlayerBar::IncNum()
{
    if(m_nCircleNum < MAX_CIRCLE_NUM) 
    {
        m_nCircleNum++;
        return true;
    }
    else m_nCircleNum = 0;

    return false;
}

void CPlayerBar::Update(float dt)
{
}

void CPlayerBar::Render()
{
    if(bExists)
    {
        m_pBackground->Render(rect.x1, rect.y1);

        for(int i = 0; i < m_nCircleNum; i++)
            m_pCircle->Render(rect.x1 + f_CircleLeft, rect.y1 + f_CircleTop[i]);
    }
}

void CPlayerBar::SetPic(zcp info, hgeSprite *spr[])
{
    HTEXTURE tex[2];
    tex[0] = m_pEngine->Texture_Load(info.pic1);
    tex[1] = m_pEngine->Texture_Load(info.pic2);

    for(int i = 0; i < 2; i++)
    {
        spr[i] = new hgeSprite(tex[i], 0, 0, PIC_WIDTH, PIC_HEIGHT);
        spr[i]->SetBlendMode(BLEND_DEFAULT_Z);
        spr[i]->SetZ(0.5f);
    }
}

void CPlayerBar::SetDis(zcp info, hgeDistortionMesh *dis[])
{
    HTEXTURE tex[2];
    tex[0] = m_pEngine->Texture_Load(info.pic1);
    tex[1] = m_pEngine->Texture_Load(info.pic2);

    for(int i = 0; i < 2; i++)
    {
        dis[i] = new hgeDistortionMesh(DIS_MAX_SQUAREA, DIS_MAX_SQUAREA);
        dis[i]->SetTexture(tex[i]);
        dis[i]->SetTextureRect(0, 0, PIC_WIDTH, PIC_HEIGHT);
        
        for(int k = 1; k < DIS_MAX_SQUAREA - 1; k++)
            for(int l = 1; l < DIS_MAX_SQUAREA - 1; l++)
            {
                dis[i]->SetBlendMode(BLEND_DEFAULT_Z);
                dis[i]->SetZ(l, k, 0.5f);
                dis[i]->SetDisplacement(l, k, cosf((k + l) / 2) * 5,
                    sinf((k + l) / 2) * 5, HGEDISP_NODE);
            }
    }
}