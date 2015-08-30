//-------------------------------------------------------------------------
/*!    COPYRIGHT NOTICE
 *     Copyright (c) 2010, 艾克视图(X2Studio.Net)
 *     All rights reserved.
 *
 * @file TimeBar.h
 * @brief 玩家板类文件
 *
 * 声明和定义了游戏玩家板的类
 * @version 1.0
 * @author 死月(8644325)
 * @date 2010年10月10日
 */
//-------------------------------------------------------------------------
#pragma once
#include "Global.h"
#include "hgegui.h"

#define MAX_CIRCLE_NUM              5                              ///< 最大豆子数

const float f_CircleTop[5] = { 113.0f, 86.0f, 60.0f, 34.0f, 7.0f };
const float f_CircleLeft = 182.0f;

class CPlayerBar : public hgeGUIObject
{
private:
    HGE *m_pEngine;                                                 ///< HGE引擎指针
    hgeSprite *m_pBackground;                                       ///< 背景图片精灵
    hgeSprite *m_pCircle;                                           ///< 豆子图片精灵
    float x;                                                        ///< 玩家板x坐标值
    float y;                                                        ///< 玩家板y坐标值
    float width;                                                    ///< 玩家板宽度
    float height;                                                   ///< 玩家板长度

    int m_nCircleNum;                                               ///< 豆子数

    bool bExists;                                                   ///< 玩家是否存在

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
