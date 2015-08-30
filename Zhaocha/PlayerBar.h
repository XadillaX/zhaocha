//-------------------------------------------------------------------------
/*!    COPYRIGHT NOTICE
 *     Copyright (c) 2010, ������ͼ(X2Studio.Net)
 *     All rights reserved.
 *
 * @file TimeBar.h
 * @brief ��Ұ����ļ�
 *
 * �����Ͷ�������Ϸ��Ұ����
 * @version 1.0
 * @author ����(8644325)
 * @date 2010��10��10��
 */
//-------------------------------------------------------------------------
#pragma once
#include "Global.h"
#include "hgegui.h"

#define MAX_CIRCLE_NUM              5                              ///< �������

const float f_CircleTop[5] = { 113.0f, 86.0f, 60.0f, 34.0f, 7.0f };
const float f_CircleLeft = 182.0f;

class CPlayerBar : public hgeGUIObject
{
private:
    HGE *m_pEngine;                                                 ///< HGE����ָ��
    hgeSprite *m_pBackground;                                       ///< ����ͼƬ����
    hgeSprite *m_pCircle;                                           ///< ����ͼƬ����
    float x;                                                        ///< ��Ұ�x����ֵ
    float y;                                                        ///< ��Ұ�y����ֵ
    float width;                                                    ///< ��Ұ���
    float height;                                                   ///< ��Ұ峤��

    int m_nCircleNum;                                               ///< ������

    bool bExists;                                                   ///< ����Ƿ����

public:
    CPlayerBar(int _id, HGE *pEngine, hgeSprite *pBackground, hgeSprite *pCircle, float _x, float _y,
        float _width, float _height);
    ~CPlayerBar(void);

    void GetIn();
    void GetOut();
    int GetNum();
    void SetNum(int num);
    bool IncNum();
    void SetPic(zcp info, hgeSprite *spr[]);
    void SetDis(zcp info, hgeDistortionMesh *dis[]);

    virtual void Update(float dt);
    virtual void Render();
};
