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
		SetScrollSizes(MM_TEXT,CSize(pMf->m_srcbmp_width,pMf->m_tileheight));//��������TILEѡ�������SCROLL��С	
	}


	CClientDC hdc(this);
	
	//�˴�ʵ�ֵ���ͼƬ���ƽ�̺�ѡͼƬ��
	//��ʵ�������������е��㷨
	//ToDo�����еĶ����г����㷨

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
	//�˴���ȡλͼ��С�������ж���TILE�������Ϳ���BLT���ٴΡ�����ı߽��ϲ�ѡ
	CBitmap   bm;   
	BITMAP   bwh;
	bm.Attach(hbitmap);   
	bm.GetObject(sizeof(BITMAP) , &bwh);   
	bm.Detach();  
	int c;//bitblt�Ĵ���
	assert(pMf->m_tilewidth>=10);//tile��Ҫ̫С�ˣ�������Ƶ�������
	c=bwh.bmWidth/pMf->m_tilewidth;
	//ȥ���߽����Ƕ���
	int bitblt_width=c*(pMf->m_tilewidth);
	pMf->m_srcbmp_width=c*(pMf->m_tilewidth);


	for (int i=0;i<c;i++){
		pDC->BitBlt(nX,nY,bitblt_width,pMf->m_tileheight,&compatible,0,0,SRCCOPY);

	}
	
	HBITMAP__ * pOld=(HBITMAP__ *)compatible.SelectObject(hbitmap);
	ReleaseDC(&compatible);
	DeleteObject(hbitmap);

	//����8�����Ƶ�
	//��̬
#if 0
	char str[800];      
	GetCurrentDirectory(800,str);  
	MessageBox(str);  //��Ȼ�ĵ�ǰ�ļ�·�����ĵ��ˣ�������ǳ���Ұָ��ĸ�Դ
#endif
	//����ֻҪ�滻ΪAPP·��
	CString strAppName = AfxGetApp()->m_pszHelpFilePath;
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	_splitpath(strAppName, drive, dir, NULL,NULL);

	CString fulldir;
	fulldir.Format("%s%s",drive,dir);
	SetCurrentDirectory(fulldir);
#ifdef _DEBUG
	//����debug�汾����debug�ļ��������ԣ�Ҫ����һ��·��
	CString tempstr;
	SetCurrentDirectory("../");
#endif

//if �ز��ܿ��/TILE���0-31->nX=0,32-63->nX=32
	for (i=0;i<=c;i++){//���Ƶ��ƶ��㷨
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
	//if(&bm1==NULL) return;//�������˸�Ұָ�룡NULL̽�ⲻ������FIXED
	bm1.CBitmap::Attach(hbitmap1);
	bm1.CBitmap::GetObject(sizeof(BITMAP) , &bwh1);   
	bm1.Detach();
	if (pMf->m_show_control_point){
	//��һ�е�һ��
	pDC->BitBlt(nX,nY,bitblt_width,pMf->m_tileheight,&compatible1,0,0,SRCCOPY);
	//��һ�еڶ���
	pDC->BitBlt(nX+pMf->m_tilewidth/2-2,nY,bitblt_width,pMf->m_tileheight,&compatible1,0,0,SRCCOPY);
	//��һ�е�����
	pDC->BitBlt(nX+pMf->m_tilewidth-4,nY,bitblt_width,pMf->m_tileheight,&compatible1,0,0,SRCCOPY);
	//�ڶ��е�һ��
	pDC->BitBlt(nX,nY+pMf->m_tileheight/2-2,bitblt_width,pMf->m_tileheight,&compatible1,0,0,SRCCOPY);
	//�ڶ��еڶ���
	pDC->BitBlt(nX+pMf->m_tilewidth-4,nY+pMf->m_tileheight/2-2,bitblt_width,pMf->m_tileheight,&compatible1,0,0,SRCCOPY);
	//�����е�һ��
	pDC->BitBlt(nX,nY+pMf->m_tileheight-4,bitblt_width,pMf->m_tileheight,&compatible1,0,0,SRCCOPY);
	//�����еڶ���
	pDC->BitBlt(nX+pMf->m_tilewidth/2-2,nY+pMf->m_tileheight-4,bitblt_width,pMf->m_tileheight,&compatible1,0,0,SRCCOPY);
	//�����е�����
	pDC->BitBlt(nX+pMf->m_tilewidth-4,nY+pMf->m_tileheight-4,bitblt_width,pMf->m_tileheight,&compatible1,0,0,SRCCOPY);
	}
	compatible1.SelectObject(pOld);//ѡ�����������񲻼�Ҳûʲô�仯��
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
bool CRightView::CheckOK()//����Ƿ���Կ�ʼ�ػ���
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
		SetScrollSizes(MM_TEXT,CSize(0,0));//����TILEѡ�������SCROLL��С	
}

