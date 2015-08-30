//-------------------------------------------------------------------------
/*!    COPYRIGHT NOTICE
 *     Copyright (c) 2010, ������ͼ(X2Studio.Net)
 *     All rights reserved.
 *
 * @file Global.h
 * @brief ȫ�ֱ����ļ�
 *
 * ������һЩȫ�ֱ���
 * @version 1.0
 * @author ����(8644325)
 * @date 2010��10��8��
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

#define GAME_NAME                   "�������Ҳ�"               ///< ��Ϸ����
#define GAME_FPS                    100                         ///< ��Ϸ֡��

#define TIMEBAR_WIDTH               938.0f                      ///< ʱ�����Ŀ��
#define TIMEBAR_HEIGHT              18.0f                       ///< ʱ�����ĸ߶�
#define PLAYERBAR_WIDTH             206.0f                      ///< ��Ұ�Ŀ��
#define PLAYERBAR_HEIGHT            144.0f                      ///< ��Ұ�ĸ߶�
#define PLAYERBAR_CIRCLE_WIDTH      18.0f                       ///< ��Ұ嶹�ӿ��
#define PLAYERBAR_CIRCLE_HEIGHT     21.0f                       ///< ��Ұ嶹�Ӹ߶�

#define GUI_TIMEBAR_ID              1                           ///< ʱ����GUI��ID
#define GUI_PLAYER_1_ID             10                          ///< ��Ұ�1��ID
#define GUI_START_ID                40                          ///< ��ʼ��ťGUI��ID

#define PIC_WIDTH                   503                         ///
#define PIC_HEIGHT                  452                         ///

#define DIS_MAX_SQUAREA             50                          ///< Ť�����������

#define MAX_PLAY_TIME               45.0f                       ///< �ʱ��
#define MAX_FORB_TIME               2.0f                        ///< ���ֹʱ��
#define COUNTED_DOWN_TIME           8.0f                        ///< ����ʱʱ��

#define FONT_MAX_UP_DIS             25.0f                       ///< ����������߶�
#define FONT_MAX_TIME               2.0f                        ///< ������ʱ��     
#define FONT_BEGINNING_POS          350.0f                      ///< �����y��

/**
 * @brief ��Ϸ״̬
 */
enum Status {
    NOT_STARTED,                                                ///< δ��ʼ
    RUNNING,                                                    ///< ������
    WIN,                                                        ///< ʤ��
    LOSE,                                                       ///< ʧ��
    WAITING,                                                    ///< �ȴ���
    READYGO,                                                    ///< Ready�ȴ���
    SPREADING,                                                  ///< չ����
    FORB                                                        ///< ��ֹ״̬
};

/**
 * @brief �Ҳ�ͼƬ
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
