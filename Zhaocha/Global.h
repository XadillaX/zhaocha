//-------------------------------------------------------------------------
/*!    COPYRIGHT NOTICE
 *     Copyright (c) 2010, 艾克视图(X2Studio.Net)
 *     All rights reserved.
 *
 * @file Global.h
 * @brief 全局变量文件
 *
 * 储存了一些全局变量
 * @version 1.0
 * @author 死月(8644325)
 * @date 2010年10月8日
 */
//-------------------------------------------------------------------------
#pragma once

#ifndef GLOBAL
#define GLOBAL
#include <cmath>
#include <hge.h>
#include <hgeSprite.h>
#include <hgeGUI.h>
#include <hgerect.h>
#include <hgedistort.h>
#include <hgeFont.h>

#define GAME_NAME                   "死月来找茬"               ///< 游戏名称
#define GAME_FPS                    100                         ///< 游戏帧率

#define TIMEBAR_WIDTH               938.0f                      ///< 时间条的宽度
#define TIMEBAR_HEIGHT              18.0f                       ///< 时间条的高度
#define PLAYERBAR_WIDTH             206.0f                      ///< 玩家板的宽度
#define PLAYERBAR_HEIGHT            144.0f                      ///< 玩家板的高度
#define PLAYERBAR_CIRCLE_WIDTH      18.0f                       ///< 玩家板豆子宽度
#define PLAYERBAR_CIRCLE_HEIGHT     21.0f                       ///< 玩家板豆子高度

#define GUI_TIMEBAR_ID              1                           ///< 时间条GUI的ID
#define GUI_PLAYER_1_ID             10                          ///< 玩家板1的ID
#define GUI_START_ID                40                          ///< 开始按钮GUI的ID

#define PIC_WIDTH                   503                         ///
#define PIC_HEIGHT                  452                         ///

#define DIS_MAX_SQUAREA             50                          ///< 扭曲最大网格数

#define MAX_PLAY_TIME               45.0f                       ///< 最长时间
#define MAX_FORB_TIME               2.0f                        ///< 最长禁止时间
#define COUNTED_DOWN_TIME           8.0f                        ///< 倒计时时间

#define FONT_MAX_UP_DIS             25.0f                       ///< 字最大上升高度
#define FONT_MAX_TIME               2.0f                        ///< 字上升时间     
#define FONT_BEGINNING_POS          350.0f                      ///< 字最初y轴

/**
 * @brief 游戏状态
 */
enum Status {
    NOT_STARTED,                                                ///< 未开始
    RUNNING,                                                    ///< 正在玩
    WIN,                                                        ///< 胜利
    LOSE,                                                       ///< 失败
    WAITING,                                                    ///< 等待中
    READYGO,                                                    ///< Ready等待中
    SPREADING,                                                  ///< 展开中
    FORB                                                        ///< 禁止状态
};

/**
 * @brief 找茬图片
 */
struct zcp {
    char name[512];
    hgeRect rect[5];
    char iniFile[512];
    char pic1[512], pic2[512], RealPic1[512], RealPic2[512];
    zcp()
    {
        iniFile[0] = pic1[0] = pic2[0] = RealPic1[0] = RealPic2[0] = '\0';
    }
};

class CGameWorld;
class CTimeBar;
class CPlayerBar;
class CDeffience;

extern CGameWorld *g_GameWorld;
extern bool LogicFunc();
extern bool RenderFunc();
extern bool GfxRestoreFunc();
extern char *rectStr[5];
extern const float pic_margin_top[2];
extern const float pic_margin_left[2];

#include <ctime>
#include "cstring"
#include "string"
#include "GameResource.h"
#include "TimeBar.h"
#include "PlayerBar.h"
#include "GUIButton.h"
#include "Deffience.h"
#include "GameWorld.h"
using namespace std;

#endif
