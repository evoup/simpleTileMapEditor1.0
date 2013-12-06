// LeftTreeView.cpp : implementation file
//

#include "stdafx.h"
#include "SplitWndDemo.h"
#include "LeftTreeView.h"
#include "RightView.h"
#include "MainFrm.h"
#include "common.h"
#include <vector>
#include "classtile.h"
#include <fstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
using namespace std;



//Todo:������ѿ��Ķ����ŵ�����
static vector<vector<map_matrix> > Matrix(DEF_V, vector<map_matrix>((int)DEF_H));


//��ô��ֻ�ܵõ���ά��ָ�룬��������Ҫ��ָ���ά�����ָ�롣
//vector<vector<map_matrix> > *va=new vector<vector<map_matrix> >();
//vector<vector<map_matrix> > *mx=new vector<vector<map_matrix> >(H, vector<map_matrix>((int)V));
//����������Ա��//http://topic.csdn.net/t/20060101/14/4494017.html
//vector<vector<map_matrix> > CLeftTreeView::Matrix(222, vector<map_matrix>(223));

/////////////////////////////////////////////////////////////////////////////
// CLeftTreeView

IMPLEMENT_DYNCREATE(CLeftTreeView, CScrollView)

//##ModelId=4A1E8473024B
CLeftTreeView::CLeftTreeView()
{	

	this->m_draw_which_layer=0;//Ĭ�ϻ������
	this->m_view_which_layer=-1;//Ĭ����ʾ���в�
	//pMf= (CMainFrame*)AfxGetMainWnd();
	//��ʼ������
	for(int i=0;i<DEF_V;i++){
		for (int j=0;j<DEF_H;j++){
			Matrix[i][j].therect.top=0;
			Matrix[i][j].therect.left=0;
			Matrix[i][j].tileiid=-1;
			Matrix[i][j].layer_obj_tileiid=-1;
			Matrix[i][j].layer_obj2_tileiid=-1;
			Matrix[i][j].layer_sky_tileiid=-1;
			Matrix[i][j].layer_obstacle=0;//�ϰ�0Ϊ�ޣ�1Ϊ��
		}
	}
	this->m_lbutton_is_down=false;
	this->m_erase=-1;//��Ƥ�����,-1��û��ѡ����Ƥ����1��С����2���в���3�Ǵ��
	this->cur=AfxGetApp()->LoadCursor(IDC_OBSTACLE);
}

//##ModelId=4A1E84730299
CLeftTreeView::~CLeftTreeView()
{
}


BEGIN_MESSAGE_MAP(CLeftTreeView, CScrollView)
//{{AFX_MSG_MAP(CLeftTreeView)
ON_WM_LBUTTONDOWN()
ON_WM_LBUTTONUP()
	ON_COMMAND(IDM_EXPORT_CODE, OnExportCode)
	ON_WM_MOUSEMOVE()
	ON_COMMAND(IDM_ERASE_SMALL, OnEraseSmall)
	ON_COMMAND(IDM_ERASE_MIDDLE, OnEraseMiddle)
	ON_COMMAND(IDM_ERASE_BIG, OnEraseBig)
	ON_WM_SETCURSOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLeftTreeView drawing

