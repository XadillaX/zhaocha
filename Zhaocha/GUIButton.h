//-------------------------------------------------------------------------
/*!    COPYRIGHT NOTICE
 *     Copyright (c) 2010, ������ͼ(X2Studio.Net)
 *     All rights reserved.
 *
 * @file GUIButton.h
 * @brief GUI��ť��
 *
 * �����Ͷ�����GUI��ť����
 * @version 1.0
 * @author ����(8644325)
 * @date 2010��10��10��
 */
//-------------------------------------------------------------------------
#pragma once
#include "hgegui.h"

class CGUIButton : public hgeGUIObject
{
private:
    float x;                                                    //��ťx����
    float y;                                                    //��ťy����
    float width;                                                //���
    float height;                                               //�߶�
    hgeSprite *Up;                                              //����ʱ����
    hgeSprite *Down;                                            //����ʱ����
    hgeSprite *Hover;                                           //����ʱ����   
    HGE *m_pEngine;                                             //HGE����ָ�룬ָ�򸸶��������

    bool m_bDown;                                               //�Ƿ���
    bool m_bHover;                                              //�Ƿ񾭹�

    HEFFECT sndGo;
    HEFFECT sndReady;

    HCHANNEL chnReady;
    HCHANNEL chnGo; 

    bool ReadyPlayed;
    bool GoPlayed;
    bool CanStart;                                              ///< �ܷ�ʼ��

public:
    CGUIButton(int _id, HGE *pEngine, HTEXTURE Texture, float _x, float _y, HEFFECT snd1, HEFFECT snd2);
    ~CGUIButton(void);

    virtual void Update(float dt);
    virtual bool MouseLButton(bool bDown);
    virtual void MouseOver(bool bOver);
    virtual void Render();

    bool SoundPlayed(){ return CanStart; }
};
