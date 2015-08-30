#include "GameWorld.h"

/**
 * @brief 主游戏类构造函数
 *
 * @see InitConfig
 * @see LoadResource
 */
CGameWorld::CGameWorld(void)
: m_TimeBar(NULL)
, m_nLastID(0)
{
    ///< 创建HGE引擎
    Engine = hgeCreate(HGE_VERSION);

    ///< 载入资源包
    Engine->Resource_AttachPack(RESOURCE_PACK_FILENAME, RESOURCE_PACK_PASSWORD);

    ///< 读取配置文件
    InitConfig();

    m_GameStat = NOT_STARTED;

    ///< 配置HGE引擎
    Engine->System_SetState(HGE_SCREENHEIGHT, m_nScreenHeight);
    Engine->System_SetState(HGE_SCREENWIDTH, m_nScreenWidth);
    Engine->System_SetState(HGE_TITLE, GAME_NAME);
    Engine->System_SetState(HGE_FPS, GAME_FPS);
    Engine->System_SetState(HGE_SCREENBPP, 32);
    Engine->System_SetState(HGE_SHOWSPLASH, true);
    Engine->System_SetState(HGE_WINDOWED, true);
    Engine->System_SetState(HGE_LOGFILE, "Game.log");
    Engine->System_SetState(HGE_FRAMEFUNC, LogicFunc);
    Engine->System_SetState(HGE_RENDERFUNC, RenderFunc);
    Engine->System_SetState(HGE_ZBUFFER, true);
    Engine->System_SetState(HGE_GFXRESTOREFUNC, GfxRestoreFunc);
    Engine->System_SetState(HGE_DONTSUSPEND, true);
    Engine->System_SetState(HGE_ICON, "IDI_ICON1");

    m_pPic[0] = NULL, m_pPic[1] = NULL;
    m_pPicBG[0] = NULL, m_pPicBG[1] = NULL;
    m_pPicDis[0] = NULL, m_pPicDis[1] = NULL;

    chnPlay = 0;
}

/**
 * @brief 析构函数
 */
CGameWorld::~CGameWorld(void)
{
}

/**
 * @brief 游戏开始
 * 启动引擎，开始游戏。
 */
void CGameWorld::StartEngine()
{    
    ///< 初始化引擎
    if(Engine->System_Initiate())
    {
        if(LoadResource()) Engine->System_Start();
        else
        {
            MessageBox(NULL, L"游戏资源载入错误！", L"错误", MB_ICONSTOP);

            Engine->System_Shutdown();
            Engine->Release();
            exit(0);
        }
    }
}

/**
 * @brief 读取配置文件
 * 将游戏相应配置读取到内存。
 */
void CGameWorld::InitConfig()
{
    string szFileName = string(INI_PATH) + string(INI_FILE_NAME);
    Engine->System_SetState(HGE_INIFILE, szFileName.c_str());

    m_nScreenHeight = Engine->Ini_GetInt("screen", "height", 0);
    m_nScreenWidth = Engine->Ini_GetInt("screen", "width", 0);
}

/**
 * @brief 载入资源
 * 将相应的游戏资源包括纹理、音效等从硬盘中载入到内存里
 *
 * @return 若载入成功则返回true，否则返回false。
 */
