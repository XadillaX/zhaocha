#include "PicMaker.h"
#include "cstring"
#include "MyButton.h"
#include <cstdio>
#include <cstdlib>
#include <hgeresource.h>

char szFile[512] = "\0";
char szTemp[512];
char szLstFile[512] = "\0";
char ResPath[512] = "\0";

OPENFILENAME ofn;
HTEXTURE g_UI, PicTexture;
hgeSprite *leftbar, *cursor, *pic = NULL, *picInTarget = NULL;
hgeGUI *gui;
hgeFont *fnt;
hgeGUIListbox *ListUI, *ListRect;
hgeGUISlider *ListSlider;
hgeGUIButton *ChangePic;
int PicNumSel = 1;
CMyButton *ChangePicBtn1, *ChangePicBtn2, *Save, *LoadPic, *NewPic;
HTARGET PicTarget;
int lnclr[3] = { 0xffffff00, 0xffff0000, 0xffffff00 };
bool MouseDown = false;
bool Drawing = false;
int NowRect = 0;
hgeResourceManager *LoadPicResource = NULL;

bool GfxRestoreFunc()
{
    if(PicTarget && pic != NULL)
    {
        pic->SetTexture(hge->Target_GetTexture(PicTarget));
    }

    return false;
}

void SaveFile()
{
    for(STLMap::iterator i = M.begin(); i != M.end(); i++)
    {
        hge->System_SetState(HGE_INIFILE, i->second.iniFile);

        for(int j = 0; j < 5; j++)
        {
            hge->Ini_SetInt(rectStr[j], "x1", (int)(i->second.rect[j].x1));
            hge->Ini_SetInt(rectStr[j], "x2", (int)(i->second.rect[j].x2));
            hge->Ini_SetInt(rectStr[j], "y1", (int)(i->second.rect[j].y1));
            hge->Ini_SetInt(rectStr[j], "y2", (int)(i->second.rect[j].y2));
        }
    }

    MessageBox(NULL, "所有文件保存成功！", "成功", MB_OK);
}

void LoadPNG()
{
    if(!GetOpenFileName(&ofn)) return;    
    if(LoadPicResource != NULL) delete LoadPicResource;

    string path = string(string(ResPath) + string((PicNumSel == 1) ? NowSel->second.RealPic1 : NowSel->second.RealPic2));

    SHFILEOPSTRUCT FileOp;   
    FileOp.hwnd = hge->System_GetState(HGE_HWND);
    FileOp.wFunc = FO_COPY;
    FileOp.pTo = path.c_str();
    FileOp.pFrom = ofn.lpstrFile;
    FileOp.fFlags = FOF_ALLOWUNDO;   
    FileOp.hNameMappings = NULL;
    FileOp.lpszProgressTitle = "图片正在载入";   
    
    int nOk;
    nOk = SHFileOperation(&FileOp); 
    if(nOk) MessageBox(NULL, "载入图片时出错！", "错误", MB_ICONSTOP);
    else
    {
        PicTexture = hge->Texture_Load((PicNumSel == 1) ? NowSel->second.pic1 : NowSel->second.pic2);
        picInTarget = new hgeSprite(PicTexture, 0, 0, 503, 452);
    }
}

bool DoCommand(int id)
{
	int f,l;
    switch(id) {
        case LISTBOX_ID:
            if(nLastSelected != ListUI->GetSelectedItem())
            {
                char tmp[512];
                nLastSelected = ListUI->GetSelectedItem();
                    
                memcpy(tmp, ListUI->GetItemText(nLastSelected), sizeof(tmp));
                NowSel = M.find(string(tmp));

                if(picInTarget != NULL) delete picInTarget;

                PicTexture = hge->Texture_Load(NowSel->second.pic1);
                picInTarget = new hgeSprite(PicTexture, 0, 0, 503, 452);
                PicNumSel = 1;
            }

            ListSlider->SetValue(ListUI->GetTopItem());
            break;
        case LISTSLIDER_ID:
            ListUI->SetTopItem((int)ListSlider->GetValue());
            break;
        case LISTRECT_ID:
            if(NowRect != ListRect->GetSelectedItem())
            {
                NowRect = ListRect->GetSelectedItem();
            }
            break;
        case CHANGE_PIC_ID1:
            {
                PicTexture = hge->Texture_Load(NowSel->second.pic1);
                if(picInTarget != NULL) delete picInTarget;
                picInTarget = new hgeSprite(PicTexture, 0, 0, 503, 452);
                PicNumSel = 1;
                picInTarget->SetZ(1);
            }
            break;
        case CHANGE_PIC_ID2:
            {
                PicTexture = hge->Texture_Load(NowSel->second.pic2);
                if(picInTarget != NULL) delete picInTarget;
                picInTarget = new hgeSprite(PicTexture, 0, 0, 503, 452);
                PicNumSel = 2;
                picInTarget->SetZ(1);
            }
            break;
        case SAVE_ID:
            SaveFile();
            break;
        case LOAD_PIC_ID:
            LoadPNG();
            break;
        case NEW_PIC_ID:
            {
            string cmd = string("notepad \"") + string(ResPath) + string("Set.lst\"");
            MessageBox(NULL, "Edit the list file and reopen this editor.", "Attention", MB_OK);
            system(cmd.c_str());
            return true;
            break;
            }
        default: break;
    };

    return false;
}

