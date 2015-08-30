//-------------------------------------------------------------------------
/*!    COPYRIGHT NOTICE
 *     Copyright (c) 2010, 艾克视图(X2Studio.Net)
 *     All rights reserved.
 *
 * @file GUIButton.h
 * @brief GUI按钮类
 *
 * 声明和定义了GUI按钮的类
 * @version 1.0
 * @author 死月(8644325)
 * @date 2010年10月10日
 */
//-------------------------------------------------------------------------
#pragma once
#include "hgegui.h"

class CGUIButton : public hgeGUIObject
{
private:
    float x;                                                    //按钮x坐标
    float y;                                                    //按钮y坐标
    float width;                                                //宽度
    float height;                                               //高度
    hgeSprite *Up;                                              //弹起时精灵
    hgeSprite *Down;                                            //按下时精灵
    hgeSprite *Hover;                                           //经过时精灵   
    HGE *m_pEngine;                                             //HGE引擎指针，指向父对象的引擎

    bool m_bDown;                                               //是否按下
    bool m_bHover;                                              //是否经过

    HEFFECT sndGo;
    HEFFECT sndReady;

    HCHANNEL chnReady;
    HCHANNEL chnGo; 

    bool ReadyPlayed;
    bool GoPlayed;
    bool CanStart;                                              ///< 能否开始了

public:
    CGUIButton(int _id, HGE *pEngine, HTEXTURE Texture, float _x, float _y, HEFFECT snd1, HEFFECT snd2);
    ~CGUIButton(void);

    virtual void Update(float dt);
    virtual bool MouseLButton(bool bDown);
    virtual void MouseOver(bool bOver);
    virtual void Render();

    bool SoundPlayed(){ return CanStart; }
};
