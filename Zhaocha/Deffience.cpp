#include "Deffience.h"

CDeffience::CDeffience(HGE *pEngine, hgeFont *pfnt)
{
    m_pEngine = pEngine;
    rect.Set(0, 0, 0, 0);
    finded = false, finished = false;
    timer = 0.0f;

    fnt = pfnt;
}

CDeffience::~CDeffience(void)
{
}

bool CDeffience::InRect(float x, float y)
{
    if(x >= rect.x1 && x <= rect.x2 && y >= rect.y1 && y <= rect.y2) return true;
    else return false;
}

void CDeffience::SetRect(float x1, float y1, float x2, float y2)
{
    float minx = (x1 < x2) ? x1 : x2, maxx = (x1 > x2) ? x1 : x2;
    float miny = (y1 < y2) ? y1 : y2, maxy = (y1 > y2) ? y1 : y2;

    rect.Set(minx, miny, maxx, maxy);

    TotLong = 2 * (maxx - minx + maxy - miny) + 1;
}

void CDeffience::SetRect(hgeRect &r)
{
    SetRect(r.x1, r.y1, r.x2, r.y2);
}

void CDeffience::Update(float dt)
{
    if(!finded || finished) return;
    timer += dt;
    if(timer > DRAW_TIME) timer = DRAW_TIME, finished = true;
}

void CDeffience::RenderFont()
{
    if(!finished)
    {
        fnt->SetZ(0);
        float dy = (timer / DRAW_TIME) * UP_DIS;
        int alpha = (int)((timer / DRAW_TIME) * 0xff);
        fnt->SetColor(ARGB(alpha, 0xff, 0x00, 0x99));
        fnt->Render(FontX, FontY - dy, HGETEXT_LEFT, m_szWord);
    }
}

void CDeffience::Render()
{
    if(!finded) return;

    float NowLong = (timer / DRAW_TIME) * TotLong;
    if(NowLong - (rect.x2 - rect.x1) <= 0)
    {
        LineRender(rect.x1, rect.y1, rect.x1 + NowLong, rect.y1, lnclr);
        RenderFont();
        return;
    }
    else
    {
        LineRender(rect.x1, rect.y1, rect.x2, rect.y1, lnclr);
        NowLong -= (rect.x2 - rect.x1);
    }

    if(NowLong - (rect.y2 - rect.y1) <= 0)
    {
        LineRender(rect.x2, rect.y1, rect.x2, rect.y1 + NowLong, lnclr);
        RenderFont();
        return;
    }
    else
    {
        LineRender(rect.x2, rect.y1, rect.x2, rect.y2, lnclr);
        NowLong -= (rect.y2 - rect.y1);
    }

    if(NowLong - (rect.x2 - rect.x1) <= 0)
    {
        LineRender(rect.x2, rect.y2, rect.x2 - NowLong, rect.y2, lnclr);
        RenderFont();
        return;
    }
    else
    {
        LineRender(rect.x2, rect.y2, rect.x1, rect.y2, lnclr);
        NowLong -= (rect.x2 - rect.x1);
    }

    LineRender(rect.x1, rect.y2, rect.x1, rect.y2 - NowLong, lnclr);
    RenderFont();
}

void CDeffience::SetFinded(int n)
{ 
    if(n) sprintf(m_szWord, "%d Left!", n); 
    else sprintf(m_szWord, "All Found!");

    //StrHeight = fnt->GetHeight();
    StrWidth = fnt->GetStringWidth(m_szWord);

    float x = (rect.x1 + rect.x2) / 2 - StrWidth / 2, y = rect.y2;
    if(x + StrWidth > PIC_WIDTH) x = PIC_WIDTH - StrWidth;
    else
    if(x < 0) x = 0;

    if(y - UP_DIS < 0) y = UP_DIS;
    else
    if(y + StrHeight > PIC_HEIGHT) y = PIC_HEIGHT - StrHeight;

    FontX = x, FontY = y;

    finded = true;
}

void CDeffience::LineRender(float x1, float y1, float x2, float y2, const int color[])
{
    int offset[3] = { 1, 0, -1 };
    if(y1 == y2)
    {
        for(int i = -1; i <= 1; i++)
        {
            m_pEngine->Gfx_RenderLine(x1 - offset[i + 1], y1 + i, x2 + offset[i + 1], y2 + i, color[i + 1], 0);
        }
    }
    else
    if(x1 == x2)
    {
        for(int i = -1; i <= 1; i++)
        {
            m_pEngine->Gfx_RenderLine(x1 + i, y1 + offset[i + 1], x2 + i, y2 - offset[i + 1], color[i + 1], 0);
        }
    }
}