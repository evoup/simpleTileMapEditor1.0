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
extern struct tiles{//TILE����
int tileiid;//�ڲ����
int tile_width;
int tile_height;
//char imagesrc[300];
char *imagesrc;//����Ч�ʵͣ����ǲ��õ���ת�������С���⡣
RECT tilerect;//���ڵľ���λ��
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
bool classtile::GetTileInfo()//��ȡTILE�ڵ�
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
bool classtile::CheckOK()//����Ƿ���Կ�ʼ�ػ���
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
struct tiles * classtile::CreateTilelist( tparam * t)//����tile����
{
CMainFrame * pMf=(CMainFrame *)AfxGetMainWnd();
if (pMf->m_Pt_tiles_linklist_headernode!=NULL)
free(pMf->m_Pt_tiles_linklist_headernode);
//��ȡλͼ����
	HBITMAP hbitmap=(HBITMAP)LoadImage(AfxGetInstanceHandle(),t->imagesrc,IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE|LR_CREATEDIBSECTION);

	CDC compatible;
	//compatible.CreateCompatibleDC(pDC);
	compatible.SelectObject(hbitmap);
	//�˴���ȡλͼ��С�������ж���TILE�������Ϳ���BLT���ٴΡ�����ı߽��ϲ�ѡ
	CBitmap   bm;   
	BITMAP   bwh;
	bm.Attach(hbitmap);   
	bm.GetObject(sizeof(BITMAP) , &bwh);   
	bm.Detach();  
	DeleteObject(hbitmap);
	int i;//bitblt�Ĵ���,���ǽڵ���
	i=bwh.bmWidth/t->tile_width;//������ȥ���߽��ϣ���������Ҫ
	int lastwidth=i*t->tile_width;
	//CString lw;
	//lw.Format("%d",lastwidth);
	//AfxMessageBox(lw);
//

	struct tiles *h,*p,*s;//ͷ��㣬ǰ�ڵ㣬��ǰ�ڵ�
	h = (struct tiles *)malloc(sizeof(struct tiles));
	h->next=NULL;
	p=h;
	for (int j=0;j<i;j++){//Ϊ������ڵ㸳ֵ
	s=(struct tiles *)malloc(sizeof(struct tiles));
	s->tileiid=j;//0��ʼ���
	//����
	s->imagesrc=t->imagesrc;
	s->tile_height=t->tile_height;
	s->tile_width=t->tile_width;
	s->tilerect.top=0;
	s->tilerect.bottom=s->tilerect.top+t->tile_height-1;
	if (j==0){ //ͷ����left
		s->tilerect.left=0;
	}
	else{
		s->tilerect.left=p->tilerect.left+t->tile_width;
	}
	if (j==0){//ͷ����right
		s->tilerect.right=0+t->tile_width-1;
	}
	else{
		s->tilerect.right=s->tilerect.left+t->tile_width-1;
	}
	p->next=s;
	s->next=NULL;//������������һ���ڵ�û�г�ʼ�������@��
	p=s;
	}

//AfxMessageBox("����TILE����OK");

return h;//����ͷ�ڵ�
}

//����tile��id��ѯ��tile������
//s�������ͷ���
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