//##ModelId=4A1E8473028C
void CLeftTreeView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here

	if (this->CheckOK()){
		SetScrollSizes(MM_TEXT,CSize(pMf->m_tilewidth*pMf->m_maphtiles,pMf->m_tileheight*pMf->m_mapvtiles));//��������MAP��SCROLL��С	
		
		//CMainFrame *pMf=(CMainFrame*)AfxGetMainWnd();
	//int s=this->GetDeviceScrollPosition().x;
	
		CRightView * pView=(CRightView*)(((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(1,0));
		pView->Invalidate();
	}
	else return;
	
	
	//�ػ汳��
	
#if 1
	
	pMf=(CMainFrame*)AfxGetMainWnd();
	if ( (pMf->m_tilewidth!=0) && (pMf->m_tileheight!=0) && (pMf->m_maphtiles!=0) && (pMf->m_mapvtiles!=0))
	{
		
		//��ͼ����

		CClientDC hdc(this);

		CString bitmappath=pMf->m_bitmap_pathname;
		
		HBITMAP hbitmap=(HBITMAP)LoadImage(AfxGetInstanceHandle(),bitmappath,IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE|LR_CREATEDIBSECTION);
		
		CDC compatible;
		
		compatible.CreateCompatibleDC(NULL);
		
		compatible.SelectObject(hbitmap);//�ǿ��Դ��ݾ���ģ�MSDNû��������
		
		//Todo������Ҫ�Ȱѽṹ��ʼ����
		if (pMf->m_b_is_transok){
			classtile tileobj;
			struct tiles * ttile;

			//[��һ���Ż�]����ͻ���������ЩTILE��ֻ����Щ��BLT,һ�㲻�ᳬ������Ļ�ɣ���������ĻΪ��Χ��
#if 1//���´������Oscroll���ԣ�ʵ����Ϊ��Ondraw���Ż�
			/************************************************************************/
			/* ͨ�����Ͻ����������ЩTILE����Ҫ���µ�                               */
			/************************************************************************/
			CPoint upleft_pt;//�༭�������Ͻ�����
			//char buf[20];
			int H=((CMainFrame*)AfxGetMainWnd())->m_maphtiles,//ˮƽTILE��
				int V=((CMainFrame*)AfxGetMainWnd())->m_mapvtiles;//��ֱTILE��
			upleft_pt.x=this->GetDeviceScrollPosition().x;
			upleft_pt.y=this->GetDeviceScrollPosition().y;
			
			//�жϵ�ǰ���������ĸ�rect,reali,realj�������blt���꣨��ǰ���ϣ�
			int real_i,real_j;//��¼��������Ԫ��
			for (int i=0;i<V;i++){
				for(int j=0;j<H;j++){
					if (upleft_pt.x>=Matrix[i][j].therect.left && upleft_pt.x<=Matrix[i][j].therect.right
						&& upleft_pt.y>=Matrix[i][j].therect.top && upleft_pt.y<=Matrix[i][j].therect.bottom){
						real_i=i;
						real_j=j;
					}
				}
			}
			
			
			//����༭����ʵ���ϵĳߴ�
			
			//���������Ǵ����ϵ�Matrix[i][j]�����µ�
			RECT thewindowrect;
			GetWindowRect(&thewindowrect);
			int window_w=thewindowrect.right-thewindowrect.left;
			int window_h=thewindowrect.bottom-thewindowrect.top;
			//�����Ͻǵ㿪ʼ����TILE��
			int y_tile_nums=window_h/((CMainFrame*)AfxGetMainWnd())->m_tilewidth+1;//������1��
			int x_tile_nums=window_w/((CMainFrame*)AfxGetMainWnd())->m_tileheight+1;
#endif//ͨ��real_i,real_j,y_tile_nums,x_tile_nums�Ϳ���������Щtiles����ҪBlt��



			int CXScreen=::GetSystemMetrics(SM_CXSCREEN);
			int CYScreen=::GetSystemMetrics(SM_CYSCREEN);
			/*char buf[20];
			sprintf(buf,"%d",CYScreen);
			AfxMessageBox(buf,MB_OK);*/
#if 1	
			int j;
			int dstx,dsty;
			switch (this->m_view_which_layer){
			case -1 ://��ʾ���в�Ļ�
				for (i=0;i<DEF_V;i++){
					for (j=0;j<DEF_H;j++){//��ѯtileid��Ӧ��tile��Ϣ������ָ��
#if 1
						//����ʾ�����
						if(Matrix[i][j].tileiid!=-1){
							ttile=tileobj.gettile(this->pMf->m_Pt_tiles_linklist_headernode,\
								Matrix[i][j].tileiid);
							if ((i>=real_i || real_i<=i+y_tile_nums) && \
								(j>=real_j || real_j<=j+x_tile_nums)
								)//[��һ���Ż�]
							{
								::BitBlt(hdc,Matrix[i][j].therect.left-GetScrollPosition ().x,Matrix[i][j].therect.top-GetScrollPosition ().y,\
									((CMainFrame*)AfxGetMainWnd())->m_tilewidth,((CMainFrame*)AfxGetMainWnd())->m_tileheight,\
									compatible,ttile->tilerect.left,ttile->tilerect.top,\
								SRCCOPY);
							}
						}//end if
#endif
						//Sleep(0.1);
						//����ʾ�����1
						if(Matrix[i][j].layer_obj_tileiid!=-1){
							ttile=tileobj.gettile(this->pMf->m_Pt_tiles_linklist_headernode,\
								Matrix[i][j].layer_obj_tileiid);	
							dstx=Matrix[i][j].therect.left-GetScrollPosition ().x;
							dsty=Matrix[i][j].therect.top-GetScrollPosition ().y;
							if ((i>=real_i || real_i<=i+y_tile_nums) && \
								(j>=real_j || real_j<=j+x_tile_nums)
								){//[��һ���Ż�]
								if(false==TransparentBlt(
									hdc,        // handle to destination DC
									dstx,   // x-coord of destination upper-left corner
									dsty,   // y-coord of destination upper-left corner
									pMf->m_tilewidth,     // width of destination rectangle
									pMf->m_tileheight,    // height of destination rectangle
									compatible,         // handle to source DC
									ttile->tilerect.left,    // x-coord of source upper-left corner
									ttile->tilerect.top,    // y-coord of source upper-left corner
									pMf->m_tilewidth,      // width of source rectangle
									pMf->m_tileheight,     // height of source rectangle
									RGB(255, 0, 255)  // color to make transparent
									)){
									AfxMessageBox("�д�����ѡ���ͼƬ�����õ�TileҪС��",MB_OK);
								}//endif
							}
						}//endif
						//������ʾ�����1
						//����ʾ�����2
						if(Matrix[i][j].layer_obj2_tileiid!=-1){
							ttile=tileobj.gettile(this->pMf->m_Pt_tiles_linklist_headernode,\
								Matrix[i][j].layer_obj2_tileiid);	
							dstx=Matrix[i][j].therect.left-GetScrollPosition ().x;
							dsty=Matrix[i][j].therect.top-GetScrollPosition ().y;
							if ((i>=real_i || real_i<=i+y_tile_nums) && \
								(j>=real_j || real_j<=j+x_tile_nums)
								){//[��һ���Ż�]
								if(false==TransparentBlt(
									hdc,        // handle to destination DC
									dstx,   // x-coord of destination upper-left corner
									dsty,   // y-coord of destination upper-left corner
									pMf->m_tilewidth,     // width of destination rectangle
									pMf->m_tileheight,    // height of destination rectangle
									compatible,         // handle to source DC
									ttile->tilerect.left,    // x-coord of source upper-left corner
									ttile->tilerect.top,    // y-coord of source upper-left corner
									pMf->m_tilewidth,      // width of source rectangle
									pMf->m_tileheight,     // height of source rectangle
									RGB(255, 0, 255)  // color to make transparent
									)){
									AfxMessageBox("�д�����ѡ���ͼƬ�����õ�TileҪС��",MB_OK);
								}//endif
							}
						}//endif
						//������ʾ�����2
					}//end for
				}//end for
				break;
			case 0://����ʾ�����
				for (i=0;i<DEF_V;i++){
					for (j=0;j<DEF_H;j++){//��ѯtileid��Ӧ��tile��Ϣ������ָ��
						if(Matrix[i][j].tileiid!=-1){
							ttile=tileobj.gettile(this->pMf->m_Pt_tiles_linklist_headernode,\
								Matrix[i][j].tileiid);	
							if ((i>=real_i || real_i<=i+y_tile_nums) && \
								(j>=real_j || real_j<=j+x_tile_nums)
								){//[��һ���Ż�]
								::BitBlt(hdc,Matrix[i][j].therect.left-GetScrollPosition ().x,Matrix[i][j].therect.top-GetScrollPosition ().y,\
									((CMainFrame*)AfxGetMainWnd())->m_tilewidth,((CMainFrame*)AfxGetMainWnd())->m_tileheight,\
									compatible,ttile->tilerect.left,ttile->tilerect.top,\
									SRCCOPY);
							}
						}//end if
					}//end for
				}//end for
				break;
			case 1://����ʾ�����1
				for (i=0;i<DEF_V;i++){
					for (j=0;j<DEF_H;j++){//��ѯtileid��Ӧ��tile��Ϣ������ָ��
						if(Matrix[i][j].layer_obj_tileiid!=-1){
							ttile=tileobj.gettile(this->pMf->m_Pt_tiles_linklist_headernode,\
								Matrix[i][j].layer_obj_tileiid);
							if ((i>=real_i || real_i<=i+y_tile_nums) && \
								(j>=real_j || real_j<=j+x_tile_nums)
								){//[��һ���Ż�]
								TransparentBlt(
									hdc,        // handle to destination DC
									Matrix[i][j].therect.left-GetScrollPosition ().x,   // x-coord of destination upper-left corner
									Matrix[i][j].therect.top-GetScrollPosition ().y,   // y-coord of destination upper-left corner
									pMf->m_tilewidth,     // width of destination rectangle
									pMf->m_tileheight,    // height of destination rectangle
									compatible,         // handle to source DC
									ttile->tilerect.left,    // x-coord of source upper-left corner
									ttile->tilerect.top,    // y-coord of source upper-left corner
									pMf->m_tilewidth,      // width of source rectangle
									pMf->m_tileheight,     // height of source rectangle
									RGB(255, 0, 255)  // color to make transparent
									);
							}
						}//end if
					}//end for
				}//end for
				break;
			case 2://����ʾ�����2
				for (i=0;i<DEF_V;i++){
					for (j=0;j<DEF_H;j++){//��ѯtileid��Ӧ��tile��Ϣ������ָ��
						if(Matrix[i][j].layer_obj2_tileiid!=-1){
							ttile=tileobj.gettile(this->pMf->m_Pt_tiles_linklist_headernode,\
								Matrix[i][j].layer_obj2_tileiid);
							if ((i>=real_i || real_i<=i+y_tile_nums) && \
								(j>=real_j || real_j<=j+x_tile_nums)
								){//[��һ���Ż�]
								TransparentBlt(
									hdc,        // handle to destination DC
									Matrix[i][j].therect.left-GetScrollPosition ().x,   // x-coord of destination upper-left corner
									Matrix[i][j].therect.top-GetScrollPosition ().y,   // y-coord of destination upper-left corner
									pMf->m_tilewidth,     // width of destination rectangle
									pMf->m_tileheight,    // height of destination rectangle
									compatible,         // handle to source DC
									ttile->tilerect.left,    // x-coord of source upper-left corner
									ttile->tilerect.top,    // y-coord of source upper-left corner
									pMf->m_tilewidth,      // width of source rectangle
									pMf->m_tileheight,     // height of source rectangle
									RGB(255, 0, 255)  // color to make transparent
									);
							}
						}//end if
					}//end for
				}//end for
				break;
			case 7://����ʾ��ղ�
				break;
			}//end switch
#endif

		}//end if pMf->m_b_is_transok
		//end ��ͼ
		ReleaseDC(&compatible);
		DeleteObject(hbitmap);
	}//end if pMf->m_tilewidth!=0) && (pMf->m_tileheight!=0 ...
	
#endif
	
}

/////////////////////////////////////////////////////////////////////////////
// CLeftTreeView diagnostics

#ifdef _DEBUG
//##ModelId=4A1E847302A9
void CLeftTreeView::AssertValid() const
{
	CScrollView::AssertValid();
}

//##ModelId=4A1E847302B9
void CLeftTreeView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLeftTreeView message handlers

//##ModelId=4A1E8473027A
void CLeftTreeView::OnInitialUpdate() 
{
	CScrollView::OnInitialUpdate();
	// TODO: Add your specialized code here and/or call the base class
	//this->InitialDBB();//��Ҫ˫������
	
	SetScrollSizes(MM_TEXT,CSize(1800,5600));
}

//##ModelId=4A1E847302C8
void CLeftTreeView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
/////////////////
	this->m_lbutton_is_down=true;
		//if (this->m_draw_which_layer==0){
			this->DrawTile(point);
	//}

/////////////////
	CScrollView::OnLButtonDown(nFlags, point);
}


