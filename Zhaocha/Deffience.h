#pragma once
#include "Global.h"

#define DRAW_TIME               1.0f                            ///< 画线时间
#define UP_DIS                  20.0f                           ///< 字上升高度

const int lnclr[3] = { 0xffffff00, 0xffff0000, 0xffffff00 };
class CDeffience
{
private:
    char m_szWord[512];
    HGE *m_pEngine;
    hgeRect rect;
    float timer;
    bool finded;
    bool finished;
    float TotLong;
    hgeFont *fnt;
    float StrHeight;
    float StrWidth;
    float FontX;
    float FontY;

public:
    CDeffience(HGE *pEngine, hgeFont *pfnt);
    ~CDeffience(void);
    void SetRect(float x1, float y1, float x2, float y2);
    void SetRect(hgeRect &r);
    void Render();
    bool Finded(){ return finded; };
    void SetFinded(int n);
    void Reset(){ timer = 0.0f, finded = false, finished = false; }
    void Update(float dt);
    void LineRender(float x1, float y1, float x2, float y2, const int color[]);
    bool InRect(float x, float y);
    bool Finished(){ return finished; }
    void RenderFont();
};