bool FrameFunc()
{
    float dt = hge->Timer_GetDelta();
    if(DoCommand(gui->Update(dt))) return true;

    switch(hge->Input_GetKeyState(HGEK_LBUTTON)) {
        case true:
            if(!MouseDown)
            {
                float x, y;
                MouseDown = true;
                hge->Input_GetMousePos(&x, &y);
                if(x >= PIC_MARGIN_LEFT && x <= PIC_MARGIN_LEFT + 503 && y >= PIC_MARGIN_TOP && y <= PIC_MARGIN_TOP + 452)
                {
                    Drawing = true;
                    NowSel->second.rect[NowRect].x1 = x - PIC_MARGIN_LEFT, NowSel->second.rect[NowRect].y1 = y - PIC_MARGIN_TOP;
                    NowSel->second.rect[NowRect].x2 = x - PIC_MARGIN_LEFT, NowSel->second.rect[NowRect].y2 = y - PIC_MARGIN_TOP;
                }
            }
            else
            if(Drawing)
            {
                float x, y;
                hge->Input_GetMousePos(&x, &y);
                if(x >= PIC_MARGIN_LEFT && x <= PIC_MARGIN_LEFT + 503 && y >= PIC_MARGIN_TOP && y <= PIC_MARGIN_TOP + 452)
                {
                    Drawing = true;
                    NowSel->second.rect[NowRect].x2 = x - PIC_MARGIN_LEFT, NowSel->second.rect[NowRect].y2 = y - PIC_MARGIN_TOP;
                }
            }
            break;
        case false:
            MouseDown = false;
            Drawing = false;
            break;
        default: break;
    };

    return false;
}

void RectRender()
{
    hge->Gfx_BeginScene(PicTarget);
    hge->Gfx_Clear(0xffffffff);

    picInTarget->Render(0, 0);

    for(int i = 0; i < 5; i++)
    {        
        if(NowSel->second.rect[i].x1 != NowSel->second.rect[i].x2 || NowSel->second.rect[i].y1 != NowSel->second.rect[i].y2)
        {
            LineRender(NowSel->second.rect[i].x1, NowSel->second.rect[i].y1, NowSel->second.rect[i].x2
                , NowSel->second.rect[i].y1, lnclr);

            LineRender(NowSel->second.rect[i].x2, NowSel->second.rect[i].y1, NowSel->second.rect[i].x2
                , NowSel->second.rect[i].y2, lnclr);

            LineRender(NowSel->second.rect[i].x2, NowSel->second.rect[i].y2, NowSel->second.rect[i].x1
                , NowSel->second.rect[i].y2, lnclr);

            LineRender(NowSel->second.rect[i].x1, NowSel->second.rect[i].y2, NowSel->second.rect[i].x1
                , NowSel->second.rect[i].y1 - 1, lnclr);

            char tmp[512];
            sprintf(tmp, "%d", i + 1);
            fnt->SetColor(0xffff0000);
            fnt->Render((NowSel->second.rect[i].x1 + NowSel->second.rect[i].x2) / 2, 
                (NowSel->second.rect[i].y1 + NowSel->second.rect[i].y2) / 2, 
                HGETEXT_LEFT, tmp);
        }
    }

    hge->Gfx_EndScene();
}

bool RenderFunc()
{
    if(picInTarget != NULL) RectRender();

    hge->Gfx_BeginScene();
    hge->Gfx_Clear(0x00000000);

    if(pic != NULL) 
    {
        pic->Render(PIC_MARGIN_LEFT, PIC_MARGIN_TOP);
    }
    leftbar->Render(0, 0);
    gui->Render();

    hge->Gfx_EndScene();

    return false;
}