//##ModelId=4A1E847302D8
void CLeftTreeView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	this->m_lbutton_is_down=false;
#if 0
	HDC hdc;
	hdc=::GetDC(this->m_hWnd);
	::MoveToEx(hdc,m_ptOrigin.x,m_ptOrigin.y,NULL);
	::LineTo(hdc,point.x,point.y);
	::ReleaseDC(this->m_hWnd,hdc);
#endif
	CScrollView::OnLButtonUp(nFlags, point);
}


//��ʼ��GDI˫����
//##ModelId=4A1E8473026F
void CLeftTreeView::InitialDBB()
{
	CRect rt;
	this->GetClientRect(&rt);
	
	// Ϊ��ĻDC�������ݵ��ڴ�DC
	if(!m_dcMemory.CreateCompatibleDC(NULL))				
	{														
		::PostQuitMessage(0);
	}	
	
	// ����λͼ
	m_Bmp.CreateCompatibleBitmap(&m_dcMemory, rt.Width(), rt.Height());
	
	// �൱��ѡ�񻭲�
	::SelectObject(m_dcMemory.GetSafeHdc(), m_Bmp);			
	MessageBox("GDI˫�����ʼ�����");
}

//BOOL CLeftTreeView::OnEraseBkgnd(CDC *pDC){//��ô���μ�VCKBASE���ƻ�ͼ���С����
	//	����Ҳû���ã�
