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



//Todo:把这个难看的东西放到类里
static vector<vector<map_matrix> > Matrix(DEF_V, vector<map_matrix>((int)DEF_H));


//这么做只能得到二维的指针，而不是想要的指向二维数组的指针。
//vector<vector<map_matrix> > *va=new vector<vector<map_matrix> >();
//vector<vector<map_matrix> > *mx=new vector<vector<map_matrix> >(H, vector<map_matrix>((int)V));
//放弃派生成员！//http://topic.csdn.net/t/20060101/14/4494017.html
//vector<vector<map_matrix> > CLeftTreeView::Matrix(222, vector<map_matrix>(223));

/////////////////////////////////////////////////////////////////////////////
// CLeftTreeView

IMPLEMENT_DYNCREATE(CLeftTreeView, CScrollView)

//##ModelId=4A1E8473024B
CLeftTreeView::CLeftTreeView()
{	

	this->m_draw_which_layer=0;//默认画地面层
	this->m_view_which_layer=-1;//默认显示所有层
	//pMf= (CMainFrame*)AfxGetMainWnd();
	//初始化矩阵
	for(int i=0;i<DEF_V;i++){
		for (int j=0;j<DEF_H;j++){
			Matrix[i][j].therect.top=0;
			Matrix[i][j].therect.left=0;
			Matrix[i][j].tileiid=-1;
			Matrix[i][j].layer_obj_tileiid=-1;
			Matrix[i][j].layer_obj2_tileiid=-1;
			Matrix[i][j].layer_sky_tileiid=-1;
			Matrix[i][j].layer_obstacle=0;//障碍0为无，1为有
		}
	}
	this->m_lbutton_is_down=false;
	this->m_erase=-1;//橡皮擦标记,-1是没有选择到橡皮擦，1是小擦，2是中擦，3是大擦
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
		SetScrollSizes(MM_TEXT,CSize(pMf->m_tilewidth*pMf->m_maphtiles,pMf->m_tileheight*pMf->m_mapvtiles));//重新设置MAP的SCROLL大小	
		
		//CMainFrame *pMf=(CMainFrame*)AfxGetMainWnd();
	//int s=this->GetDeviceScrollPosition().x;
	
		CRightView * pView=(CRightView*)(((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(1,0));
		pView->Invalidate();
	}
	else return;
	
	
	//重绘背景
	
#if 1
	
	pMf=(CMainFrame*)AfxGetMainWnd();
	if ( (pMf->m_tilewidth!=0) && (pMf->m_tileheight!=0) && (pMf->m_maphtiles!=0) && (pMf->m_mapvtiles!=0))
	{
		
		//贴图测试

		CClientDC hdc(this);

		CString bitmappath=pMf->m_bitmap_pathname;
		
		HBITMAP hbitmap=(HBITMAP)LoadImage(AfxGetInstanceHandle(),bitmappath,IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE|LR_CREATEDIBSECTION);
		
		CDC compatible;
		
		compatible.CreateCompatibleDC(NULL);
		
		compatible.SelectObject(hbitmap);//是可以传递句柄的，MSDN没讲到！！
		
		//Todo：下面要先把结构初始化。
		if (pMf->m_b_is_transok){
			classtile tileobj;
			struct tiles * ttile;

			//[第一次优化]计算客户区里有哪些TILE，只有这些会BLT,一般不会超过整屏幕吧！就以整屏幕为范围！
#if 1//以下代码仅在Oscroll调试，实际是为了Ondraw的优化
			/************************************************************************/
			/* 通过左上角坐标计算哪些TILE是需要更新的                               */
			/************************************************************************/
			CPoint upleft_pt;//编辑窗口左上角坐标
			//char buf[20];
			int H=((CMainFrame*)AfxGetMainWnd())->m_maphtiles,//水平TILE数
				int V=((CMainFrame*)AfxGetMainWnd())->m_mapvtiles;//垂直TILE数
			upleft_pt.x=this->GetDeviceScrollPosition().x;
			upleft_pt.y=this->GetDeviceScrollPosition().y;
			
			//判断当前坐标属于哪个rect,reali,realj就是起点blt坐标（当前左上）
			int real_i,real_j;//记录所属矩阵单元格
			for (int i=0;i<V;i++){
				for(int j=0;j<H;j++){
					if (upleft_pt.x>=Matrix[i][j].therect.left && upleft_pt.x<=Matrix[i][j].therect.right
						&& upleft_pt.y>=Matrix[i][j].therect.top && upleft_pt.y<=Matrix[i][j].therect.bottom){
						real_i=i;
						real_j=j;
					}
				}
			}
			
			
			//计算编辑窗口实际上的尺寸
			
			//接下来凡是从左上点Matrix[i][j]到右下的
			RECT thewindowrect;
			GetWindowRect(&thewindowrect);
			int window_w=thewindowrect.right-thewindowrect.left;
			int window_h=thewindowrect.bottom-thewindowrect.top;
			//从左上角点开始纵向TILE数
			int y_tile_nums=window_h/((CMainFrame*)AfxGetMainWnd())->m_tilewidth+1;//余数算1点
			int x_tile_nums=window_w/((CMainFrame*)AfxGetMainWnd())->m_tileheight+1;
#endif//通过real_i,real_j,y_tile_nums,x_tile_nums就可以锁定哪些tiles是需要Blt的



			int CXScreen=::GetSystemMetrics(SM_CXSCREEN);
			int CYScreen=::GetSystemMetrics(SM_CYSCREEN);
			/*char buf[20];
			sprintf(buf,"%d",CYScreen);
			AfxMessageBox(buf,MB_OK);*/
#if 1	
			int j;
			int dstx,dsty;
			switch (this->m_view_which_layer){
			case -1 ://显示所有层的话
				for (i=0;i<DEF_V;i++){
					for (j=0;j<DEF_H;j++){//查询tileid对应的tile信息，返回指针
#if 1
						//先显示地面层
						if(Matrix[i][j].tileiid!=-1){
							ttile=tileobj.gettile(this->pMf->m_Pt_tiles_linklist_headernode,\
								Matrix[i][j].tileiid);
							if ((i>=real_i || real_i<=i+y_tile_nums) && \
								(j>=real_j || real_j<=j+x_tile_nums)
								)//[第一次优化]
							{
								::BitBlt(hdc,Matrix[i][j].therect.left-GetScrollPosition ().x,Matrix[i][j].therect.top-GetScrollPosition ().y,\
									((CMainFrame*)AfxGetMainWnd())->m_tilewidth,((CMainFrame*)AfxGetMainWnd())->m_tileheight,\
									compatible,ttile->tilerect.left,ttile->tilerect.top,\
								SRCCOPY);
							}
						}//end if
#endif
						//Sleep(0.1);
						//再显示物件层1
						if(Matrix[i][j].layer_obj_tileiid!=-1){
							ttile=tileobj.gettile(this->pMf->m_Pt_tiles_linklist_headernode,\
								Matrix[i][j].layer_obj_tileiid);	
							dstx=Matrix[i][j].therect.left-GetScrollPosition ().x;
							dsty=Matrix[i][j].therect.top-GetScrollPosition ().y;
							if ((i>=real_i || real_i<=i+y_tile_nums) && \
								(j>=real_j || real_j<=j+x_tile_nums)
								){//[第一次优化]
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
									AfxMessageBox("有错！可能选择的图片比设置的Tile要小！",MB_OK);
								}//endif
							}
						}//endif
						//结束显示物件层1
						//再显示物件层2
						if(Matrix[i][j].layer_obj2_tileiid!=-1){
							ttile=tileobj.gettile(this->pMf->m_Pt_tiles_linklist_headernode,\
								Matrix[i][j].layer_obj2_tileiid);	
							dstx=Matrix[i][j].therect.left-GetScrollPosition ().x;
							dsty=Matrix[i][j].therect.top-GetScrollPosition ().y;
							if ((i>=real_i || real_i<=i+y_tile_nums) && \
								(j>=real_j || real_j<=j+x_tile_nums)
								){//[第一次优化]
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
									AfxMessageBox("有错！可能选择的图片比设置的Tile要小！",MB_OK);
								}//endif
							}
						}//endif
						//结束显示物件层2
					}//end for
				}//end for
				break;
			case 0://仅显示地面层
				for (i=0;i<DEF_V;i++){
					for (j=0;j<DEF_H;j++){//查询tileid对应的tile信息，返回指针
						if(Matrix[i][j].tileiid!=-1){
							ttile=tileobj.gettile(this->pMf->m_Pt_tiles_linklist_headernode,\
								Matrix[i][j].tileiid);	
							if ((i>=real_i || real_i<=i+y_tile_nums) && \
								(j>=real_j || real_j<=j+x_tile_nums)
								){//[第一次优化]
								::BitBlt(hdc,Matrix[i][j].therect.left-GetScrollPosition ().x,Matrix[i][j].therect.top-GetScrollPosition ().y,\
									((CMainFrame*)AfxGetMainWnd())->m_tilewidth,((CMainFrame*)AfxGetMainWnd())->m_tileheight,\
									compatible,ttile->tilerect.left,ttile->tilerect.top,\
									SRCCOPY);
							}
						}//end if
					}//end for
				}//end for
				break;
			case 1://仅显示物件层1
				for (i=0;i<DEF_V;i++){
					for (j=0;j<DEF_H;j++){//查询tileid对应的tile信息，返回指针
						if(Matrix[i][j].layer_obj_tileiid!=-1){
							ttile=tileobj.gettile(this->pMf->m_Pt_tiles_linklist_headernode,\
								Matrix[i][j].layer_obj_tileiid);
							if ((i>=real_i || real_i<=i+y_tile_nums) && \
								(j>=real_j || real_j<=j+x_tile_nums)
								){//[第一次优化]
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
			case 2://仅显示物件层2
				for (i=0;i<DEF_V;i++){
					for (j=0;j<DEF_H;j++){//查询tileid对应的tile信息，返回指针
						if(Matrix[i][j].layer_obj2_tileiid!=-1){
							ttile=tileobj.gettile(this->pMf->m_Pt_tiles_linklist_headernode,\
								Matrix[i][j].layer_obj2_tileiid);
							if ((i>=real_i || real_i<=i+y_tile_nums) && \
								(j>=real_j || real_j<=j+x_tile_nums)
								){//[第一次优化]
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
			case 7://仅显示天空层
				break;
			}//end switch
#endif

		}//end if pMf->m_b_is_transok
		//end 贴图
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
	//this->InitialDBB();//不要双缓冲了
	
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


//初始化GDI双缓冲
//##ModelId=4A1E8473026F
void CLeftTreeView::InitialDBB()
{
	CRect rt;
	this->GetClientRect(&rt);
	
	// 为屏幕DC创建兼容的内存DC
	if(!m_dcMemory.CreateCompatibleDC(NULL))				
	{														
		::PostQuitMessage(0);
	}	
	
	// 创建位图
	m_Bmp.CreateCompatibleBitmap(&m_dcMemory, rt.Width(), rt.Height());
	
	// 相当于选择画布
	::SelectObject(m_dcMemory.GetSafeHdc(), m_Bmp);			
	MessageBox("GDI双缓冲初始化完毕");
}

//BOOL CLeftTreeView::OnEraseBkgnd(CDC *pDC){//这么做参见VCKBASE类似画图板的小程序
	//	不过也没掉用！
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
#if 0//以下代码仅在此处调试，实际是为了Ondraw的优化
	/************************************************************************/
	/* 通过左上角坐标计算哪些TILE是需要更新的                               */
	/************************************************************************/
	CPoint upleft_pt;//编辑窗口左上角坐标
	//char buf[20];
	int H=((CMainFrame*)AfxGetMainWnd())->m_maphtiles,//水平TILE数
	int V=((CMainFrame*)AfxGetMainWnd())->m_mapvtiles;//垂直TILE数
	upleft_pt.x=this->GetDeviceScrollPosition().x;
	upleft_pt.y=this->GetDeviceScrollPosition().y;

	//判断当前坐标属于哪个rect,reali,realj就是起点blt坐标（当前左上）
	int real_i,real_j;//记录所属矩阵单元格
	for (int i=0;i<V;i++){
		for(int j=0;j<H;j++){
			if (upleft_pt.x>=Matrix[i][j].therect.left && upleft_pt.x<=Matrix[i][j].therect.right
				&& upleft_pt.y>=Matrix[i][j].therect.top && upleft_pt.y<=Matrix[i][j].therect.bottom){
				real_i=i;
				real_j=j;
			}
		}
	}


//计算编辑窗口实际上的尺寸
	
//接下来凡是从左上点Matrix[i][j]到右下的
	RECT thewindowrect;
	GetWindowRect(&thewindowrect);
	int window_w=thewindowrect.right-thewindowrect.left;
	int window_h=thewindowrect.bottom-thewindowrect.top;
	//从左上角点开始纵向TILE数
	int y_tile_nums=window_h/((CMainFrame*)AfxGetMainWnd())->m_tilewidth+1;//余数算1点
	int x_tile_nums=window_w/((CMainFrame*)AfxGetMainWnd())->m_tileheight+1;
#endif

//	this->Invalidate();//Todo:2009-10-9 0:15不要刷新，可以减少一次刷新的痛苦！
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
	//【生成地图代码】for map算法1
	//Todo:这个MAP1生成地图算法基本废除了！没有必要保留了，下次删掉！
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
				matrixrow+=comm;//如果不是最后一个水平TILEID，则加上逗号
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
	//【生成二进制地图文件】for map算法2
	MessageBox("生成二进制地图文件");
	//from gamedev.net
	int x, y;
	// generate a random map -- this should be replaced by a nice
	// map editor when you get a chance :)
	//BYTE byMap[60][60][2];//暂时只有一层地图
	//BYTE byMap[pMf->m_maphtiles][pMf->m_mapvtiles][1];
//STL三维数组显示byMap[x][y][z]

	//int m=pMf->m_mapvtiles;
    //int n=pMf->m_maphtiles;
	int v=pMf->m_mapvtiles;
    int h=pMf->m_maphtiles;

    //int l=1;//暂时就一维
	int l=3;
    vector<vector<vector<BYTE> > > byMap(v,vector<vector<BYTE> >(h,vector<BYTE>(l)));
	for(x=0;x<v;x++){
		for(y=0;y<h;y++){
			//byMap[x][y][0]=Matrix[x][y].tileiid;
			if(Matrix[x][y].tileiid==-1)
				byMap[x][y][0]=0;
			else{
				byMap[x][y][0]=Matrix[x][y].tileiid;
				//byMap[x][y][1]=0;//第二层图片为0？
				//byMap[x][y][1]=-1;//第二层图片为-1
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
	//putc(h-1, pfile);//前2个代表的是mapdata.xMax和mapdata.yMax,减去1是因为DEMO地图数组从下标0开始
	//putc(v-1, pfile);
	char bufstr1[4];
	char bufstr2[4];
	itoa(h,bufstr1,10);
	itoa(v,bufstr2,10);
	fputs("Map:",pfile);//必须先放1个字符，否则DEMO的sscanf匹配不出！
	fputs("H",pfile);
	fputs(bufstr1,pfile);
	fputs("V",pfile);//“H地图横格子数V地图竖格子数|”
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
	CPoint   ptDlt   =GetDeviceScrollPosition(); //获取偏移量
	szPoint.Format("%d,%d",ptDlt.x+point.x,ptDlt.y+point.y); //格式化map View坐标

	
	int H=((CMainFrame*)AfxGetMainWnd())->m_maphtiles,//水平TILE数
		V=((CMainFrame*)AfxGetMainWnd())->m_mapvtiles;//垂直TILE数

	//注意先初始化掉MAP部分
	if (!this->CheckOK()){
		//MessageBox("请先设置TILE和MAP大小");
		return 0;
	}
	
	 //vector<vector<map_matrix> > Matrix(H, vector<map_matrix>((int)V));//vector二维数组,vc6的写法
	////vector<vector<int> > Matrix(H,int(V));//g++编译器的写法

	//Matrix0.clear();
	//Matrix0=Matrix;
	static int already_init_matrix=0;//Todo：改成单件模式
	if (already_init_matrix==0){
		RECT myrect;
		//给矩阵赋值
		for (int i=0;i<V;i++){//i是列，j是行
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
		//AfxMessageBox("矩阵坐标数据已初始化！",MB_OK);
		already_init_matrix=1;
	}
	
	//判断当前坐标属于哪个rect
	int real_i,real_j;//记录所属坐标
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
//为当前选择的区域赋TILE的ID值
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
	else{//默认就是最左面的
		Matrix[real_i][real_j].tileiid=0;
		Matrix[real_i][real_j].layer_obj_tileiid=0;
		Matrix[real_i][real_j].layer_obj2_tileiid=0;
	}


	if(!this->CheckOK())	return 0;
	
	//贴图测试
	//HDC hdc;
	//hdc=::GetDC(this->m_hWnd); 
	//CClientDC hdc(this);
	CString bitmappath=pMf->m_bitmap_pathname;
	HBITMAP hbitmap=(HBITMAP)LoadImage(AfxGetInstanceHandle(),bitmappath,IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE|LR_CREATEDIBSECTION);
	
	CDC compatible;
	compatible.CreateCompatibleDC(NULL);
	compatible.SelectObject(hbitmap);//是可以传递句柄的，MSDN没讲到！！
	
	if (this->pMf->m_Pt_blttile==NULL) {//没有选择的话，默认这就
		BitBlt(hdc,Matrix[real_i][real_j].therect.left,Matrix[real_i][real_j].therect.top,pMf->m_tilewidth,pMf->m_tileheight,compatible,0,0,SRCCOPY);
	}
	else{
		switch(m_draw_which_layer){
		case 0://画地面层
			BitBlt(hdc,Matrix[real_i][real_j].therect.left,Matrix[real_i][real_j].therect.top,\
				pMf->m_tilewidth,pMf->m_tileheight,\
				compatible,pMf->m_Pt_blttile->tilerect.left,pMf->m_Pt_blttile->tilerect.top,\
				SRCCOPY);
			break;
		case 1://画物件层1
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
		case 2://画物件层2
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
	//end 贴图
#if 1


	//Matrix0=Matrix;//错误！对象离开作用域了，只能一个一个成员赋值
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
			AfxMessageBox("      填充所有TILES      ",MB_OK);
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

//读取地图文件上的1个CELL区域的多个层的数据到矩阵Matrix
//V矩阵垂直TILE数，H矩阵水平TILE数，layer矩阵维数，value是TILE的ID
//##ModelId=4A1E84730302
void CLeftTreeView::load_map2matrix_element(int V,int H,int layer,int value)
{
	//char buf[20];
		if (layer==0){
			Matrix[V][H].tileiid = value;
		}
		else if (layer==1){
			if (value!=255){//Todo:这次是getc或获取到的255，实际上是acsii是-1？-1的补码？正解
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

