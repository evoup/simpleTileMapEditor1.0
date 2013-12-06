// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "MainFrm.h"
#include "LeftTreeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern const int DEF_H,DEF_V;



extern   vector<vector<map_matrix> > Matrix(DEF_V, vector<map_matrix>((int)DEF_H));
/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(IDM_IMPORT_TILES, OnImportTiles)
	ON_COMMAND(IDM_CREATE_MAP, OnCreateMap)
	ON_COMMAND(IDM_EXP_METHOD, OnExpMethod)
	ON_COMMAND(IDM_LAYER_LAND, OnLayerLand)
	ON_COMMAND(IDM_LAYER_OBJECT, OnLayerObject)
	ON_COMMAND(IDM_LAYER_SKY, OnLayerSky)
	ON_COMMAND(IDM_VIEW_LAYER_LAND, OnViewLayerLand)
	ON_COMMAND(IDM_VIEW_LAYER_OBJECT, OnViewLayerObject)
	ON_COMMAND(IDM_VIEW_LAYER_SKY, OnViewLayerSky)
	ON_COMMAND(IDM_SHOW_ALL_LAYER, OnShowAllLayer)
	ON_COMMAND(IDM_FILLALLTILE, OnFillalltile)
	ON_COMMAND(IDM_OPEN_MAP_FILE, OnOpenMapFile)
	ON_COMMAND(IDM_LAYER_OBJECT2, OnLayerObject2)
	ON_COMMAND(IDM_VIEW_LAYER_OBJECT2, OnViewLayerObject2)
	ON_COMMAND(IDM_EXPORT_CODE, OnExportCode)
	ON_COMMAND(IDM_EXP_SRCBMP, OnExpSrcbmp)
	ON_COMMAND(IDM_SET_OBSTACLE, OnSetObstacle)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

//##ModelId=4A1E84730192
CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	this->m_tileid="tile1";
	this->m_tilewidth=0;
	this->m_tileheight=0;
	this->m_maphtiles=0;
	this->m_mapvtiles=0;
	this->m_setmapok=0;
	this->m_settileok=0;
	this->m_bitmap_pathname="";
	this->m_srcbmp_height=0;
	this->m_srcbmp_width=0;
	this->m_Pt_tiles_linklist_headernode=NULL;
	this->m_Pt_blttile=NULL;
	//vector<vector<map_matrix> > Matrix0(1, vector<map_matrix>((int)1));//���Ƕ���
	this->m_b_is_transok=false;
	this->m_exp_method=0;
	this->m_show_control_point=true;
	erasersur=0;
}

//##ModelId=4A1E847301A8
CMainFrame::~CMainFrame()
{
//Matrix0.clear();
}

//##ModelId=4A1E847301C4
int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

//##ModelId=4A1E84730193
BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
//##ModelId=4A1E847301AF
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

//##ModelId=4A1E847301B1
void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers



//##ModelId=4A1E8473019F
BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
 // TODO: Add your specialized code here and/or call the base class
 // create splitter window
 if (!m_wndSplitter.CreateStatic(this, 2, 1))
  return FALSE;
//m_wndSplitter.SetScrollStyle(WS_HSCROLL);
 if (!m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CLeftTreeView),CSize(200, 390), pContext) ||
  !m_wndSplitter.CreateView(1, 0, RUNTIME_CLASS(CRightView), CSize(100, 100), pContext))
 {
  m_wndSplitter.DestroyWindow();
  return FALSE;
 }
 //set the target for mapped messages
// ((CFormLeft*)m_wndSplitter.GetPane(0,0))->SetTarget(m_wndSplitter.GetPane(0,1));

 return TRUE;
}



//##ModelId=4A1E847301C7
void CMainFrame::OnImportTiles() 
{
	// TODO: Add your command handler code here
	CImportTile dlg;
	if(IDOK==dlg.DoModal()){

		//MessageBox("���óɹ���","��ʾ");
		m_tileid=dlg.m_tileid;
		m_tilewidth=dlg.m_tilewidth;
		m_tileheight=dlg.m_tileheight;
		m_settileok=1;//���ñ�ǣ�������OnDraw���ж�
		
	}
}

//##ModelId=4A1E847301CE
void CMainFrame::OnCreateMap() 
{
	// TODO: Add your command handler code here
	//MessageBox("������ͼ");
	CNewmap dlg;
	if(IDOK==dlg.DoModal()){
	MessageBox("������ͼ�ɹ���","��ʾ");
	m_maphtiles=dlg.m_htiles;
	m_mapvtiles=dlg.m_vtiles;
	m_setmapok=1;
	//��ȡmapeditor����ָ��
	CWnd * ptr_mapeditorview=m_wndSplitter.GetPane(0,0);
	ptr_mapeditorview->RedrawWindow();//�ػ棬ǿ���ػ������
	//Ccommon myobj;
	
	}
}