//	return true;
//}



//##ModelId=4A1E8473025F
bool CLeftTreeView::CheckOK()
{
	pMf=(CMainFrame*)AfxGetMainWnd();
	if (pMf->m_settileok && pMf->m_setmapok){
		if ( (pMf->m_tilewidth!=0) && (pMf->m_tileheight!=0) && (pMf->m_maphtiles!=0) && (pMf->m_mapvtiles!=0))
		{
			return true;
		}
	}
	return false;
}
//abandoned!
//##ModelId=4A1E8473025D
bool CLeftTreeView::getMatrix(vector<vector<map_matrix> >& v)
{
	CString cs;
	cs.Format("%d",v[0][0].tileiid);
	MessageBox(cs);
	return 1;
}

//##ModelId=4A1E8473027C
BOOL CLeftTreeView::OnScroll(UINT nScrollCode, UINT nPos, BOOL bDoScroll) 
{
	// TODO: Add your specialized code here and/or call the base class
#if 0//���´�����ڴ˴����ԣ�ʵ����Ϊ��Ondraw���Ż�
	/************************************************************************/
	/* ͨ�����Ͻ����������ЩTILE����Ҫ���µ�                               */
	/************************************************************************/
	CPoint upleft_pt;//�༭�������Ͻ�����
	//char buf[20];
	int H=((CMainFrame*)AfxGetMainWnd())->m_maphtiles,//ˮƽTILE��
	int V=((CMainFrame*)AfxGetMainWnd())->m_mapvtiles;//��ֱTILE��
	upleft_pt.x=this->GetDeviceScrollPosition().x;
	upleft_pt.y=this->GetDeviceScrollPosition().y;

	//�жϵ�ǰ���������ĸ�rect,reali,realj�������blt���꣨��ǰ���ϣ�
	int real_i,real_j;//��¼��������Ԫ��
	for (int i=0;i<V;i++){
		for(int j=0;j<H;j++){
			if (upleft_pt.x>=Matrix[i][j].therect.left && upleft_pt.x<=Matrix[i][j].therect.right
				&& upleft_pt.y>=Matrix[i][j].therect.top && upleft_pt.y<=Matrix[i][j].therect.bottom){
				real_i=i;
				real_j=j;
			}
		}
	}


//����༭����ʵ���ϵĳߴ�
	
//���������Ǵ����ϵ�Matrix[i][j]�����µ�
	RECT thewindowrect;
	GetWindowRect(&thewindowrect);
	int window_w=thewindowrect.right-thewindowrect.left;
	int window_h=thewindowrect.bottom-thewindowrect.top;
	//�����Ͻǵ㿪ʼ����TILE��
	int y_tile_nums=window_h/((CMainFrame*)AfxGetMainWnd())->m_tilewidth+1;//������1��
	int x_tile_nums=window_w/((CMainFrame*)AfxGetMainWnd())->m_tileheight+1;
#endif

//	this->Invalidate();//Todo:2009-10-9 0:15��Ҫˢ�£����Լ���һ��ˢ�µ�ʹ�࣡
	//sprintf(buf,"%d",s);
	//MessageBox(buf,"",MB_OK);
	return CScrollView::OnScroll(nScrollCode, nPos, bDoScroll);
}