bool CGameWorld::LoadResource()
{
    Engine->Resource_AttachPack(RESOURCE_PACK_FILENAME, RESOURCE_PACK_PASSWORD);
    Engine->Resource_AttachPack(PICTURE_PACK_FILENAME, RESOURCE_PACK_PASSWORD);

    string szFileName;

    /* 载入字体 */
    szFileName = string(TEXTURE_PATH) + string(FONT);
    fnt = new hgeFont(szFileName.c_str());
    if(fnt == NULL) return false;
    for(int i = 0; i < 5; i++) m_pFrameLine[i] = new CDeffience(Engine, fnt);

    /* 读入游戏音乐 */
    szFileName = string(SOUND_PATH) + string(SOUND_PLAY);
    sndPlay = Engine->Effect_Load(szFileName.c_str());
    if(!sndPlay) return false;
     
    szFileName = string(SOUND_PATH) + string(SOUND_READY);
    sndReady = Engine->Effect_Load(szFileName.c_str());
    if(!sndReady) return false;

    szFileName = string(SOUND_PATH) + string(SOUND_GO);
    sndGo = Engine->Effect_Load(szFileName.c_str());
    if(!sndGo) return false;

    szFileName = string(SOUND_PATH) + string(SOUND_READY_WAV);
    sndReadyWav = Engine->Effect_Load(szFileName.c_str());
    if(!sndReadyWav) return false;

    szFileName = string(SOUND_PATH) + string(SOUND_SPREAD);
    sndSpread = Engine->Effect_Load(szFileName.c_str());
    if(!sndSpread) return false;

    szFileName = string(SOUND_PATH) + string(SOUND_CLICK_RIGHT);
    sndClickRight = Engine->Effect_Load(szFileName.c_str());
    if(!sndClickRight) return false;
    
    szFileName = string(SOUND_PATH) + string(SOUND_CLICK_WRONG);
    sndClickWrong = Engine->Effect_Load(szFileName.c_str());
    if(!sndClickWrong) return false;

    szFileName = string(SOUND_PATH) + string(SOUND_LOSE);
    sndLose = Engine->Effect_Load(szFileName.c_str());
    if(!sndLose) return false;

    szFileName = string(SOUND_PATH) + string(SOUND_WIN);
    sndWin = Engine->Effect_Load(szFileName.c_str());
    if(!sndWin) return false;

    szFileName = string(SOUND_PATH) + string(SOUND_COUNT_DOWN);
    sndCountDown = Engine->Effect_Load(szFileName.c_str());
    if(!sndCountDown) return false;

    /* 载入背景 */
    szFileName = string(TEXTURE_PATH) + string(TEXTURE_BACKGROUND);
    m_BackgroundTexture = Engine->Texture_Load(szFileName.c_str());
    if(!m_BackgroundTexture) return false;
    else
    {
        m_pBackground = new hgeSprite(m_BackgroundTexture, 0, 0,
            Engine->Texture_GetWidth(m_BackgroundTexture), Engine->Texture_GetHeight(m_BackgroundTexture));

        m_pBackground->SetBlendMode(BLEND_DEFAULT);
        m_pBackground->SetZ(1.0f);
    }

    /* 载入时间条遮蔽物 */
    szFileName = string(TEXTURE_PATH) + string(TEXTURE_TIMEBAR_VASE);
    m_TimeBarVaseTexture = Engine->Texture_Load(szFileName.c_str());
    if(!m_TimeBarVaseTexture) return false;
    else
    {
        m_pTimeBarVase = new hgeSprite(m_TimeBarVaseTexture, 0, 0,
            Engine->Texture_GetWidth(m_TimeBarVaseTexture), Engine->Texture_GetHeight(m_TimeBarVaseTexture));

        m_pTimeBarVase->SetBlendMode(BLEND_DEFAULT);
        m_pTimeBarVase->SetZ(0.01f);
    }

    szFileName = string(TEXTURE_PATH) + string(TEXTURE_PICTURE_COVER);
    m_PictureCoverTexture = Engine->Texture_Load(szFileName.c_str());
    if(!m_PictureCoverTexture) return false;
    else
    {
        m_pPictureCover = new hgeSprite(m_PictureCoverTexture, 0, 0,
            Engine->Texture_GetWidth(m_PictureCoverTexture), Engine->Texture_GetHeight(m_PictureCoverTexture));

        m_pPictureCover->SetBlendMode(BLEND_DEFAULT);
        m_pPictureCover->SetZ(0.1f);
    }

    /* 载入时间条 */
    szFileName = string(TEXTURE_PATH) + string(TEXTURE_TIMEBAR);
    m_TimeBarTexture = Engine->Texture_Load(szFileName.c_str());
    szFileName = string(TEXTURE_PATH) + string(TEXTURE_TIMEBAR_WOOD);
    m_TimeBarWoodTexture = Engine->Texture_Load(szFileName.c_str());
    if(!m_TimeBarTexture || !m_TimeBarWoodTexture) return false;
    else
    {
        m_pTimeBar_L = new hgeSprite(m_TimeBarTexture, 0, 0, 13, 8);
        m_pTimeBar_M = new hgeSprite(m_TimeBarTexture, 13, 0, 2, 8);
        m_pTimeBar_R = new hgeSprite(m_TimeBarTexture, 15, 0, 12, 8);

        m_pTimeBar_Wood = new hgeSprite(m_TimeBarWoodTexture, 0, 0,
            Engine->Texture_GetWidth(m_TimeBarWoodTexture), Engine->Texture_GetHeight(m_TimeBarWoodTexture));

        m_TimeBar = new CTimeBar(GUI_TIMEBAR_ID, Engine, m_pBackground, m_pTimeBar_L, m_pTimeBar_M, m_pTimeBar_R, m_pTimeBar_Wood, 
            142, 72, TIMEBAR_WIDTH, TIMEBAR_HEIGHT);
    }

    /* 载入玩家板 */
    szFileName = string(TEXTURE_PATH) + string(TEXTURE_PLAYERBAR_1);
    m_PlayerBarTexture = Engine->Texture_Load(szFileName.c_str());
    szFileName = string(TEXTURE_PATH) + string(TEXTURE_PLAYERBAR_CIRCLE);
    m_PlayerBarCircleTexture = Engine->Texture_Load(szFileName.c_str());
    if(!m_PlayerBarTexture || !m_PlayerBarCircleTexture) return false;
    else
    {
        m_PlayerBar = new CPlayerBar(GUI_PLAYER_1_ID, Engine, new hgeSprite(m_PlayerBarTexture, 0, 0, PLAYERBAR_WIDTH, PLAYERBAR_HEIGHT),
            new hgeSprite(m_PlayerBarCircleTexture, 0, 0, PLAYERBAR_CIRCLE_WIDTH, PLAYERBAR_CIRCLE_HEIGHT), 206, 0, PLAYERBAR_WIDTH, PLAYERBAR_HEIGHT);
    }

    /* 载入开始按钮 */
    szFileName = string(TEXTURE_PATH) + string(TEXTURE_START_BTN);
    m_StartButtonTexture = Engine->Texture_Load(szFileName.c_str());
    if(!m_StartButtonTexture) return false;
    else
    {
        m_StartButton = new CGUIButton(GUI_START_ID, Engine, m_StartButtonTexture,
            808, 617, sndReadyWav, sndGo);
    }

    /* 鼠标 */
    szFileName = string(TEXTURE_PATH) + string(TEXTURE_NORMAL_CURSOR);
    m_NormalCurTexture = Engine->Texture_Load(szFileName.c_str());
    if(!m_NormalCurTexture) return false;
    else
    {
        m_pNormal_Cursor = new hgeSprite(m_NormalCurTexture, 0, 0, 32, 32);
        m_pNormal_Cursor->SetZ(0.0f);
    }

    szFileName = string(TEXTURE_PATH) + string(TEXTURE_FINDING_CURSOR);
    m_FindingCurTexture = Engine->Texture_Load(szFileName.c_str());
    if(!m_NormalCurTexture) return false;
    else
    {
        m_pFinding_Cursor = new hgeSprite(m_FindingCurTexture, 0, 0, 32, 32);
        m_pFinding_Cursor->SetZ(0.0f);
    }

    szFileName = string(TEXTURE_PATH) + string(TEXTURE_FORB_CURSOR);
    m_ForbCurTexture = Engine->Texture_Load(szFileName.c_str());
    if(!m_ForbCurTexture) return false;
    else
    {
        m_pForb_Cursor = new hgeSprite(m_ForbCurTexture, 0, 0, 32, 32);
        m_pForb_Cursor->SetZ(0.0f);
    }

    szFileName = string(TEXTURE_PATH) + string(TEXTURE_STATIC_CURSOR);
    m_StaticCurTexture = Engine->Texture_Load(szFileName.c_str());
    if(!m_StaticCurTexture) return false;
    else
    {
        m_pStatic_Cursor = new hgeSprite(m_StaticCurTexture, 0, 0, 32, 32);
        m_pStatic_Cursor->SetZ(0.0f);
        m_pStatic_Cursor->SetHotSpot(11, 10);
    }

    /* 读入关卡 */
    szFileName = string(ZHAOCHA_PATH) + string(ZHAOCHA_LST);
    FILE *fp;
    fp = fopen(szFileName.c_str(), "r");
    if(fp == NULL) return false;
    fscanf(fp, "%d", &m_nTask);
    int n = m_nTask, m = 0, ncnt = 0;
    while(n--)
    {
        fscanf(fp, "%s", m_Zhaocha[m].name);
        m_Zhaocha[m].iniFile[0] = m_Zhaocha[m].pic1[0] = m_Zhaocha[m].pic2[0] = m_Zhaocha[m].RealPic1[0] = m_Zhaocha[m].RealPic2[0] = '\0'; 
        ncnt++;
        string tmp = string(ZHAOCHA_PATH) + string(m_Zhaocha[m].name) + string(".ini");
        memcpy(m_Zhaocha[m].iniFile, tmp.c_str(), sizeof(m_Zhaocha[m].iniFile));

        Engine->System_SetState(HGE_INIFILE, m_Zhaocha[m].iniFile);

        string pic1 = string(m_Zhaocha[m].name) + string("1.png");
        string pic2 = string(m_Zhaocha[m].name) + string("2.png");

        memcpy(m_Zhaocha[m].RealPic1, Engine->Ini_GetString("picture", "pic1", pic1.c_str()), 
            sizeof(m_Zhaocha[m].RealPic1));
        memcpy(m_Zhaocha[m].RealPic2, Engine->Ini_GetString("picture", "pic2", pic2.c_str()), 
            sizeof(m_Zhaocha[m].RealPic2));

        memcpy(m_Zhaocha[m].pic1, ZHAOCHA_PATH, sizeof(m_Zhaocha[m].pic1));
        memcpy(m_Zhaocha[m].pic2, ZHAOCHA_PATH, sizeof(m_Zhaocha[m].pic2));
        strncat(m_Zhaocha[m].pic1, m_Zhaocha[m].RealPic1, sizeof(m_Zhaocha[m].pic1));
        strncat(m_Zhaocha[m].pic2, m_Zhaocha[m].RealPic2, sizeof(m_Zhaocha[m].pic2));

        /* 读入矩形 */
        //m_Zhaocha[m] = new zcp();
        for(int i = 0; i < 5; i++)
        {
            m_Zhaocha[m].rect[i].x1 = Engine->Ini_GetFloat(rectStr[i], "x1", 0.0f);
            m_Zhaocha[m].rect[i].x2 = Engine->Ini_GetFloat(rectStr[i], "x2", 0.0f);

            m_Zhaocha[m].rect[i].y1 = Engine->Ini_GetFloat(rectStr[i], "y1", 0.0f);
            m_Zhaocha[m].rect[i].y2 = Engine->Ini_GetFloat(rectStr[i], "y2", 0.0f);
        }

        m++;
    }
    m_nTask = ncnt;

    /* 建立GUI */
    gui = new hgeGUI();
    gui->AddCtrl(m_TimeBar);
    gui->AddCtrl(m_PlayerBar);
    gui->AddCtrl(m_StartButton);

    CurGUI = new hgeGUI();
    CurGUI->SetCursor(m_pNormal_Cursor);

    chnReady = Engine->Effect_PlayEx(sndReady, 100, 0, 1.0, true);

    return true;
}

