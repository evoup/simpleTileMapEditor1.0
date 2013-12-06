// RightView.cpp : implementation file
//

#include "stdafx.h"
#include "SplitWndDemo.h"
#include "RightView.h"
#include "assert.h"
#include "classtile.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRightView

IMPLEMENT_DYNCREATE(CRightView, CScrollView)

//##ModelId=4A1E847300F5
CRightView::CRightView()
{
pMf=(CMainFrame*)AfxGetMainWnd();
m_PtOrigin=0;
}

//##ModelId=4A1E84730124
CRightView::~CRightView()
{
}


BEGIN_MESSAGE_MAP(CRightView, CScrollView)
	//{{AFX_MSG_MAP(CRightView)
	ON_WM_LBUTTONDOWN()
	ON_WM_ERASEBKGND()
	ON_COMMAND(IDM_EXP_SRCBMP, OnExpSrcbmp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRightView drawing

//##ModelId=4A1E8473011B
void CRightView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
	if (this->CheckOK()){
		assert(pMf->m_tileheight<600);
		if (pMf->m_srcbmp_width!=0)
		SetScrollSizes(MM_TEXT,CSize(pMf->m_srcbmp_width,pMf->m_tileheight));//重新设置TILE选择区域的SCROLL大小	
	}


	CClientDC hdc(this);
	
	//此处实现导入图片后的平铺候选图片组
	//先实现连续不起新行的算法
	//ToDo：换行的多余切除的算法

	CRect myrect;
	int nX=0;
	int nY=0;
	::GetClientRect(this->m_hWnd,myrect);
	pDC->FillSolidRect(myrect,RGB(192,192,192));
	if (!this->CheckOK()) return;
//	static HBITMAP hbitmap=(HBITMAP)LoadImage(AfxGetInstanceHandle(),pMf->m_bitmap_pathname,IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE|LR_CREATEDIBSECTION);
	HBITMAP hbitmap=(HBITMAP)LoadImage(AfxGetInstanceHandle(),pMf->m_bitmap_pathname,IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE|LR_CREATEDIBSECTION);
	
	CDC compatible;
	compatible.CreateCompatibleDC(pDC);
	compatible.SelectObject(hbitmap);
	//此处获取位图大小，计算有多少TILE，这样就可以BLT多少次。多余的边角料不选
	CBitmap   bm;   
	BITMAP   bwh;
	bm.Attach(hbitmap);   
	bm.GetObject(sizeof(BITMAP) , &bwh);   
	bm.Detach();  
	int c;//bitblt的次数
	assert(pMf->m_tilewidth>=10);//tile不要太小了，否则控制点有问题
	c=bwh.bmWidth/pMf->m_tilewidth;
	//去掉边角料是多少
	int bitblt_width=c*(pMf->m_tilewidth);
	pMf->m_srcbmp_width=c*(pMf->m_tilewidth);


	for (int i=0;i<c;i++){
		pDC->BitBlt(nX,nY,bitblt_width,pMf->m_tileheight,&compatible,0,0,SRCCOPY);

	}
	
	HBITMAP__ * pOld=(HBITMAP__ *)compatible.SelectObject(hbitmap);
	ReleaseDC(&compatible);
	DeleteObject(hbitmap);

	//生成8个控制点
	//动态
#if 0
	char str[800];      
	GetCurrentDirectory(800,str);  
	MessageBox(str);  //果然的当前文件路劲被改掉了！！这就是出现野指针的根源
#endif
	//所以只要替换为APP路径
	CString strAppName = AfxGetApp()->m_pszHelpFilePath;
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	_splitpath(strAppName, drive, dir, NULL,NULL);

	CString fulldir;
	fulldir.Format("%s%s",drive,dir);
	SetCurrentDirectory(fulldir);
#ifdef _DEBUG
	//由于debug版本是在debug文件夹下所以，要向上一级路劲
	CString tempstr;
	SetCurrentDirectory("../");
#endif

//if 素材总宽度/TILE宽度0-31->nX=0,32-63->nX=32
	for (i=0;i<=c;i++){//控制点移动算法
		if(this->m_PtOrigin.x<=pMf->m_tilewidth*i && this->m_PtOrigin.x>=pMf->m_tilewidth*(i-1))
			nX=pMf->m_tilewidth*(i-1);
	}




	//HBITMAP hbitmap1=(HBITMAP)LoadImage(AfxGetInstanceHandle(),"cp.bmp",IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE|LR_CREATEDIBSECTION);
	HBITMAP hbitmap1=(HBITMAP)LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP_CONTROL));
	CDC compatible1;
	compatible1.CreateCompatibleDC(pDC);
	compatible1.SelectObject(hbitmap1);
	CBitmap   bm1;
	BITMAP   bwh1;
	//if(&bm1==NULL) return;//这里来了个野指针！NULL探测不到！！FIXED
	bm1.CBitmap::Attach(hbitmap1);
	bm1.CBitmap::GetObject(sizeof(BITMAP) , &bwh1);   
	bm1.Detach();
	if (pMf->m_show_control_point){
	//第一行第一个
	pDC->BitBlt(nX,nY,bitblt_width,pMf->m_tileheight,&compatible1,0,0,SRCCOPY);
	//第一行第二个
	pDC->BitBlt(nX+pMf->m_tilewidth/2-2,nY,bitblt_width,pMf->m_tileheight,&compatible1,0,0,SRCCOPY);
	//第一行第三个
	pDC->BitBlt(nX+pMf->m_tilewidth-4,nY,bitblt_width,pMf->m_tileheight,&compatible1,0,0,SRCCOPY);
	//第二行第一个
	pDC->BitBlt(nX,nY+pMf->m_tileheight/2-2,bitblt_width,pMf->m_tileheight,&compatible1,0,0,SRCCOPY);
	//第二行第二个
	pDC->BitBlt(nX+pMf->m_tilewidth-4,nY+pMf->m_tileheight/2-2,bitblt_width,pMf->m_tileheight,&compatible1,0,0,SRCCOPY);
	//第三行第一个
	pDC->BitBlt(nX,nY+pMf->m_tileheight-4,bitblt_width,pMf->m_tileheight,&compatible1,0,0,SRCCOPY);
	//第三行第二个
	pDC->BitBlt(nX+pMf->m_tilewidth/2-2,nY+pMf->m_tileheight-4,bitblt_width,pMf->m_tileheight,&compatible1,0,0,SRCCOPY);
	//第三行第三个
	pDC->BitBlt(nX+pMf->m_tilewidth-4,nY+pMf->m_tileheight-4,bitblt_width,pMf->m_tileheight,&compatible1,0,0,SRCCOPY);
	}
	compatible1.SelectObject(pOld);//选回来，但好像不加也没什么变化。