//##ModelId=4A1E847302DC
void CLeftTreeView::OnExportCode() 
{
	// TODO: Add your command handler code here
	//CString ss;
	//ss.Format("%d",Matrix[0][0].tileiid);
	//MessageBox(ss);
	if (!this->CheckOK()) return;
	//�����ɵ�ͼ���롿for map�㷨1
	//Todo:���MAP1���ɵ�ͼ�㷨�����ϳ��ˣ�û�б�Ҫ�����ˣ��´�ɾ����
	FILE *fp;
	if( (fp = fopen( "the_code.code", "w+t" )) != NULL )
	{
		//char strptr1[] = "This is a test of fputc!!\n";
		//char *p=strptr1;
		//while( (*p != '\0') && fputc( *(p++), fp ) != EOF ) ;
		/*#define TILE_SIZE       32
		#define WORLD_SIZEX     60
		#define WORLD_SIZEY     60
		#define SCREEN_SIZEX    20
#define SCREEN_SIZEY    15*/
		char buffer[300];
		CMainFrame *pMf=(CMainFrame*)AfxGetMainWnd();
		sprintf(buffer, "#define TILE_SIZE %d\n", pMf->m_tilewidth);
		fputs( buffer, fp );
		sprintf(buffer, "#define WORLD_SIZEX %d\n", pMf->m_maphtiles);
		fputs( buffer, fp );
		sprintf(buffer, "#define WORLD_SIZEY %d\n", pMf->m_mapvtiles);
		fputs( buffer, fp );
		sprintf(buffer,"unsigned short  map[WORLD_SIZEY][WORLD_SIZEX]=\n");
		fputs(buffer,fp);
		sprintf(buffer,"{");
		fputs(buffer,fp);

		CString matrixrow;
		CString temp_str;
		CString comm;
		comm.Format("%s",",");
		for (int i=0;i<(pMf->m_mapvtiles);i++){
			matrixrow.Empty();
			fputs("{",fp);
			for (int j=0;j<(pMf->m_maphtiles);j++){
				temp_str.Format("%d",Matrix[i][j].tileiid);
				matrixrow+=temp_str.GetBuffer(sizeof(temp_str));
				if(j!=(pMf->m_maphtiles-1)){
				matrixrow+=comm;//����������һ��ˮƽTILEID������϶���
				}
			}
			fputs(matrixrow,fp);
			if(i!=(pMf->m_mapvtiles)){
				fputs("}",fp);
				if(i!=(pMf->m_mapvtiles-1)){
					fputs(",",fp);
				}
				fputs("\n",fp);
			}
		}
		sprintf(buffer,"};");
		fputs(buffer,fp);
		fclose( fp );
	}
	//�����ɶ����Ƶ�ͼ�ļ���for map�㷨2
	MessageBox("���ɶ����Ƶ�ͼ�ļ�");
	//from gamedev.net
	int x, y;
	// generate a random map -- this should be replaced by a nice
	// map editor when you get a chance :)
	//BYTE byMap[60][60][2];//��ʱֻ��һ���ͼ
	//BYTE byMap[pMf->m_maphtiles][pMf->m_mapvtiles][1];
//STL��ά������ʾbyMap[x][y][z]

	//int m=pMf->m_mapvtiles;
    //int n=pMf->m_maphtiles;
	int v=pMf->m_mapvtiles;
    int h=pMf->m_maphtiles;

    //int l=1;//��ʱ��һά
	int l=3;
    vector<vector<vector<BYTE> > > byMap(v,vector<vector<BYTE> >(h,vector<BYTE>(l)));
	for(x=0;x<v;x++){
		for(y=0;y<h;y++){
			//byMap[x][y][0]=Matrix[x][y].tileiid;
			if(Matrix[x][y].tileiid==-1)
				byMap[x][y][0]=0;
			else{
				byMap[x][y][0]=Matrix[x][y].tileiid;
				//byMap[x][y][1]=0;//�ڶ���ͼƬΪ0��
				//byMap[x][y][1]=-1;//�ڶ���ͼƬΪ-1
				byMap[x][y][1]=Matrix[x][y].layer_obj_tileiid;
				byMap[x][y][2]=Matrix[x][y].layer_obj2_tileiid;

			}
		}
	}
//	MessageBox("22","",MB_OK);
	CString css;
	css.Format("%d",byMap[0][0][2]);
	//css.Format("%d",Matrix[0][0].tileiid);
	//AfxMessageBox(css,MB_OK);
	/*byMap[0][0][0]=1;
	byMap[0][1][0]=1;
	byMap[0][2][0]=1;
	byMap[0][3][0]=1;
	byMap[0][4][0]=1;
	byMap[0][5][0]=1;
	byMap[0][6][0]=1;
	byMap[0][7][0]=1;
	byMap[0][8][0]=1;
	byMap[0][9][0]=1;
	byMap[0][10][0]=1;
	byMap[1][3][0]=1;
	byMap[1][4][0]=1;
	byMap[1][5][0]=1;*/
	// write map to file
	FILE *pfile = fopen("testmap.dat", "wb");
	//fputs("Map:",pfile);
	//putc(h-1, pfile);//ǰ2���������mapdata.xMax��mapdata.yMax,��ȥ1����ΪDEMO��ͼ������±�0��ʼ
	//putc(v-1, pfile);
	char bufstr1[4];
	char bufstr2[4];
	itoa(h,bufstr1,10);
	itoa(v,bufstr2,10);
	fputs("Map:",pfile);//�����ȷ�1���ַ�������DEMO��sscanfƥ�䲻����
	fputs("H",pfile);
	fputs(bufstr1,pfile);
	fputs("V",pfile);//��H��ͼ�������V��ͼ��������|��
	fputs(bufstr2,pfile);
	fputs("|",pfile);
//ofstream  mylog("testlog.txt");
//string str;
//char itoabuf[20];

	for (x=0; x<v; x++)
	{
		for (y=0; y<h; y++)
		{
			putc(byMap[x][y][0], pfile);
			putc(byMap[x][y][1], pfile);
			putc(byMap[x][y][2], pfile);
//			str.append(" ");
//			itoa(byMap[x][y][2],itoabuf,100);
//			str.append(itoabuf);
		}
//		str.append("\n");
	}
	fclose(pfile);
//	mylog.write(str.c_str(),str.length());
}

