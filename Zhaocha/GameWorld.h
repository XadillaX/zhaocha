//-------------------------------------------------------------------------
/*!    COPYRIGHT NOTICE
 *     Copyright (c) 2010, 艾克视图(X2Studio.Net)
 *     All rights reserved.
 *
 * @file Game.h
 * @brief 死月来找茬主游戏类文件
 *
 * 游戏世界主要类文件，包括HGE引擎在内
 * @version 1.0
 * @author 死月(8644325)
 * @date 2010年10月8日
 */
//-------------------------------------------------------------------------
#pragma once

#ifndef GAMEWORLD
#define GAMEWORLD

#include "Global.h"

class CTimeBar;
class CPlayerBar;
class CGUIButton;

#define FINISHED_WAITING            1.0f                ///< 一张图找完等待时间
#define SPREAD_TIME                 1.0f                ///< 展开时间

/**
 * @brief 主游戏类
 * 死月找茬游戏游戏核心类，包含HGE引擎
 */
class CGameWorld
{
private:
    void InitConfig();
    bool LoadResource();

public:
    CGameWorld(void);
    ~CGameWorld(void);
    void StartEngine();
    bool GameLogicFunc();
    bool GameRenderFunc();
    bool GameGfxRestoreFunc();
    bool StartGame();
    void PicRender();
    void PendFind(float x, float y);
    void GamingLogic(float dt);
    void NextPic();
    void CursorRender();

public:
    float fFinishedTimer;                                   ///< 一张图找完毕到现在的时间
    float StatusTimer;                                      ///< 状态字计时器
    float ForbTimer;                                        ///< 禁手计时器
    HGE *Engine;                                            ///< HGE引擎指针
    hgeGUI *gui;                                            ///< GUI指针
    hgeGUI *CurGUI;                                         ///< 鼠标GUI

    CTimeBar *m_TimeBar;                                    ///< 时间轴指针
    CPlayerBar *m_PlayerBar;                                ///< 玩家板指针
    CGUIButton *m_StartButton;                              ///< 开始按钮

    HTEXTURE m_BackgroundTexture;                           ///< 背景图片纹理句柄
    HTEXTURE m_TimeBarVaseTexture;                          ///< 时间条遮蔽物纹理句柄
    HTEXTURE m_PictureCoverTexture;                         ///< 图片遮蔽物纹理句柄
    HTEXTURE m_TimeBarTexture;                              ///< 时间条纹理句柄
    HTEXTURE m_TimeBarWoodTexture;                          ///< 时间条木块纹理句柄
    HTEXTURE m_PlayerBarTexture;                            ///< 玩家板纹理句柄
    HTEXTURE m_PlayerBarCircleTexture;                      ///< 玩家板豆子纹理句柄
    HTEXTURE m_StartButtonTexture;                          ///< 开始按钮纹理句柄
    HTEXTURE m_NormalCurTexture;                            ///< 普通鼠标纹理句柄
    HTEXTURE m_FindingCurTexture;                           ///< 查找时鼠标纹理句柄
    HTEXTURE m_StaticCurTexture;                            ///< 魔棒鼠标纹理句柄
    HTEXTURE m_ForbCurTexture;                              ///< 魔棒鼠标纹理句柄

    hgeSprite *m_pBackground;                               ///< 背景图片精灵
    hgeSprite *m_pTimeBarVase;                              ///< 时间条遮蔽物精灵
    hgeSprite *m_pPictureCover;                             ///< 图片遮蔽物精灵
    hgeSprite *m_pTimeBar_L;                                ///< 时间条左
    hgeSprite *m_pTimeBar_R;                                ///< 时间条右
    hgeSprite *m_pTimeBar_M;                                ///< 时间条中
    hgeSprite *m_pTimeBar_Wood;                             ///< 时间条木块
    hgeSprite *m_pNormal_Cursor;                            ///< 普通鼠标精灵
    hgeSprite *m_pFinding_Cursor;                           ///< 查找时鼠标精灵
    hgeSprite *m_pStatic_Cursor;                            ///< 魔棒鼠标
    hgeSprite *m_pForb_Cursor;                              ///< 禁手鼠标

    hgeDistortionMesh *m_pPicDis[2];                        ///< 找茬图片水波精灵
    hgeSprite *m_pPic[2];                                   ///< 找茬图片精灵
    hgeSprite *m_pPicBG[2];                                 ///< 找茬图片精灵背景

    HTARGET Target_Pic[2];                                  ///< 找茬图片缓存区

    CDeffience *m_pFrameLine[5];                            ///< 框框

    HEFFECT sndPlay;                                        ///< 游戏音乐 
    HEFFECT sndReady;                                       ///< 游戏等待音乐
    HEFFECT sndGo;                                          ///< GO音乐
    HEFFECT sndReadyWav;                                    ///< Ready音乐
    HEFFECT sndSpread;                                      ///< 展开音乐
    HEFFECT sndClickRight;                                  ///< 按正确
    HEFFECT sndClickWrong;                                  ///< 按错误
    HEFFECT sndLose;                                        ///< 输音乐
    HEFFECT sndWin;                                         ///< 赢音乐
    HEFFECT sndCountDown;                                   ///< 倒计时音乐

    HCHANNEL chnPlay;                                       ///< 游戏音乐频道
    HCHANNEL chnReady;                                      ///< 游戏等待音乐频道

    hgeFont *fnt;                                           ///< 字体
    float StatusFontX;                                      ///< 字X轴
    float StatusFontY;                                      ///< 字Y轴

private:
    int m_nScreenHeight;                                    ///< 游戏程序高度
    int m_nScreenWidth;                                     ///< 游戏程序宽度
    Status m_GameStat;                                      ///< 游戏状态

    int m_nTask;                                            ///< 游戏关卡数
    zcp m_Zhaocha[65535];                                   ///< 游戏各关卡
    zcp *m_NowZhaocha[5];                                   ///< 此次游戏关卡
    bool m_isInGame[65535];                                 ///< 关卡是否在游戏中
    bool m_bCountedDown;                                    ///< 是否倒计时过

    int m_nLastID;                                          ///< 最后按下的按钮

    int m_nthisLeft;                                        ///< 这幅图剩下数量
};

#endif