/**
 * @brief 游戏开始函数
 *
 * @return 若开始成功则返回true，否则返回false。
 */
bool CGameWorld::StartGame()
{
    if(Target_Pic[0] && Target_Pic[1])
    {
        Engine->Target_Free(Target_Pic[0]);
        Engine->Target_Free(Target_Pic[1]);
    }

    if(m_pPic[0] && m_pPic[1])
    {
        delete m_pPic[0];
        delete m_pPic[1];
        m_pPic[0] = NULL, m_pPic[1] = NULL;
    }

    if(m_pPicDis[0] && m_pPicDis[1])
    {
        delete m_pPicDis[0];
        delete m_pPicDis[1];
        m_pPicDis[0] = NULL, m_pPicDis[1] = NULL;
    }
    //框框全设置没有
    m_PlayerBar->GetOut();
    m_TimeBar->Stop();

    /* 随机生成关卡 */
    //srand((unsigned int)time(0));
    memset(m_isInGame, 0, sizeof(m_isInGame));
    Engine->Random_Seed();
    for(int i = 0; i < 5; i++)
    {
        int tmp = Engine->Random_Int(0, m_nTask - 1);
        while(m_isInGame[tmp]) tmp = Engine->Random_Int(0, m_nTask - 1);

        m_isInGame[tmp] = true;
        m_NowZhaocha[i] = m_Zhaocha + tmp;
    }

    //m_PlayerBar->SetPic(*m_NowZhaocha[0], m_pPicBG);

    Target_Pic[0] = Engine->Target_Create(PIC_WIDTH, PIC_HEIGHT, 0.2f);
    Target_Pic[1] = Engine->Target_Create(PIC_WIDTH, PIC_HEIGHT, 0.2f);

    //for(int i = 0; i < 5; i++)
    //{
    //    m_pFrameLine[i]->Reset();
    //    m_pFrameLine[i]->SetRect(m_NowZhaocha[0]->rect[i]);
    //}

    //m_nthisLeft = 5;
    m_PlayerBar->GetIn();
    //m_TimeBar->Start();
    //m_GameStat = RUNNING;
    //fFinishedTimer = 0.0f;

    m_GameStat = READYGO;
    Engine->Channel_Stop(chnReady);
    if(chnPlay) Engine->Channel_Stop(chnPlay);
    chnPlay = Engine->Effect_PlayEx(sndPlay, 100, 0, 1.0, true);
    StatusTimer = 0.0f;

    return true;
}