//##ModelId=4A1E847302E7
void CLeftTreeView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	//////////////////////////
	if (this->m_lbutton_is_down)
		this->DrawTile(point);
	if (this->m_erase!=-1){
		CClientDC dc(this);
		HBRUSH hBrush=CreateSolidBrush(RGB(0,255,0));
		CBrush brush(RGB(255,255,255));
		CPen pen(PS_SOLID, 3, RGB(0, 0, 0));
		CPen * Pdc = (CPen *)(dc.SelectObject(&pen));
		dc.Rectangle(10, 10, 100, 100);
		CRect rect(10,10,100,100);
		dc.FillRect(&rect,&brush);


	}
	if (((CMainFrame *)AfxGetMainWnd())->erasersur)
	{
	//HCURSOR cur11;
	::SetCursor(cur); 
	//((CMainFrame *)AfxGetMainWnd())->erasersur=0;
}
//////////////////////////////
	CScrollView::OnMouseMove(nFlags, point);
}

//##ModelId=4A1E8473025B
bool CLeftTreeView::DrawTile(CPoint point)
{
//////////////////////////////
CClientDC hdc(this);
OnPrepareDC(&hdc);
hdc.DPtoLP(&point);
#if 1
	
	CMainFrame * pMf=(CMainFrame *)AfxGetMainWnd();
	
	this->m_ptOrigin=point;
	CClientDC dc(this);
	dc.SetMapMode(MM_LOENGLISH);
	CString szPoint;
	CPoint   ptDlt   =GetDeviceScrollPosition(); //��ȡƫ����
	szPoint.Format("%d,%d",ptDlt.x+point.x,ptDlt.y+point.y); //��ʽ��map View����

	
	int H=((CMainFrame*)AfxGetMainWnd())->m_maphtiles,//ˮƽTILE��
		V=((CMainFrame*)AfxGetMainWnd())->m_mapvtiles;//��ֱTILE��

	//ע���ȳ�ʼ����MAP����
	if (!this->CheckOK()){
		//MessageBox("��������TILE��MAP��С");
		return 0;
	}
	
	 //vector<vector<map_matrix> > Matrix(H, vector<map_matrix>((int)V));//vector��ά����,vc6��д��
	////vector<vector<int> > Matrix(H,int(V));//g++��������д��

	//Matrix0.clear();
	//Matrix0=Matrix;
	static int already_init_matrix=0;//Todo���ĳɵ���ģʽ
	if (already_init_matrix==0){
		RECT myrect;
		//������ֵ
		for (int i=0;i<V;i++){//i���У�j����
			for(int j=0;j<H;j++){
				myrect.left   = ((CMainFrame*)AfxGetMainWnd())->m_tilewidth*i;
				myrect.top    = ((CMainFrame*)AfxGetMainWnd())->m_tileheight*j;
				myrect.right  = myrect.left+((CMainFrame*)AfxGetMainWnd())->m_tilewidth;
				myrect.bottom = myrect.top+((CMainFrame*)AfxGetMainWnd())->m_tileheight;
				
				Matrix[i][j].therect.top=myrect.top;
				Matrix[i][j].therect.left=myrect.left;
				Matrix[i][j].therect.bottom=myrect.bottom;
				Matrix[i][j].therect.right=myrect.right;
			}
		}
		//AfxMessageBox("�������������ѳ�ʼ����",MB_OK);
		already_init_matrix=1;
	}
	
	//�жϵ�ǰ���������ĸ�rect
	int real_i,real_j;//��¼��������
	for (int i=0;i<V;i++){
		for(int j=0;j<H;j++){
			if (point.x>=Matrix[i][j].therect.left && point.x<=Matrix[i][j].therect.right
				&& point.y>=Matrix[i][j].therect.top && point.y<=Matrix[i][j].therect.bottom){
				real_i=i;
				real_j=j;
			}
		}
	}

	/*CString css;
	css.Format("%d %d",real_i,real_j);
	MessageBox(css);*/
//Ϊ��ǰѡ�������TILE��IDֵ
	if (pMf->m_Pt_blttile!=NULL){
		switch(m_draw_which_layer){
		case 0:
			Matrix[real_i][real_j].tileiid=pMf->m_Pt_blttile->tileiid;
			break;
		case 1:
			Matrix[real_i][real_j].layer_obj_tileiid=pMf->m_Pt_blttile->tileiid;
			break;
		case 2:
			Matrix[real_i][real_j].layer_obj2_tileiid=pMf->m_Pt_blttile->tileiid;
			break;
		}
	}
	else{//Ĭ�Ͼ����������
		Matrix[real_i][real_j].tileiid=0;
		Matrix[real_i][real_j].layer_obj_tileiid=0;
		Matrix[real_i][real_j].layer_obj2_tileiid=0;
	}


	if(!this->CheckOK())	return 0;
	
	//��ͼ����
	//HDC hdc;
	//hdc=::GetDC(this->m_hWnd); 
	//CClientDC hdc(this);
	CString bitmappath=pMf->m_bitmap_pathname;
	HBITMAP hbitmap=(HBITMAP)LoadImage(AfxGetInstanceHandle(),bitmappath,IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE|LR_CREATEDIBSECTION);
	
	CDC compatible;
	compatible.CreateCompatibleDC(NULL);
	compatible.SelectObject(hbitmap);//�ǿ��Դ��ݾ���ģ�MSDNû��������
	
	if (this->pMf->m_Pt_blttile==NULL) {//û��ѡ��Ļ���Ĭ�����
		BitBlt(hdc,Matrix[real_i][real_j].therect.left,Matrix[real_i][real_j].therect.top,pMf->m_tilewidth,pMf->m_tileheight,compatible,0,0,SRCCOPY);
	}
	else{
		switch(m_draw_which_layer){
		case 0://�������
			BitBlt(hdc,Matrix[real_i][real_j].therect.left,Matrix[real_i][real_j].therect.top,\
				pMf->m_tilewidth,pMf->m_tileheight,\
				compatible,pMf->m_Pt_blttile->tilerect.left,pMf->m_Pt_blttile->tilerect.top,\
				SRCCOPY);
			break;
		case 1://�������1
			TransparentBlt(
				hdc,        // handle to destination DC
				Matrix[real_i][real_j].therect.left,   // x-coord of destination upper-left corner
				Matrix[real_i][real_j].therect.top,   // y-coord of destination upper-left corner
				pMf->m_tilewidth,     // width of destination rectangle
				pMf->m_tileheight,    // height of destination rectangle
				compatible,         // handle to source DC
				pMf->m_Pt_blttile->tilerect.left,    // x-coord of source upper-left corner
				pMf->m_Pt_blttile->tilerect.top,    // y-coord of source upper-left corner
				pMf->m_tilewidth,      // width of source rectangle
				pMf->m_tileheight,     // height of source rectangle
				RGB(255, 0, 255)  // color to make transparent
				);
			break;
		case 2://�������2
			TransparentBlt(
				hdc,        // handle to destination DC
				Matrix[real_i][real_j].therect.left,   // x-coord of destination upper-left corner
				Matrix[real_i][real_j].therect.top,   // y-coord of destination upper-left corner
				pMf->m_tilewidth,     // width of destination rectangle
				pMf->m_tileheight,    // height of destination rectangle
				compatible,         // handle to source DC
				pMf->m_Pt_blttile->tilerect.left,    // x-coord of source upper-left corner
				pMf->m_Pt_blttile->tilerect.top,    // y-coord of source upper-left corner
				pMf->m_tilewidth,      // width of source rectangle
				pMf->m_tileheight,     // height of source rectangle
				RGB(255, 0, 255)  // color to make transparent
				);
			break;
		}
	}
OnPrepareDC(&hdc);
//hdc.DPtoLP(&point);
//hdc.DPtoLP((struct tagPOINT *)&(pMf->m_Pt_blttile->tilerect.left));
//hdc.DPtoLP((struct tagPOINT *)&(pMf->m_Pt_blttile->tilerect.top));

	ReleaseDC(&compatible);
	DeleteObject(hbitmap);
	//end ��ͼ
#if 1


	//Matrix0=Matrix;//���󣡶����뿪�������ˣ�ֻ��һ��һ����Ա��ֵ
	//this->pMf->m_b_is_transok=false;
	//if (this->pMf->Matrix0.size()<Matrix.size()){
		//this->pMf->Matrix0.clear();
		//this->pMf->Matrix0.resize(Matrix.size());
	//}
	//this->pMf->Matrix0[real_i][real_j].therect.left=Matrix[real_i][real_j].therect.left;
	//this->pMf->Matrix0[real_i][real_j].therect.top=Matrix[real_i][real_j].therect.top;
	//this->pMf->Matrix0[real_i][real_j].tileiid=pMf->m_Pt_blttile->tileiid;

	this->pMf->m_b_is_transok=true;
#endif

#endif
return 1;
//////////////////////////////
}

