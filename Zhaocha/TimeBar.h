//-------------------------------------------------------------------------
/*!    COPYRIGHT NOTICE
 *     Copyright (c) 2010, 艾克视图(X2Studio.Net)
 *     All rights reserved.
 *
 * @file TimeBar.h
 * @brief 时间条类文件
 *
 * 声明和定义了游戏时间条的类
 * @version 1.0
 * @author 死月(8644325)
 * @date 2010年10月9日
 */
//-------------------------------------------------------------------------
#pragma once
#include "Global.h"
#include "hgegui.h"

class CTimeBar : public hgeGUIObject
{
private:
    const float m_fTotTime;                                 ///< 最大时间
    float width;                                            ///< GUI宽度
    float height;                                           ///< GUI高度
    float margin_left;                                      ///< 左外框大小
    float margin_top;                                       ///< 上外框大小
    float m_fNowTime;                                       ///< 现在的用时

    HGE *m_pEngine;                                         ///< HGE引擎，指向父对象的引擎
    hgeSprite *m_pSpriteBackground;                         ///< 背景精灵
    hgeSprite *m_pSpriteLeft;                               ///< 精灵左端
    hgeSprite *m_pSpriteRight;                              ///< 精灵右端
    hgeSprite *m_pSpriteCenter;                             ///< 精灵中端
    hgeSprite *m_pSpriteWood;                               ///< 精灵木块

    bool m_bRunning;                                        ///< 是否正在计时
    bool m_bTimeUp;                                         ///< 时间到

public:
    hgeSprite *m_pTargetSpr;
    HTARGET m_Target;                                       ///< 本GUI渲染对象

public:
    CTimeBar(int _id, HGE *pEngine, hgeSprite *pBackground, hgeSprite *pSpriteLeft, hgeSprite *pSpriteCenter, hgeSprite *pSpriteRight, hgeSprite *pSpriteWood,
        float fMargin_top, float fMargin_left, float _width, float _height);
    ~CTimeBar(void);

    virtual void Update(float dt);
    virtual void Render();
    void Start();
    void Stop();
    void Pause();
    void DecTime(float t);
    float GetTime();
    bool TimeUp(){ return m_bTimeUp; }
};
