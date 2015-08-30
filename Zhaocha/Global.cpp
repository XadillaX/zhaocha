#include "Global.h"

CGameWorld *g_GameWorld;                            ///< 主游戏类的实例，全局变量
char *rectStr[5] = { "rect1", "rect2", "rect3", "rect4", "rect5" };
const float pic_margin_top[2] = { 165, 165 };
const float pic_margin_left[2] = { 4, 513 };

/**
 * @brief 游戏逻辑中转函数
 * 转至g_GameWorld的逻辑函数
 *
 * @return 若需要退出游戏，则返回true，否则返回false
 * @see CGameWorld
 */
bool LogicFunc()
{
    return g_GameWorld->GameLogicFunc();
}

/**
 * @brief 游戏渲染中转函数
 * 转至g_GameWorld的渲染函数
 *
 * @return 若需要退出游戏，则返回true，否则返回false
 * @see CGameWorld
 */
bool RenderFunc()
{
    return g_GameWorld->GameRenderFunc();
}

bool GfxRestoreFunc()
{
    return g_GameWorld->GameGfxRestoreFunc();
}