void CGameWorld::GamingLogic(float dt)
{
    if(m_TimeBar->TimeUp())
    {
        Engine->Effect_Play(sndLose);
        m_GameStat = LOSE;
        Engine->Channel_Stop(chnPlay);
        //chnReady = Engine->Effect_PlayEx(sndReady, 100, 0, 1.0, true);
        return ;
    }
    else
    if(MAX_PLAY_TIME - m_TimeBar->GetTime() < COUNTED_DOWN_TIME && !m_bCountedDown)
    {
        Engine->Effect_Play(sndCountDown);
        m_bCountedDown = true;
    }

    if(Engine->Input_GetKeyState(HGEK_LBUTTON))
    {
        float x, y;
        Engine->Input_GetMousePos(&x, &y);
        PendFind(x, y);
        if(!m_nthisLeft)
        {
            fFinishedTimer = 0.0f;
            m_GameStat = WAITING;
            m_TimeBar->Pause();
        }
    }
}

void CGameWorld::NextPic()
{
    if(m_PlayerBar->IncNum())
    {
        m_bCountedDown = false;
        if(m_pPicDis[0] != NULL && m_pPicDis[1] != NULL)
        {
            delete m_pPicDis[0];
            delete m_pPicDis[1];
            m_pPicDis[0] = NULL;
            m_pPicDis[1] = NULL;
        }

        /* 设置水波 */
        m_PlayerBar->SetDis(*m_NowZhaocha[m_PlayerBar->GetNum() - 1], m_pPicDis);
        
        Engine->Effect_Play(sndSpread);
        /* 设置图片 */
        m_PlayerBar->SetPic(*m_NowZhaocha[m_PlayerBar->GetNum() - 1], m_pPicBG);

        /* 设置线段 */
        for(int i = 0; i < 5; i++)
        {
            m_pFrameLine[i]->Reset();
            m_pFrameLine[i]->SetRect(m_NowZhaocha[m_PlayerBar->GetNum() - 1]->rect[i]);
        }

        m_nthisLeft = 5;
        m_GameStat = SPREADING;
        fFinishedTimer = 0.0f;
    }
    else
    {
        Engine->Effect_Play(sndWin);
        m_GameStat = WIN;
        Engine->Channel_Stop(chnPlay);
        //chnReady = Engine->Effect_PlayEx(sndReady, 100, 0, 1.0, true);

        m_PlayerBar->SetNum(5);
        return ;
    }
}