//##ModelId=4A1E84730136
void CRightView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	//�˴��ȴ�ӡ�������
	struct tiles *h;
	//h=this->m_Pt_tiles_linklist_headernode;
	CMainFrame * pMf=(CMainFrame*)AfxGetMainWnd();
	h=pMf->m_Pt_tiles_linklist_headernode;
	struct tiles *thetile=this->find_tile(h,point.x+GetScrollPosition ().x,point.y+GetScrollPosition ().y);
	if (thetile==NULL)	return;
	pMf->m_Pt_blttile=thetile;//Ҫblt���ز�tile
	char buf[30];
	CLeftTreeView * pView=(CLeftTreeView*)(((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(0,0));
	if(pView->m_draw_which_layer==0){
		sprintf(buf,"���ڱ༭0��  ��ǰtile��id:%d",thetile->tileiid);
	}
	else if(pView->m_draw_which_layer==1){
		sprintf(buf,"���ڱ༭1��  ��ǰtile��id:%d",thetile->tileiid);
	}
	else if(pView->m_draw_which_layer==2){
		sprintf(buf,"���ڱ༭2��  ��ǰtile��id:%d",thetile->tileiid);
	}
	else if(pView->m_draw_which_layer==3){
		sprintf(buf,"���ڱ༭3��  ��ǰtile��id:%d",thetile->tileiid);
	}

	//AfxMessageBox(buf);
	//״̬��
	CStatusBar*   pStatus=(CStatusBar*)AfxGetApp()->m_pMainWnd->GetDescendantWindow(AFX_IDW_STATUS_BAR);   
  //pStatus->SetPaneText(0,"test   string");
	pStatus->SetPaneText(0,buf);


	CClientDC cdc(this);
	//::SetMapMode(cdc,MM_ANISOTROPIC);
	//cdc.LPtoDP(&point);
	this->m_PtOrigin.x=point.x+GetScrollPosition ().x;
	this->m_PtOrigin.y=point.y+GetScrollPosition ().y;
	//ˢ����ɾ��֮ǰ�Ŀ��Ƶ�
	//CRightView * pView=(CRightView*)(((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(1,0));
	this->Invalidate();
	//ջ����
	//classtile clstile;
	//clstile.GetTileInfo();
	//�ѷ���
	//classtile *clstile=new classtile();
	//clstile->GetTileInfo();
	//delete clstile;

	CScrollView::OnLButtonDown(nFlags, point);
}

//��ӡ����(abandoned)
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

//Ѱ��TILE����ڵ��ӦTILE��Ϣ��
// �����ҵ��Ľڵ�TILE
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
		MessageBox("�ȵ����زİ�","info",MB_OK);
		return NULL;
	}
	//
		//��Ȼ������ز�ͼƬ��
	//http://topic.csdn.net/t/20050121/10/3742978.html
	pMf->m_show_control_point=false;//�رտ��Ƶ����ʾ
	this->invalidate_me();
	CClientDC dc(this);
	CDC   memDC;
	memDC.CreateCompatibleDC(&dc); 
	CMainFrame *pMf=(CMainFrame *)AfxGetMainWnd();
	CBitmap   bm;
    if(pMf->m_exp_method==0){
		//MessageBox("�����������");
		bm.CreateCompatibleBitmap(&dc,pMf->m_tileheight,pMf->m_srcbmp_width);  
	}
	else{
		//MessageBox("������Ǻ���");
		bm.CreateCompatibleBitmap(&dc,pMf->m_srcbmp_width,pMf->m_tileheight); 
		//����֮ǰ�·�TILEѡ��������㷨
	}
		//��ɻ�ͼ��,���뽫ԭ���ľɱ�ѡ���豸����  
		//����windows���ܻ�ʹ���Ǹ�ѡ���豸��GDI���������ƿؼ��������ؼ�!  
		
		//��Todo�����ڴ�DC����ͼ

	CBitmap* pOld   = memDC.SelectObject(&bm);
		//memDC.TextOut(0,0,"test");
