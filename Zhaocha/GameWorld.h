//-------------------------------------------------------------------------
/*!    COPYRIGHT NOTICE
 *     Copyright (c) 2010, ������ͼ(X2Studio.Net)
 *     All rights reserved.
 *
 * @file Game.h
 * @brief �������Ҳ�����Ϸ���ļ�
 *
 * ��Ϸ������Ҫ���ļ�������HGE��������
 * @version 1.0
 * @author ����(8644325)
 * @date 2010��10��8��
 */
//-------------------------------------------------------------------------
#pragma once

#ifndef GAMEWORLD
#define GAMEWORLD

#include "Global.h"

class CTimeBar;
class CPlayerBar;
class CGUIButton;

#define FINISHED_WAITING            1.0f                ///< һ��ͼ����ȴ�ʱ��
#define SPREAD_TIME                 1.0f                ///< չ��ʱ��

/**
 * @brief ����Ϸ��
 * �����Ҳ���Ϸ��Ϸ�����࣬����HGE����
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
    float fFinishedTimer;                                   ///< һ��ͼ����ϵ����ڵ�ʱ��
    float StatusTimer;                                      ///< ״̬�ּ�ʱ��
    float ForbTimer;                                        ///< ���ּ�ʱ��
    HGE *Engine;                                            ///< HGE����ָ��
    hgeGUI *gui;                                            ///< GUIָ��
    hgeGUI *CurGUI;                                         ///< ���GUI

    CTimeBar *m_TimeBar;                                    ///< ʱ����ָ��
    CPlayerBar *m_PlayerBar;                                ///< ��Ұ�ָ��
    CGUIButton *m_StartButton;                              ///< ��ʼ��ť

    HTEXTURE m_BackgroundTexture;                           ///< ����ͼƬ������
    HTEXTURE m_TimeBarVaseTexture;                          ///< ʱ�����ڱ���������
    HTEXTURE m_PictureCoverTexture;                         ///< ͼƬ�ڱ���������
    HTEXTURE m_TimeBarTexture;                              ///< ʱ����������
    HTEXTURE m_TimeBarWoodTexture;                          ///< ʱ����ľ��������
    HTEXTURE m_PlayerBarTexture;                            ///< ��Ұ�������
    HTEXTURE m_PlayerBarCircleTexture;                      ///< ��Ұ嶹��������
    HTEXTURE m_StartButtonTexture;                          ///< ��ʼ��ť������
    HTEXTURE m_NormalCurTexture;                            ///< ��ͨ���������
    HTEXTURE m_FindingCurTexture;                           ///< ����ʱ���������
    HTEXTURE m_StaticCurTexture;                            ///< ħ�����������
    HTEXTURE m_ForbCurTexture;                              ///< ħ�����������

    hgeSprite *m_pBackground;                               ///< ����ͼƬ����
    hgeSprite *m_pTimeBarVase;                              ///< ʱ�����ڱ��ﾫ��
    hgeSprite *m_pPictureCover;                             ///< ͼƬ�ڱ��ﾫ��
    hgeSprite *m_pTimeBar_L;                                ///< ʱ������
    hgeSprite *m_pTimeBar_R;                                ///< ʱ������
    hgeSprite *m_pTimeBar_M;                                ///< ʱ������
    hgeSprite *m_pTimeBar_Wood;                             ///< ʱ����ľ��
    hgeSprite *m_pNormal_Cursor;                            ///< ��ͨ��꾫��
    hgeSprite *m_pFinding_Cursor;                           ///< ����ʱ��꾫��
    hgeSprite *m_pStatic_Cursor;                            ///< ħ�����
    hgeSprite *m_pForb_Cursor;                              ///< �������

    hgeDistortionMesh *m_pPicDis[2];                        ///< �Ҳ�ͼƬˮ������
    hgeSprite *m_pPic[2];                                   ///< �Ҳ�ͼƬ����
    hgeSprite *m_pPicBG[2];                                 ///< �Ҳ�ͼƬ���鱳��

    HTARGET Target_Pic[2];                                  ///< �Ҳ�ͼƬ������

    CDeffience *m_pFrameLine[5];                            ///< ���

    HEFFECT sndPlay;                                        ///< ��Ϸ���� 
    HEFFECT sndReady;                                       ///< ��Ϸ�ȴ�����
    HEFFECT sndGo;                                          ///< GO����
    HEFFECT sndReadyWav;                                    ///< Ready����
    HEFFECT sndSpread;                                      ///< չ������
    HEFFECT sndClickRight;                                  ///< ����ȷ
    HEFFECT sndClickWrong;                                  ///< ������
    HEFFECT sndLose;                                        ///< ������
    HEFFECT sndWin;                                         ///< Ӯ����
    HEFFECT sndCountDown;                                   ///< ����ʱ����

    HCHANNEL chnPlay;                                       ///< ��Ϸ����Ƶ��
    HCHANNEL chnReady;                                      ///< ��Ϸ�ȴ�����Ƶ��

    hgeFont *fnt;                                           ///< ����
    float StatusFontX;                                      ///< ��X��
    float StatusFontY;                                      ///< ��Y��

private:
    int m_nScreenHeight;                                    ///< ��Ϸ����߶�
    int m_nScreenWidth;                                     ///< ��Ϸ������
    Status m_GameStat;                                      ///< ��Ϸ״̬

    int m_nTask;                                            ///< ��Ϸ�ؿ���
    zcp m_Zhaocha[65535];                                   ///< ��Ϸ���ؿ�
    zcp *m_NowZhaocha[5];                                   ///< �˴���Ϸ�ؿ�
    bool m_isInGame[65535];                                 ///< �ؿ��Ƿ�����Ϸ��
    bool m_bCountedDown;                                    ///< �Ƿ񵹼�ʱ��

    int m_nLastID;                                          ///< ����µİ�ť

    int m_nthisLeft;                                        ///< ���ͼʣ������
};

#endif
