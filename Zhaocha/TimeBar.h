//-------------------------------------------------------------------------
/*!    COPYRIGHT NOTICE
 *     Copyright (c) 2010, ������ͼ(X2Studio.Net)
 *     All rights reserved.
 *
 * @file TimeBar.h
 * @brief ʱ�������ļ�
 *
 * �����Ͷ�������Ϸʱ��������
 * @version 1.0
 * @author ����(8644325)
 * @date 2010��10��9��
 */
//-------------------------------------------------------------------------
#pragma once
#include "Global.h"
#include "hgegui.h"

class CTimeBar : public hgeGUIObject
{
private:
    const float m_fTotTime;                                 ///< ���ʱ��
    float width;                                            ///< GUI���
    float height;                                           ///< GUI�߶�
    float margin_left;                                      ///< ������С
    float margin_top;                                       ///< ������С
    float m_fNowTime;                                       ///< ���ڵ���ʱ

    HGE *m_pEngine;                                         ///< HGE���棬ָ�򸸶��������
    hgeSprite *m_pSpriteBackground;                         ///< ��������
    hgeSprite *m_pSpriteLeft;                               ///< �������
    hgeSprite *m_pSpriteRight;                              ///< �����Ҷ�
    hgeSprite *m_pSpriteCenter;                             ///< �����ж�
    hgeSprite *m_pSpriteWood;                               ///< ����ľ��

    bool m_bRunning;                                        ///< �Ƿ����ڼ�ʱ
    bool m_bTimeUp;                                         ///< ʱ�䵽

public:
    hgeSprite *m_pTargetSpr;
    HTARGET m_Target;                                       ///< ��GUI��Ⱦ����

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