//���ڶ����ڴ�DC��
//�Ѿ��еĲ���
//dc,memDC(Ŀ���ڴ�DC),bm(no use),pOld��һ���ڴ�DC��֮ǰ��ѡ��GDI����
//Todo���ٴ���1���ڴ�DC:compatible,Ҫ��֮ǰ��DC���ݣ���ô���ݣ����ã�compatible.CreateCompatibleDC(&memDC);\
//pOldbitmap�ڶ����ڴ�DC֮ǰ��ѡ��GDI����
#if 1
	//CClientDC dc2(this);
	HBITMAP hbitmap=(HBITMAP)LoadImage(AfxGetInstanceHandle(),pMf->m_bitmap_pathname,IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE|LR_CREATEDIBSECTION);
	
	//�˴���ȡλͼ��С�������ж���TILE�������Ϳ���BLT���ٴΡ�����ı߽��ϲ�ѡ
	CBitmap   bm1;   
	CBitmap   *pOldbitmap;  
	BITMAP   bwh;
bm1.Attach(hbitmap); //ע�⹤����detach��
//bm1.GetObject(sizeof(BITMAP) , &bwh); //�����GetBitmap��ͨ��
bm1.GetBitmap(&bwh);   
//CString d;
//d.Format("%d",bwh.bmWidth);
//MessageBox(d);
	CDC compatible;//�ڶ����ڴ�DC
	compatible.CreateCompatibleDC(&memDC);//������pDC���ݵ�DC����ʵ�������õ�һ���ڴ�DC
	pOldbitmap=compatible.SelectObject(&bm1);
	int c;//bitblt�Ĵ���
//	assert(pMf->m_tilewidth>=10);//tile��Ҫ̫С�ˣ�������Ƶ�������

	
		c=bwh.bmWidth/pMf->m_tilewidth;
		//ȥ���߽����Ƕ���
		int bitblt_width=c*(pMf->m_tilewidth);
		pMf->m_srcbmp_width=c*(pMf->m_tilewidth);
		pMf->m_srcbmp_height=bwh.bmHeight;
	if(pMf->m_exp_method==0){	
		//memDC.BitBlt(0,0,bwh.bmWidth,bwh.bmHeight,&compatible,0,0,SRCCOPY);  
		for (int i=0;i<c;i++){
			//pDC->BitBlt(nX,nY,bitblt_width,pMf->m_tileheight,&compatible,0,0,SRCCOPY);
			memDC.BitBlt(/*Ŀ�������x*/0,pMf->m_tileheight*i,/*Ŀ��ؿ�*/pMf->m_tilewidth,pMf->m_tileheight,&compatible,\
				/*Դ��������x����*/pMf->m_tilewidth*i,/*rect.TopLeft().y*/0,SRCCOPY);
		}
	}
	else{
		/*CString a;
		a.Format("%d %d",pMf->m_srcbmp_width,pMf->m_srcbmp_height);
		MessageBox(a);*/
		memDC.BitBlt(/*Ŀ�������x*/0,0,/*Ŀ��ؿ�*/pMf->m_srcbmp_width,pMf->m_srcbmp_height,&compatible,\
			/*Դ��������x����*/0,/*rect.TopLeft().y*/0,SRCCOPY);
	}

	//memDC.BitBlt(/*Ŀ���������x����*/0,0,/*Ŀ����ο�*/32,32,&dc,/*Դ��������x����*/0,/*rect.TopLeft().y*/0,SRCCOPY);