ReleaseDC(&compatible1);
DeleteObject(hbitmap1);
}

/////////////////////////////////////////////////////////////////////////////
// CRightView diagnostics

#ifdef _DEBUG
//##ModelId=4A1E84730126
void CRightView::AssertValid() const
{
	CScrollView::AssertValid();
}

//##ModelId=4A1E84730133
void CRightView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRightView message handlers






//##ModelId=4A1E84730118
bool CRightView::CheckOK()//检查是否可以开始重绘了
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

//##ModelId=4A1E84730119
void CRightView::OnInitialUpdate() 
{
	CScrollView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
		SetScrollSizes(MM_TEXT,CSize(0,0));//设置TILE选择区域的SCROLL大小	
}

//##ModelId=4A1E84730136
void CRightView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	//此处先打印这个变量
	struct tiles *h;
	//h=this->m_Pt_tiles_linklist_headernode;
	CMainFrame * pMf=(CMainFrame*)AfxGetMainWnd();
	h=pMf->m_Pt_tiles_linklist_headernode;
	struct tiles *thetile=this->find_tile(h,point.x+GetScrollPosition ().x,point.y+GetScrollPosition ().y);
	if (thetile==NULL)	return;
	pMf->m_Pt_blttile=thetile;//要blt的素材tile
	char buf[30];
	CLeftTreeView * pView=(CLeftTreeView*)(((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(0,0));
	if(pView->m_draw_which_layer==0){
		sprintf(buf,"正在编辑0层  当前tile的id:%d",thetile->tileiid);
	}
	else if(pView->m_draw_which_layer==1){
		sprintf(buf,"正在编辑1层  当前tile的id:%d",thetile->tileiid);
	}
	else if(pView->m_draw_which_layer==2){
		sprintf(buf,"正在编辑2层  当前tile的id:%d",thetile->tileiid);
	}
	else if(pView->m_draw_which_layer==3){
		sprintf(buf,"正在编辑3层  当前tile的id:%d",thetile->tileiid);
	}

	//AfxMessageBox(buf);
	//状态栏
	CStatusBar*   pStatus=(CStatusBar*)AfxGetApp()->m_pMainWnd->GetDescendantWindow(AFX_IDW_STATUS_BAR);   
  //pStatus->SetPaneText(0,"test   string");
	pStatus->SetPaneText(0,buf);


	CClientDC cdc(this);
	//::SetMapMode(cdc,MM_ANISOTROPIC);
	//cdc.LPtoDP(&point);
	this->m_PtOrigin.x=point.x+GetScrollPosition ().x;
	this->m_PtOrigin.y=point.y+GetScrollPosition ().y;
	//刷新以删除之前的控制点
	//CRightView * pView=(CRightView*)(((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(1,0));
	this->Invalidate();
	//栈方法
	//classtile clstile;
	//clstile.GetTileInfo();
	//堆方法
	//classtile *clstile=new classtile();
	//clstile->GetTileInfo();
	//delete clstile;

	CScrollView::OnLButtonDown(nFlags, point);
}

//打印链表(abandoned)
//##ModelId=4A1E84730109
bool CRightView::display_tile_linklist(struct tiles *s)
{
s = s->next;
while(s!=NULL)
{
	CString nodestr;
	nodestr.Format("%d",s->tilerect.left);
	AfxMessageBox(nodestr);
	s = s->next;
}
return 1;
}

//寻找TILE链表节点对应TILE信息。
// 返回找到的节点TILE
//##ModelId=4A1E84730105
struct tiles * CRightView::find_tile(struct tiles *s,int x,int y)
{
	if (!this->CheckOK()) {
	return NULL;
	}
	s = s->next;
	while(s!=NULL)
	{
		if (y>=s->tilerect.top && y<=s->tilerect.bottom) {
			if(x>=s->tilerect.left && x<=s->tilerect.right){
				return s;
			}
		}
		s = s->next;
	}
	return s;
}

//##ModelId=4A1E84730104
bool CRightView::Export_src_bmp()
{
	if (!this->CheckOK()) {
		MessageBox("先导入素材吧","info",MB_OK);
		return NULL;
	}
	//
		//【然后输出素材图片】
	//http://topic.csdn.net/t/20050121/10/3742978.html
	pMf->m_show_control_point=false;//关闭控制点的显示
	this->invalidate_me();
	CClientDC dc(this);
	CDC   memDC;
	memDC.CreateCompatibleDC(&dc); 
	CMainFrame *pMf=(CMainFrame *)AfxGetMainWnd();
	CBitmap   bm;
    if(pMf->m_exp_method==0){
		//MessageBox("输出的是竖向");
		bm.CreateCompatibleBitmap(&dc,pMf->m_tileheight,pMf->m_srcbmp_width);  
	}
	else{
		//MessageBox("输出的是横向");
		bm.CreateCompatibleBitmap(&dc,pMf->m_srcbmp_width,pMf->m_tileheight); 
		//按照之前下方TILE选择区域的算法
	}
		//完成绘图后,必须将原来的旧笔选回设备环境  
		//否则windows可能会使用那个选进设备的GDI对象来绘制控件和其他控件!  
		
		//【Todo】在内存DC上作图

	CBitmap* pOld   = memDC.SelectObject(&bm);
		//memDC.TextOut(0,0,"test");
//【第二个内存DC】
//已经有的操作
//dc,memDC(目标内存DC),bm(no use),pOld第一个内存DC的之前的选择GDI对象
//Todo：再创建1个内存DC:compatible,要与之前的DC兼容！怎么兼容？引用！compatible.CreateCompatibleDC(&memDC);\
//pOldbitmap第二个内存DC之前的选择GDI对象
#if 1
	//CClientDC dc2(this);
	HBITMAP hbitmap=(HBITMAP)LoadImage(AfxGetInstanceHandle(),pMf->m_bitmap_pathname,IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE|LR_CREATEDIBSECTION);
	
	//此处获取位图大小，计算有多少TILE，这样就可以BLT多少次。多余的边角料不选
	CBitmap   bm1;   
	CBitmap   *pOldbitmap;  
	BITMAP   bwh;
bm1.Attach(hbitmap); //注意工作完detach它
//bm1.GetObject(sizeof(BITMAP) , &bwh); //这个比GetBitmap更通用
bm1.GetBitmap(&bwh);   
//CString d;
//d.Format("%d",bwh.bmWidth);
//MessageBox(d);
	CDC compatible;//第二个内存DC
	compatible.CreateCompatibleDC(&memDC);//创建和pDC兼容的DC，其实就是引用第一个内存DC
	pOldbitmap=compatible.SelectObject(&bm1);
	int c;//bitblt的次数
//	assert(pMf->m_tilewidth>=10);//tile不要太小了，否则控制点有问题

	
		c=bwh.bmWidth/pMf->m_tilewidth;
		//去掉边角料是多少
		int bitblt_width=c*(pMf->m_tilewidth);
		pMf->m_srcbmp_width=c*(pMf->m_tilewidth);
		pMf->m_srcbmp_height=bwh.bmHeight;
	if(pMf->m_exp_method==0){	
		//memDC.BitBlt(0,0,bwh.bmWidth,bwh.bmHeight,&compatible,0,0,SRCCOPY);  
		for (int i=0;i<c;i++){
			//pDC->BitBlt(nX,nY,bitblt_width,pMf->m_tileheight,&compatible,0,0,SRCCOPY);
			memDC.BitBlt(/*目标矩左上x*/0,pMf->m_tileheight*i,/*目标矩宽*/pMf->m_tilewidth,pMf->m_tileheight,&compatible,\
				/*源矩形左上x坐标*/pMf->m_tilewidth*i,/*rect.TopLeft().y*/0,SRCCOPY);
		}
	}
	else{
		/*CString a;
		a.Format("%d %d",pMf->m_srcbmp_width,pMf->m_srcbmp_height);
		MessageBox(a);*/
		memDC.BitBlt(/*目标矩左上x*/0,0,/*目标矩宽*/pMf->m_srcbmp_width,pMf->m_srcbmp_height,&compatible,\
			/*源矩形左上x坐标*/0,/*rect.TopLeft().y*/0,SRCCOPY);
	}

	//memDC.BitBlt(/*目标矩形左上x坐标*/0,0,/*目标矩形宽*/32,32,&dc,/*源矩形左上x坐标*/0,/*rect.TopLeft().y*/0,SRCCOPY);
memDC.SelectObject(pOld);//选回来！
compatible.SelectObject(pOldbitmap);
#endif
		//memDC.BitBlt(/*目标矩形左上x坐标*/0,   0,/*目标矩形宽*/   Width,   Height,   dc,   /*源矩形左上x坐标*/0,   /*rect.TopLeft().y*/0,   SRCCOPY);  
		//memDC.SelectObject(pOld);//将旧bmp选回设备
		///////////////////////////////////////////
		//生成位图

	#if 1
		BITMAP btm;
		bm.GetBitmap(&btm);
		/*  
		DWORD   DataSizePerLine;  
		DWORD   DataSize;  
		DataSizePerLine=   (btm.bmWidth*btm.bmBitsPixel+31)/8;    
		//   一个扫描行所占的字节数  
		DataSizePerLine=   DataSizePerLine/4*4;   //   字节数必须是4的倍数  
		//位图数据的大小(不压缩情况下):  
		DataSize=   DataSizePerLine*   btm.bmHeight;  
		*/   

		DWORD     size   =   btm.bmWidthBytes   *   btm.bmHeight;//位图数据即为行字节*高字节  
		LPSTR   lpData   =   (LPSTR)GlobalAlloc(GPTR,   size);//开辟内存

		BITMAPINFOHEADER     bih;//bmp头信息  
		bih.biBitCount   =   btm.bmBitsPixel;//   每个像素所需的位数，必须是1(双色),4(16色)，8(256色)或24(真彩色)之一  
		bih.biClrImportant   =   0;//   位图显示过程中重要的颜色数  
		bih.biClrUsed   =   0;//   位图实际使用的颜色表中的颜色数  
		bih.biCompression   =   0;//   位图压缩类型，必须是   0(不压缩),1(BI_RLE8压缩类型)或2(BI_RLE4压缩类型)之一  
		bih.biHeight   =   btm.bmHeight;//   位图的高度，以像素为单位  
		bih.biWidth   =   btm.bmWidth;//   位图的宽度，以像素为单位  
		bih.biPlanes   =   1;//   目标设备的级别，必须为1  
		bih.biSize   =   sizeof(BITMAPINFOHEADER);//   本结构所占用字节数  
		bih.biSizeImage   =   size;//   位图的大小，以字节为单位  
		bih.biWidth   =   btm.bmWidth;  
		bih.biXPelsPerMeter   =   0;//   位图水平分辨率，每米像素数  
		bih.biYPelsPerMeter   =   0;//   位图垂直分辨率，每米像素数  
		
		GetDIBits(dc,bm,0,bih.biHeight,lpData,(BITMAPINFO*)&bih,DIB_RGB_COLORS);  
		//bm.GetBitmapBits(size,lpData);//此函数在处理5-5-5模式的16位色下会出现颜色混乱  
		
		BITMAPFILEHEADER       bfh;//bmp文件头  
		bfh.bfReserved1   =   bfh.bfReserved2   =   0;//   位图文件保留字，必须为0  
		bfh.bfType   =   ((WORD)('M'<<   8)|'B');//   位图文件的类型，必须为BM  
		bfh.bfSize   =   54   +   size;//   位图文件的大小，以字节为单位  
		bfh.bfOffBits   =   54;//   位图数据的起始位置，以相对于位图文件头的偏移量表示，以字节为单位  
		
	
		CFileDialog   dlg(false,_T("BMP"),_T("*.bmp"),OFN_HIDEREADONLY   |   OFN_OVERWRITEPROMPT,_T("*.bmp|*.bmp|*.*|*.*|"));  
		if   (dlg.DoModal()!=IDOK)  {
			pMf->m_show_control_point=true;
			return 0;
		}
		
		CFile     bf;  
		
		CString   ss=dlg.GetPathName();  
		if(bf.Open(ss,   CFile::modeCreate   |   CFile::modeWrite))  
		{  
			bf.WriteHuge(&bfh,   sizeof(BITMAPFILEHEADER));//写bmp文件头  
			bf.WriteHuge(&bih,   sizeof(BITMAPINFOHEADER));//写bmp头信息  
			bf.WriteHuge(lpData,   size);//写bmp数据  
			bf.Close();  
			AfxMessageBox("保存成功");  
		}  
#if 1
	ReleaseDC(&memDC);
	ReleaseDC(&compatible);
	DeleteObject(hbitmap);
	bm1.Detach();
#endif
		GlobalFree(lpData);//释放内存
#endif
	//
		pMf->m_show_control_point=true;
		this->invalidate_me();
		return 1;
}

//##ModelId=4A1E84730142
void CRightView::OnExpSrcbmp() 
{
	// TODO: Add your command handler code here
	this->Export_src_bmp();
}

//##ModelId=4A1E84730103
bool CRightView::invalidate_me()
{
	CRightView * pView=(CRightView*)(((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(1,0));
	pView->Invalidate(true);//强制刷新一次，这样控制点就消失了，不会位拷贝进来
	//【记得重绘发消息要时间的!】
		//OnExpSrcbmp_callback_fun();//回调函数，帮助退出菜单
	//Todo(Done)：为什么一个MessageBox就可以！？因为重绘要时间!!
	//MessageBox("test");
	//Sleep(2000);//不要使用休眠API，不处理重绘消息的!
	//延时
	Ccommon mycomm;
	mycomm.Delay(100);//重绘消息0.1秒够了吧
	return 1;
}