//##ModelId=4A1E847301D0
void CMainFrame::OnExpMethod() 
{
	// TODO: Add your command handler code here
	CExpMethod dlg;
	if(IDOK==dlg.DoModal()){
		if(dlg.m_radio_h)//����������زģ�������������زģ���������������Ա��
			m_exp_method=0;//����Ǻ���Ϊ0
		else
			m_exp_method=1;//�����Ϊ1
		//CString ss;
		//CExpMethod *pt_expm;
		//	pt_expm=(CExpMethod *)GetDlgItem(IDD_DLG_EXP_METHOD);
		
		//ss.Format("%d",this->m_exp_method);
		//MessageBox(ss);
	}
}


//##ModelId=4A1E847301D2
void CMainFrame::OnLayerLand() 
{
	// TODO: Add your command handler code here
	CLeftTreeView * pView=(CLeftTreeView*)(((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(0,0));
	pView->m_draw_which_layer=0;
	((CMainFrame *)AfxGetMainWnd())->erasersur=0;
	//AfxMessageBox("�����",MB_OK);
}

//##ModelId=4A1E847301D4
void CMainFrame::OnLayerObject() 
{
	// TODO: Add your command handler code here
	CLeftTreeView * pView=(CLeftTreeView*)(((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(0,0));
	pView->m_draw_which_layer=1;
	((CMainFrame *)AfxGetMainWnd())->erasersur=0;
	//AfxMessageBox("�����",MB_OK);	
}

//##ModelId=4A1E847301DE
void CMainFrame::OnLayerSky() 
{
	// TODO: Add your command handler code here
	CLeftTreeView * pView=(CLeftTreeView*)(((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(0,0));
	pView->m_draw_which_layer=7;
	//AfxMessageBox("��ղ�",MB_OK);
	((CMainFrame *)AfxGetMainWnd())->erasersur=0;
}

//##ModelId=4A1E847301E0
void CMainFrame::OnViewLayerLand() 
{
	// TODO: Add your command handler code here
	CLeftTreeView * pView=(CLeftTreeView*)(((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(0,0));
	pView->m_view_which_layer=0;
	pView->Invalidate(true);
	//AfxMessageBox("      �鿴�����      ",MB_OK);	
}

//##ModelId=4A1E847301E2
void CMainFrame::OnViewLayerObject() 
{
	// TODO: Add your command handler code here
	CLeftTreeView * pView=(CLeftTreeView*)(((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(0,0));
	pView->m_view_which_layer=1;
	pView->Invalidate(true);
	//AfxMessageBox("      �鿴�����      ",MB_OK);
}

//##ModelId=4A1E847301E4
void CMainFrame::OnViewLayerSky() 
{
	// TODO: Add your command handler code here
	CLeftTreeView * pView=(CLeftTreeView*)(((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(0,0));
	pView->m_view_which_layer=7;
	pView->Invalidate(true);
	//AfxMessageBox("      �鿴��ղ�      ",MB_OK);
}

//##ModelId=4A1E847301E6
void CMainFrame::OnShowAllLayer() 
{
	// TODO: Add your command handler code here
	CLeftTreeView * pView=(CLeftTreeView*)(((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(0,0));
	pView->m_view_which_layer=-1;
	pView->Invalidate(true);
	//AfxMessageBox("      �鿴���в�      ",MB_OK);
}

//##ModelId=4A1E847301EE
void CMainFrame::OnFillalltile() 
{
	// TODO: Add your command handler code here
	CLeftTreeView * pView=(CLeftTreeView*)(((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(0,0));
	pView->FillAllTTiles();
}

//##ModelId=4A1E847301F0
void CMainFrame::OnOpenMapFile() 
{
	// TODO: Add your command handler code here
	//AfxMessageBox("�򿪵�ͼ�ļ�",MB_OK);

#if 1
CFileDialog dlgFile(TRUE);

static CString strFilter = "*.dat";
strFilter += (TCHAR)NULL;
strFilter += "*.dat";
strFilter += (TCHAR)NULL;
strFilter += "*.*";
strFilter += (TCHAR)NULL;
strFilter += "*.*";
strFilter += (TCHAR)NULL;

dlgFile.m_ofn.lpstrFilter = strFilter; 


dlgFile.m_ofn.lpstrTitle ="ѡ���ͼ�ļ�";
dlgFile.m_ofn.lpstrFilter=strFilter;
	if (dlgFile.DoModal()==IDCANCEL) 
	return ; // open cancelled 
	else{
		CString s;
		s.Format("%s",dlgFile.m_ofn.lpstrFile);
		AfxMessageBox(s,MB_OK);

		//this->m_ctr_pic_path.SetWindowText(s);
		this->m_map_file_str=s;
		//CMainFrame *pMf=(CMainFrame*)AfxGetMainWnd();
	}
#endif

	FILE *pfile=fopen(this->m_map_file_str,"rb");
	//��ȥ��MAP��HXXXVXXX���ֶΡ�
#if 1
	int xmax,ymax;
	char s[100];//����Դ
	char thestr[20];
	char buf[300];
	//���ݸ�ʽ mapH100V200|
	//�Ȼ�ȡ100���ַ��������������ͼ�������|��ͼ��������$�����ַ���
	fgets(s,100,pfile);
	fclose(pfile);
	//const char* s = "mapH100V200|";
	sscanf( s, "%*[^H]H%[^V]", thestr );
	sprintf(buf,"%s",thestr);
	//MessageBox(globalhwnd,buf,"",MB_OK);
	AfxMessageBox(buf,MB_OK);
	xmax=atoi(thestr)-1;//��Ϊ�±��Ǵ�0��ʼ���ʼ�ȥ1
	sscanf( s, "%*[^V]V%[^|]", thestr );
	sprintf(buf,"%s",thestr);
	//MessageBox(globalhwnd,buf,"",MB_OK);	
	AfxMessageBox(buf,MB_OK);
	ymax=atoi(thestr)-1;
	int cut_str_num;//֮�󲿷ֵľ��ǵ�ͼCELL������
	///�����CELL����������ַ�����������MAP:H112V123|��Щ�ַ���������
	int tmp_mapdata_xMax=xmax;
	int tmp_mapdata_yMax=ymax;
	int   weishu   =   1;  
	while(1){  
		tmp_mapdata_xMax   /=   10;  
		if   (tmp_mapdata_xMax){  
			weishu++;  
		}  
		else{  
			break;  
		}  
	}   
	while(1){  
		tmp_mapdata_yMax   /=   10;  
		if   (tmp_mapdata_yMax){  
			weishu++;  
		}  
		else{  
			break;  
		}  
	}   

	cut_str_num=7+weishu;//MAP:HV|��7λ��
	
	if ((pfile = fopen(this->m_map_file_str, "rb")) == NULL)
		return;
	for(int i=0;i<13;i++){
		getc(pfile);//�е���Щ�ַ�
	}
#endif
	
#if 1
	CLeftTreeView * pView=(CLeftTreeView*)(((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(0,0));
	// now read the actual map data and close the file
	for (int x=0; x<=xmax; x++)
	{
		for (int y=0; y<=ymax; y++)
		{
			//byMap[x][y][0] = getc(pfile);
			//byMap[x][y][1] = getc(pfile);
			pView->load_map2matrix_element(x,y,0,getc(pfile));
			pView->load_map2matrix_element(x,y,1,getc(pfile));
			pView->load_map2matrix_element(x,y,2,getc(pfile));
		}
	}
	fclose(pfile);
	pView->Invalidate();
#endif

}

//##ModelId=4A1E847301F2
void CMainFrame::OnLayerObject2() 
{
	// TODO: Add your command handler code here
	CLeftTreeView * pView=(CLeftTreeView*)(((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(0,0));
	pView->m_draw_which_layer=2;
	//AfxMessageBox("�����2",MB_OK);
	((CMainFrame *)AfxGetMainWnd())->erasersur=0;
}

//##ModelId=4A1E847301F4
void CMainFrame::OnViewLayerObject2() 
{
	// TODO: Add your command handler code here
	CLeftTreeView * pView=(CLeftTreeView*)(((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(0,0));
	pView->m_view_which_layer=2;
	pView->Invalidate(true);
	//AfxMessageBox("�鿴�����2",MB_OK);
}

//##ModelId=4B06766A02FD
void CMainFrame::OnExportCode() 
{
	// TODO: Add your command handler code here
		// TODO: Add your command handler code here
	//CString ss;
	//ss.Format("%d",Matrix[0][0].tileiid);
	//MessageBox(ss);
	CLeftTreeView * pView=(CLeftTreeView*)(((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(0,0));
	if (!pView->CheckOK()) return;
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
	CMainFrame *pMf=(CMainFrame*)AfxGetMainWnd();
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

//##ModelId=4B06766A031D
void CMainFrame::OnExpSrcbmp() 
{
	// TODO: Add your command handler code here
	CRightView * pView=(CRightView*)(((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(1,0));
 pView->Export_src_bmp();
}

//##ModelId=4B06766A033D
void CMainFrame::OnSetObstacle() 
{
	// TODO: Add your command handler code here
	((CMainFrame *)AfxGetMainWnd())->erasersur=1;
}
