//-------------------------------------------------------------------------
/*!    COPYRIGHT NOTICE
 *     Copyright (c) 2010, 艾克视图(X2Studio.Net)
 *     All rights reserved.
 *
 * @file Game.h
 * @brief 死月来找茬入口文件
 *
 * WINAPI入口函数文件，加载游戏类并运行
 * @version 1.0
 * @author 死月(8644325)
 * @date 2010年10月8日
 */
//-------------------------------------------------------------------------
#include "global.h"

/**
 * @breif 程序入口
 * WINAPI函数
 * @see CGameWorld::CGameWorld
 */
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    g_GameWorld = new CGameWorld();
    g_GameWorld->StartEngine();
    return 0;
}
