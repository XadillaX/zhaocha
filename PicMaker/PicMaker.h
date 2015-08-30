#define RES_PATH                        "ZhaoChaPicture/"
#define RES_FILTER                      "PNG Picture(*.png)\0*.png\0\0"
#define UI_PATH                         "ZhaoChaUI/"

#define LISTBOX_ID                      11
#define LISTSLIDER_ID                   12
#define LISTRECT_ID                     20
#define CHANGE_PIC_ID1                  13
#define CHANGE_PIC_ID2                  14
#define LOAD_PIC_ID                     15
#define NEW_PIC_ID                     16
#define SAVE_ID                         21
#define PIC_MARGIN_LEFT                 230
#define PIC_MARGIN_TOP                  50

#include <hge.h>
#include <hgegui.h>
#include <hgeguictrls.h>
#include <hgesprite.h>
#include <map>
#include <string>
#include < fstream >
using namespace std;

struct zcp {
    string name;
    hgeRect rect[5];
    char iniFile[512];
    char pic1[512], pic2[512], RealPic1[512], RealPic2[512];
};

char *rectStr[5] = { "rect1", "rect2", "rect3", "rect4", "rect5" };
map<string, zcp> M;
int _count = 0;
int nLastSelected = 0;
HGE *hge = NULL;

typedef map<string, zcp> STLMap;
STLMap::iterator NowSel;

void LineRender(float x1, float y1, float x2, float y2, int color[])
{
    int offset[3] = { 1, 0, -1 };
    if(y1 == y2)
    {
        for(int i = -1; i <= 1; i++)
        {
            hge->Gfx_RenderLine(x1 - offset[i + 1], y1 + i, x2 + offset[i + 1], y2 + i, color[i + 1], 0);
        }
    }
    else
    if(x1 == x2)
    {
        for(int i = -1; i <= 1; i++)
        {
            hge->Gfx_RenderLine(x1 + i, y1 + offset[i + 1], x2 + i, y2 - offset[i + 1], color[i + 1], 0);
        }
    }
}