memDC.SelectObject(pOld);//ѡ������
compatible.SelectObject(pOldbitmap);
#endif
		//memDC.BitBlt(/*Ŀ���������x����*/0,   0,/*Ŀ����ο�*/   Width,   Height,   dc,   /*Դ��������x����*/0,   /*rect.TopLeft().y*/0,   SRCCOPY);  
		//memDC.SelectObject(pOld);//����bmpѡ���豸
		///////////////////////////////////////////
		//����λͼ

	#if 1
		BITMAP btm;
		bm.GetBitmap(&btm);
		/*  
		DWORD   DataSizePerLine;  
		DWORD   DataSize;  
		DataSizePerLine=   (btm.bmWidth*btm.bmBitsPixel+31)/8;    
		//   һ��ɨ������ռ���ֽ���  
		DataSizePerLine=   DataSizePerLine/4*4;   //   �ֽ���������4�ı���  
		//λͼ���ݵĴ�С(��ѹ�������):  
		DataSize=   DataSizePerLine*   btm.bmHeight;  
		*/   

		DWORD     size   =   btm.bmWidthBytes   *   btm.bmHeight;//λͼ���ݼ�Ϊ���ֽ�*���ֽ�  
		LPSTR   lpData   =   (LPSTR)GlobalAlloc(GPTR,   size);//�����ڴ�

		BITMAPINFOHEADER     bih;//bmpͷ��Ϣ  
		bih.biBitCount   =   btm.bmBitsPixel;//   ÿ�����������λ����������1(˫ɫ),4(16ɫ)��8(256ɫ)��24(���ɫ)֮һ  
		bih.biClrImportant   =   0;//   λͼ��ʾ��������Ҫ����ɫ��  
		bih.biClrUsed   =   0;//   λͼʵ��ʹ�õ���ɫ���е���ɫ��  
		bih.biCompression   =   0;//   λͼѹ�����ͣ�������   0(��ѹ��),1(BI_RLE8ѹ������)��2(BI_RLE4ѹ������)֮һ  
		bih.biHeight   =   btm.bmHeight;//   λͼ�ĸ߶ȣ�������Ϊ��λ  
		bih.biWidth   =   btm.bmWidth;//   λͼ�Ŀ�ȣ�������Ϊ��λ  
		bih.biPlanes   =   1;//   Ŀ���豸�ļ��𣬱���Ϊ1  
		bih.biSize   =   sizeof(BITMAPINFOHEADER);//   ���ṹ��ռ���ֽ���  
		bih.biSizeImage   =   size;//   λͼ�Ĵ�С�����ֽ�Ϊ��λ  
		bih.biWidth   =   btm.bmWidth;  
		bih.biXPelsPerMeter   =   0;//   λͼˮƽ�ֱ��ʣ�ÿ��������  
		bih.biYPelsPerMeter   =   0;//   λͼ��ֱ�ֱ��ʣ�ÿ��������  
		
		GetDIBits(dc,bm,0,bih.biHeight,lpData,(BITMAPINFO*)&bih,DIB_RGB_COLORS);  
		//bm.GetBitmapBits(size,lpData);//�˺����ڴ���5-5-5ģʽ��16λɫ�»������ɫ����  
		
		BITMAPFILEHEADER       bfh;//bmp�ļ�ͷ  
		bfh.bfReserved1   =   bfh.bfReserved2   =   0;//   λͼ�ļ������֣�����Ϊ0  
		bfh.bfType   =   ((WORD)('M'<<   8)|'B');//   λͼ�ļ������ͣ�����ΪBM  
		bfh.bfSize   =   54   +   size;//   λͼ�ļ��Ĵ�С�����ֽ�Ϊ��λ  
		bfh.bfOffBits   =   54;//   λͼ���ݵ���ʼλ�ã��������λͼ�ļ�ͷ��ƫ������ʾ�����ֽ�Ϊ��λ  
		
	
		CFileDialog   dlg(false,_T("BMP"),_T("*.bmp"),OFN_HIDEREADONLY   |   OFN_OVERWRITEPROMPT,_T("*.bmp|*.bmp|*.*|*.*|"));  
		if   (dlg.DoModal()!=IDOK)  {
			pMf->m_show_control_point=true;
			return 0;
		}
		
		CFile     bf;  
		
		CString   ss=dlg.GetPathName();  
		if(bf.Open(ss,   CFile::modeCreate   |   CFile::modeWrite))  
		{  
			bf.WriteHuge(&bfh,   sizeof(BITMAPFILEHEADER));//дbmp�ļ�ͷ  
			bf.WriteHuge(&bih,   sizeof(BITMAPINFOHEADER));//дbmpͷ��Ϣ  
			bf.WriteHuge(lpData,   size);//дbmp����  
			bf.Close();  
			AfxMessageBox("����ɹ�");  
		}  
#if 1
	ReleaseDC(&memDC);
	ReleaseDC(&compatible);
	DeleteObject(hbitmap);
	bm1.Detach();
#endif
		GlobalFree(lpData);//�ͷ��ڴ�
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
	pView->Invalidate(true);//ǿ��ˢ��һ�Σ��������Ƶ����ʧ�ˣ�����λ��������
	//���ǵ��ػ淢��ϢҪʱ���!��
		//OnExpSrcbmp_callback_fun();//�ص������������˳��˵�
	//Todo(Done)��Ϊʲôһ��MessageBox�Ϳ��ԣ�����Ϊ�ػ�Ҫʱ��!!
	//MessageBox("test");
	//Sleep(2000);//��Ҫʹ������API���������ػ���Ϣ��!
	//��ʱ
	Ccommon mycomm;
	mycomm.Delay(100);//�ػ���Ϣ0.1�빻�˰�
	return 1;
}