//##ModelId=4A1E8473030B
bool CLeftTreeView::FillAllTTiles()
{
	int i,j;
	CMainFrame *pMf=(CMainFrame*)AfxGetMainWnd();
	if (pMf->m_Pt_blttile!=NULL){
		switch(this->m_draw_which_layer){
		case 0:
			AfxMessageBox("      �������TILES      ",MB_OK);
			for (i=0;i<DEF_H;i++){
				for(j=0;j<DEF_V;j++){
					Matrix[i][j].tileiid=pMf->m_Pt_blttile->tileiid;
				}
			}
			
			break;
		case 1:
			for (i=0;i<DEF_H;i++){
				for(j=0;j<DEF_V;j++){
					Matrix[i][j].layer_obj_tileiid=pMf->m_Pt_blttile->tileiid;
					break;
				}
			}
		}
	}
	Invalidate();
	return 1;
}

//��ȡ��ͼ�ļ��ϵ�1��CELL����Ķ��������ݵ�����Matrix
//V����ֱTILE����H����ˮƽTILE����layer����ά����value��TILE��ID
//##ModelId=4A1E84730302
void CLeftTreeView::load_map2matrix_element(int V,int H,int layer,int value)
{
	//char buf[20];
		if (layer==0){
			Matrix[V][H].tileiid = value;
		}
		else if (layer==1){
			if (value!=255){//Todo:�����getc���ȡ����255��ʵ������acsii��-1��-1�Ĳ��룿����
//http://zhidao.baidu.com/question/48053080.html
			Matrix[V][H].layer_obj_tileiid = value;
			}
		}
		else if (layer==2){
			if (value!=255){
				Matrix[V][H].layer_obj2_tileiid = value;
			}
		}
	//AfxMessageBox("loadit!",MB_OK);
}



//##ModelId=4B06766B004E
void CLeftTreeView::OnEraseSmall() 
{
	// TODO: Add your command handler code here
	AfxMessageBox("1 OK");
	this->m_erase=1;
}

//##ModelId=4B06766B007D
void CLeftTreeView::OnEraseMiddle() 
{
	// TODO: Add your command handler code here
	AfxMessageBox("2 OK");
	this->m_erase=2;
}

//##ModelId=4B06766B00AB
void CLeftTreeView::OnEraseBig() 
{
	// TODO: Add your command handler code here
	AfxMessageBox("3 OK");
	this->m_erase=3;
}

BOOL CLeftTreeView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	// TODO: Add your message handler code here and/or call default
//	if(erasersur)
//static xs=0;
#if 0
if (((CMainFrame *)AfxGetMainWnd())->erasersur)
{
	HCURSOR cur11;
	cur11=AfxGetApp()->LoadCursor(IDC_OBSTACLE);
	::SetCursor(((CMainFrame *)AfxGetMainWnd())->cur11); 
	//((CMainFrame *)AfxGetMainWnd())->erasersur=0;
}
#endif

	return CScrollView::OnSetCursor(pWnd, nHitTest, message);
}

