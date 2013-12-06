// classtile.cpp: implementation of the classtile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "classtile.h"
#ifndef INCLUDE_MAINFRAME
#define INCLUDE_MAINFRAME
#include "MainFrm.h"
#include <assert.h>
#endif
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/*#ifndef TILES_STRUCT
#define TILES_STRUCT
extern struct tiles{//TILE链表
int tileiid;//内部标记
int tile_width;
int tile_height;
//char imagesrc[300];
char *imagesrc;//这样效率低，但是不用担心转换数组大小问题。
RECT tilerect;//所在的矩形位置
tiles *next;
}*tiles_struct;
#endif
*/
//##ModelId=4A1E847303A9
classtile::classtile()
{

}

//##ModelId=4A1E847303AA
classtile::~classtile()
{

}

//##ModelId=4A1E847303A7
bool classtile::GetTileInfo()//获取TILE节点
{
	if(!this->CheckOK())
		return 0;
	static int i;
	i++;
	CString cs;
	cs.Format("%d",i);
	
		AfxMessageBox(cs);
	return 1;
}

//##ModelId=4A1E847303A8
bool classtile::CheckOK()//检查是否可以开始重绘了
{
	CMainFrame *pMf=(CMainFrame*)AfxGetMainWnd();
	if (pMf->m_settileok && pMf->m_setmapok){
		if ( (pMf->m_tilewidth!=0) && (pMf->m_tileheight!=0) && (pMf->m_maphtiles!=0) && (pMf->m_mapvtiles!=0))
		{
			return true;
		}
	}
	return false;
}

//##ModelId=4A1E847303A5
struct tiles * classtile::CreateTilelist( tparam * t)//创建tile链表
{
CMainFrame * pMf=(CMainFrame *)AfxGetMainWnd();
if (pMf->m_Pt_tiles_linklist_headernode!=NULL)
free(pMf->m_Pt_tiles_linklist_headernode);
//读取位图长度
	HBITMAP hbitmap=(HBITMAP)LoadImage(AfxGetInstanceHandle(),t->imagesrc,IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE|LR_CREATEDIBSECTION);

	CDC compatible;
	//compatible.CreateCompatibleDC(pDC);
	compatible.SelectObject(hbitmap);
	//此处获取位图大小，计算有多少TILE，这样就可以BLT多少次。多余的边角料不选
	CBitmap   bm;   
	BITMAP   bwh;
	bm.Attach(hbitmap);   
	bm.GetObject(sizeof(BITMAP) , &bwh);   
	bm.Detach();  
	DeleteObject(hbitmap);
	int i;//bitblt的次数,就是节点数
	i=bwh.bmWidth/t->tile_width;//这样能去掉边角料，即余数不要
	int lastwidth=i*t->tile_width;
	//CString lw;
	//lw.Format("%d",lastwidth);
	//AfxMessageBox(lw);
//

	struct tiles *h,*p,*s;//头结点，前节点，当前节点
	h = (struct tiles *)malloc(sizeof(struct tiles));
	h->next=NULL;
	p=h;
	for (int j=0;j<i;j++){//为链表各节点赋值
	s=(struct tiles *)malloc(sizeof(struct tiles));
	s->tileiid=j;//0开始编号
	//保留
	s->imagesrc=t->imagesrc;
	s->tile_height=t->tile_height;
	s->tile_width=t->tile_width;
	s->tilerect.top=0;
	s->tilerect.bottom=s->tilerect.top+t->tile_height-1;
	if (j==0){ //头结点的left
		s->tilerect.left=0;
	}
	else{
		s->tilerect.left=p->tilerect.left+t->tile_width;
	}
	if (j==0){//头结点的right
		s->tilerect.right=0+t->tile_width-1;
	}
	else{
		s->tilerect.right=s->tilerect.left+t->tile_width-1;
	}
	p->next=s;
	s->next=NULL;//否则遍历到最后一个节点没有初始化会出错@！
	p=s;
	}

//AfxMessageBox("创建TILE链表OK");

return h;//返回头节点
}

//根据tile的id查询出tile的属性
//s传入参数头结点
//##ModelId=4A1E84730394
struct tiles * classtile::gettile(struct tiles * s,int tileiid)
{
	while(s->tileiid!=tileiid){
		s=s->next;
	}
	if(s==NULL){
		assert("linklist id not match");
	}
	else{
		return s;
	}
	return NULL;
}