void InitOpenDialog()
{
    ZeroMemory(&ofn, sizeof(OPENFILENAME));
    ofn.lStructSize = sizeof(OPENFILENAME); 
    ofn.hwndOwner = hge->System_GetState(HGE_HWND); 
    ofn.lpstrFilter = RES_FILTER;
    ofn.lpstrFile = szFile; 
    ofn.nMaxFile = sizeof(szFile); 
    ofn.Flags = OFN_OVERWRITEPROMPT;
    ofn.lpstrDefExt = "png";
}

bool LoadResource()
{
    string filename;
    filename = string(UI_PATH) + string("gui.png");
    g_UI = hge->Texture_Load(filename.c_str());
    filename = string(UI_PATH) + string("Font.fnt");
    fnt = new hgeFont(filename.c_str());

    if(!g_UI) return false;

    leftbar = new hgeSprite(g_UI, 0, 0, 200, 600);
    cursor = new hgeSprite(g_UI, 428, 0, 32, 32);
    ChangePicBtn1 = new CMyButton(CHANGE_PIC_ID1, new hgeSprite(g_UI, 200, 0, 76, 32),
        new hgeSprite(g_UI, 200 + 76, 0, 76, 32), new hgeSprite(g_UI, 200 + 76 + 76, 0, 76, 32),
        fnt, 230, 17, 76, 32, "First");
    ChangePicBtn2 = new CMyButton(CHANGE_PIC_ID2, new hgeSprite(g_UI, 200, 0, 76, 32),
        new hgeSprite(g_UI, 200 + 76, 0, 76, 32), new hgeSprite(g_UI, 200 + 76 + 76, 0, 76, 32),
        fnt, 306, 17, 76, 32, "Second");
    Save = new CMyButton(SAVE_ID, new hgeSprite(g_UI, 200, 0, 76, 32),
        new hgeSprite(g_UI, 200 + 76, 0, 76, 32), new hgeSprite(g_UI, 200 + 76 + 76, 0, 76, 32),
        fnt, 65, 540, 76, 32, "Save");
    LoadPic = new CMyButton(LOAD_PIC_ID, new hgeSprite(g_UI, 200, 0, 76, 32),
        new hgeSprite(g_UI, 200 + 76, 0, 76, 32), new hgeSprite(g_UI, 200 + 76 + 76, 0, 76, 32),
        fnt, 382, 17, 76, 32, "Load");
    NewPic = new CMyButton(NEW_PIC_ID, new hgeSprite(g_UI, 200, 0, 76, 32),
        new hgeSprite(g_UI, 200 + 76, 0, 76, 32), new hgeSprite(g_UI, 200 + 76 + 76, 0, 76, 32),
        fnt, 35, 260, 76, 32, "New");

    /* 列表框 */
    ListUI = new hgeGUIListbox(LISTBOX_ID, 12, 50, 160, 195, fnt, 0xffffffff, 0xffff7800, 0x88ffffff);
    for(STLMap::iterator i = M.begin(); i != M.end(); i++)
    {
        char tmp[512];
        memcpy(tmp, i->second.name.c_str(), sizeof(tmp));
        ListUI->AddItem(tmp);
    }

    //Rect列表
    ListRect = new hgeGUIListbox(LISTRECT_ID, 12, 325, 175, 200, fnt, 0xffff0099, 0xffff7800, 0x88ffffff);

    ListSlider = new hgeGUISlider(LISTSLIDER_ID, 177, 47, 14, 198, g_UI, 200, 189, 14, 200, true);
    ListSlider->SetMode(0, (float)(ListUI->GetNumItems() - ListUI->GetNumRows()), HGESLIDER_BAR);
    ListSlider->SetValue(0);

    for(int i = 1; i <= 5; i++)
    {
        char tmp[512];
        sprintf(tmp, "No. %d", i);
        ListRect->AddItem(tmp);
    }

    gui = new hgeGUI();
    gui->SetCursor(cursor);
    gui->AddCtrl(ListUI);
    gui->AddCtrl(ListRect);
    gui->AddCtrl(ListSlider);
    gui->AddCtrl(ChangePicBtn1);
    gui->AddCtrl(ChangePicBtn2);
    gui->AddCtrl(Save);
    gui->AddCtrl(LoadPic);
    gui->AddCtrl(NewPic);

    PicTarget = hge->Target_Create(503, 452, 0.5f);

    PicTexture = hge->Texture_Load(NowSel->second.pic1);
    picInTarget = new hgeSprite(PicTexture, 0, 0, 503, 452);
    picInTarget->SetZ(1);

    pic = new hgeSprite(hge->Target_GetTexture(PicTarget), 0, 0, 503, 452);

    return true;
}

