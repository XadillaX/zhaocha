#include "Global.h"

CGameWorld *g_GameWorld;                            ///< ����Ϸ���ʵ����ȫ�ֱ���
char *rectStr[5] = { "rect1", "rect2", "rect3", "rect4", "rect5" };
const float pic_margin_top[2] = { 165, 165 };
const float pic_margin_left[2] = { 4, 513 };

/**
 * @brief ��Ϸ�߼���ת����
 * ת��g_GameWorld���߼�����
 *
 * @return ����Ҫ�˳���Ϸ���򷵻�true�����򷵻�false
 * @see CGameWorld
 */
bool LogicFunc()
{
    return g_GameWorld->GameLogicFunc();
}

/**
 * @brief ��Ϸ��Ⱦ��ת����
 * ת��g_GameWorld����Ⱦ����
 *
 * @return ����Ҫ�˳���Ϸ���򷵻�true�����򷵻�false
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