/**
 * @brief 逻辑函数
 * 游戏的逻辑函数，一些逻辑层操作在这里。
 *
 * @return 若引擎需要退出，则返回true，否则返回false。
 */
bool CGameWorld::GameLogicFunc()
{
    float dt = Engine->Timer_GetDelta();

    int id = gui->Update(dt);

    if(!id)
    {
        switch(m_nLastID) {
            case GUI_START_ID: 
                {
                    StartGame();
                    break;
                }
        }
        m_nLastID = 0;
    }
    else
    if(id)
    {
        m_nLastID = id;
    }

    CurGUI->Update(dt);

    /* 如果在游戏中 */
    if(m_GameStat == READYGO)
    {
        if(m_StartButton->SoundPlayed())
        {
            m_GameStat = RUNNING;
            NextPic();
        }
    }
    if(m_GameStat == RUNNING) GamingLogic(dt);
    else
    if(m_GameStat == WAITING) /* 如果一张图结束正在等待 */
    {
        fFinishedTimer += dt;

        /* 若等待时间到 */
        if(fFinishedTimer > FINISHED_WAITING) NextPic();
    }
    else
    if(m_GameStat == FORB)
    {
        ForbTimer += dt;
        if(ForbTimer > MAX_FORB_TIME) m_GameStat = RUNNING;
    }
    else
    if(m_GameStat == SPREADING)
    {
        fFinishedTimer += dt;
        int nSquare = (int)(DIS_MAX_SQUAREA * (1 - fFinishedTimer / SPREAD_TIME));
        float alpha = 0xff * (fFinishedTimer / SPREAD_TIME);

        for(int i = 0; i < 2; i++)
        {
            for(int k = 0; k < nSquare; k++)
                for(int l = 0; l < nSquare; l++)
                {
                    m_pPicDis[i]->SetZ(l, k, 0.5f);
                    m_pPicDis[i]->SetColor(l, k, ARGB(alpha, 0xff, 0xff, 0xff));
                    m_pPicDis[i]->SetDisplacement(l, k, cosf(fFinishedTimer * 10 + (k + l) / 2) * 5,
                        sinf(fFinishedTimer * 10 + (k + l) / 2) * 5, HGEDISP_NODE);
                }
        }

        /* 若时间到 */
        if(fFinishedTimer > SPREAD_TIME) 
        {
            m_pPicDis[0]->Clear(0xFF000000);
            m_pPicDis[1]->Clear(0xFF000000);
            m_GameStat = RUNNING;
            fFinishedTimer = 0.0f;
            delete m_pPicDis[0];
            delete m_pPicDis[1];
            m_pPicDis[0] = NULL;
            m_pPicDis[1] = NULL;

            m_TimeBar->Stop();
            m_TimeBar->Start();
        }
    }
    if(m_GameStat == LOSE || m_GameStat == WIN)
    {
        if(StatusTimer < FONT_MAX_TIME)
        {
            const char *str = (m_GameStat == LOSE) ? "You Lose!" : "You Win!";
            StatusTimer += dt;
            float dy = (StatusTimer / FONT_MAX_TIME) * FONT_MAX_UP_DIS;
            float w = fnt->GetStringWidth(str, false);
            StatusFontX = (800 - w) / 2;
            StatusFontY = FONT_BEGINNING_POS - dy;
        }
    }

    for(int i = 0; i < 5; i++) m_pFrameLine[i]->Update(dt);

    return false;
}