bool ReadLst()
{
    string filename = string(RES_PATH) + string("Set.lst");
    strncat(szLstFile, filename.c_str(), sizeof(szLstFile));

    FILE *fp = fopen(szLstFile, "r");
    if(fp == NULL) return false;

    fscanf(fp, "%d", &_count);
    for(int i = 0; i < _count; i++)
    {
        char tmp[512];
        fscanf(fp, "%s", tmp);

        string n = string(tmp);
        M[n].name = n;

        memcpy(M[n].iniFile, RES_PATH, sizeof(M[n].iniFile));
        strncat(M[n].iniFile, tmp, sizeof(M[n].iniFile));
        strncat(M[n].iniFile, ".ini", sizeof(M[n].iniFile));

        hge->System_SetState(HGE_INIFILE, M[n].iniFile);

        string pic1 = string(tmp) + string("1.png");
        string pic2 = string(tmp) + string("2.png");

        memcpy(M[n].pic1, RES_PATH, sizeof(M[n].pic1));
        memcpy(M[n].pic2, RES_PATH, sizeof(M[n].pic2));
        memcpy(M[n].RealPic1, hge->Ini_GetString("picture", "pic1", pic1.c_str()), sizeof(M[n].RealPic1));
        memcpy(M[n].RealPic2, hge->Ini_GetString("picture", "pic2", pic2.c_str()), sizeof(M[n].RealPic2));
        strncat(M[n].pic1, hge->Ini_GetString("picture", "pic1", pic1.c_str()), sizeof(M[n].pic1));
        strncat(M[n].pic2, hge->Ini_GetString("picture", "pic2", pic2.c_str()), sizeof(M[n].pic2));
        for(int j = 0; j < 5; j++)
        {
            M[n].rect[j].x1 = hge->Ini_GetFloat(rectStr[j], "x1", 0.0f);
            M[n].rect[j].x2 = hge->Ini_GetFloat(rectStr[j], "x2", 0.0f);

            M[n].rect[j].y1 = hge->Ini_GetFloat(rectStr[j], "y1", 0.0f);
            M[n].rect[j].y2 = hge->Ini_GetFloat(rectStr[j], "y2", 0.0f);
        }
    }

    fclose(fp);

    char tmp[512];

    NowSel = M.begin();
    PicNumSel = 1;

    //MessageBox(NULL, NowSel->second.pic1, NowSel->second.pic1, MB_ICONERROR);

    return true;
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	hge = hgeCreate(HGE_VERSION);

	hge->System_SetState(HGE_INIFILE, "PicMaker.ini");
	hge->System_SetState(HGE_LOGFILE, "PicMaker.log");
	hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
	hge->System_SetState(HGE_RENDERFUNC, RenderFunc);
	hge->System_SetState(HGE_TITLE, "Zhaocha Picture Editor");
	hge->System_SetState(HGE_SCREENWIDTH, 800);
	hge->System_SetState(HGE_SCREENHEIGHT, 600);
	hge->System_SetState(HGE_SCREENBPP, 32);
	hge->System_SetState(HGE_USESOUND, false);
    hge->System_SetState(HGE_WINDOWED, true);
    hge->System_SetState(HGE_GFXRESTOREFUNC, GfxRestoreFunc);
    hge->System_SetState(HGE_ZBUFFER, true);
    hge->System_SetState(HGE_ICON, "IDI_ICON1");

    memcpy(ResPath, hge->Ini_GetString("set", "ResPath", "NULL"), sizeof(ResPath));

    hge->Resource_AttachPack("UI.x2pak", "X2Studio");

    InitOpenDialog();
    if(!ReadLst()) exit(0);
    
    if(hge->System_Initiate())
    {
        if(!LoadResource())
        {
            MessageBox(NULL, "资源错误！", "错误", MB_ICONSTOP);
            exit(0);
        }
        hge->System_Start();
    }
    else MessageBox(NULL, "初始化错误！", "错误", MB_ICONSTOP);

    hge->System_Shutdown();
    hge->Release();

    return 0;
}
