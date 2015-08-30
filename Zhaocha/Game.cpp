//-------------------------------------------------------------------------
/*!    COPYRIGHT NOTICE
 *     Copyright (c) 2010, ������ͼ(X2Studio.Net)
 *     All rights reserved.
 *
 * @file Game.h
 * @brief �������Ҳ�����ļ�
 *
 * WINAPI��ں����ļ���������Ϸ�ಢ����
 * @version 1.0
 * @author ����(8644325)
 * @date 2010��10��8��
 */
//-------------------------------------------------------------------------
#include "global.h"

/**
 * @breif �������
 * WINAPI����
 *
 * @see CGameWorld::CGameWorld
 */
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    g_GameWorld = new CGameWorld();
    g_GameWorld->StartEngine();
    
    return 0;
}