void CGameWorld::PendFind(float x, float y)
{
    bool bFlag = false;
    float ry = y - (pic_margin_top[0]);
    float rx = x - ((x >= pic_margin_left[1]) ? pic_margin_left[1] : pic_margin_left[0]);

    for(int i = 0; i < 5; i++)
    {
        if(!m_pFrameLine[i]->Finded() && m_pFrameLine[i]->InRect(rx, ry))
        {
            bFlag = true;
            Engine->Effect_Play(sndClickRight);
            m_nthisLeft--;
            m_pFrameLine[i]->SetFinded(m_nthisLeft);
            break;
        }
        else
        if(m_pFrameLine[i]->InRect(rx, ry))
        {
            bFlag = true;
        }
    }

    if(!bFlag && rx >= 0 && rx <= PIC_WIDTH && ry >= 0 && ry <= PIC_HEIGHT)
    {
        m_GameStat = FORB;
        Engine->Effect_Play(sndClickWrong);
        ForbTimer = 0.0f;
    }
}

void CGameWorld::PicRender()
{
    for(int i = 0; i < 2; i++)
    {
        Engine->Gfx_BeginScene(Target_Pic[i]);
        Engine->Gfx_Clear(0xffffffff);

        m_pPicBG[i]->Render(0, 0);

        for(int j = 0; j < 5; j++)
        {
            m_pFrameLine[j]->Render();
        }

        Engine->Gfx_EndScene();

        if(!m_pPic[i])
        {
            m_pPic[i] = new hgeSprite(Engine->Target_GetTexture(Target_Pic[i]),
                0, 0, PIC_WIDTH, PIC_HEIGHT);
        }
    }
}

/**
 * @brief 渲染函数
 * 游戏的渲染函数，一些渲染层操作在这里。
 *
 * @return 若引擎需要退出，则返回true，否则返回false。
 */
bool CGameWorld::GameRenderFunc()
{
    if(m_GameStat == RUNNING || m_GameStat == WAITING || m_GameStat == FORB) PicRender();
   
    Engine->Gfx_BeginScene();
    Engine->Gfx_Clear(0xff000000);

    m_pBackground->Render(0, 0);

    if(m_GameStat == RUNNING || m_GameStat == WAITING || m_GameStat == LOSE || m_GameStat == FORB)
    {
        for(int i = 0; i < 2; i++) 
        {
            if(m_GameStat == LOSE) m_pPic[i]->SetColor(0xff999999);
            m_pPic[i]->Render(pic_margin_left[i], pic_margin_top[i]);
        }
    }
    else
    if(m_GameStat == SPREADING)
    {
        for(int i = 0; i < 2; i++) m_pPicDis[i]->Render(pic_margin_left[i], pic_margin_top[i]);
    }

    gui->Render();

    m_pTimeBarVase->Render(1, 112);
    m_pPictureCover->Render(0, 161);

    if(m_GameStat == LOSE || m_GameStat == WIN)
    {
        char *str = (m_GameStat == LOSE) ? "You Lose!" : "You Win!";
        fnt->Render(StatusFontX, StatusFontY, HGETEXT_LEFT, str);
    }

    CursorRender();
    
    Engine->Gfx_EndScene();

    return false;
}

void CGameWorld::CursorRender()
{
    float x, y;
    Engine->Input_GetMousePos(&x, &y);
    if(x >= pic_margin_left[0] && x <= pic_margin_left[0] + PIC_WIDTH 
        && y >= pic_margin_top[0] && y <= pic_margin_top[0] + PIC_HEIGHT)
    {
        CurGUI->SetCursor(m_pFinding_Cursor);
        m_pStatic_Cursor->Render(x - pic_margin_left[0] + pic_margin_left[1], 
            y - pic_margin_top[0] + pic_margin_top[1]);

        if(m_GameStat == FORB) CurGUI->SetCursor(m_pForb_Cursor);
    }
    else
    if(x >= pic_margin_left[1] && x <= pic_margin_left[1] + PIC_WIDTH 
        && y >= pic_margin_top[1] && y <= pic_margin_top[1] + PIC_HEIGHT)
    {
        CurGUI->SetCursor(m_pFinding_Cursor);
        m_pStatic_Cursor->Render(x - pic_margin_left[1] + pic_margin_left[0], 
            y - pic_margin_top[1] + pic_margin_top[0]);

        if(m_GameStat == FORB) CurGUI->SetCursor(m_pForb_Cursor);
    }
    else
    {
        CurGUI->SetCursor(m_pNormal_Cursor);
        if(m_GameStat == FORB) CurGUI->SetCursor(m_pForb_Cursor);
    }

    CurGUI->Render();
}

bool CGameWorld::GameGfxRestoreFunc()
{
    if(m_TimeBar != NULL)
    {
        if(m_TimeBar->m_Target && m_TimeBar->m_pTargetSpr != NULL)
        {
            m_TimeBar->m_pTargetSpr->SetTexture(Engine->Target_GetTexture(m_TimeBar->m_Target));
        }
    }

    if(Target_Pic[0] && Target_Pic[1] && m_pPic[0] != NULL && m_pPic[1] != NULL)
    {
        m_pPic[0]->SetTexture(Engine->Target_GetTexture(Target_Pic[0]));
        m_pPic[1]->SetTexture(Engine->Target_GetTexture(Target_Pic[1]));
    }

    return false;
}
