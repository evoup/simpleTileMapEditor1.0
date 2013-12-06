// ImportTile.cpp : implementation file
//

#include "stdafx.h"
#include "SplitWndDemo.h"
#include "ImportTile.h"
#include "MainFrm.h"
#include "classtile.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImportTile dialog


//##ModelId=4A1E84730318
CImportTile::CImportTile(CWnd* pParent /*=NULL*/)
	: CDialog(CImportTile::IDD, pParent)
{
	//{{AFX_DATA_INIT(CImportTile)
	m_tileid = _T("tile1");
	m_tilewidth = 32;
	m_tileheight = 32;
	//}}AFX_DATA_INIT
}


//##ModelId=4A1E8473032D
void CImportTile::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CImportTile)
	DDX_Control(pDX, IDC_EDIT_PIC_PATH, m_ctr_pic_path);
	DDX_Text(pDX, IDC_EDIT_TILE_ID, m_tileid);
	DDX_Text(pDX, IDC_EDIT_TILE_W, m_tilewidth);
	DDX_Text(pDX, IDC_EDIT_TILE_H, m_tileheight);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CImportTile, CDialog)
	//{{AFX_MSG_MAP(CImportTile)
	ON_BN_CLICKED(IDC_BUTTON_SELECT_FILE, OnButtonSelectFile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImportTile message handlers

//##ModelId=4A1E84730330
void CImportTile::OnButtonSelectFile() 
{
	// TODO: Add your control notification handler code here
CFileDialog dlgFile(TRUE);

static CString strFilter = "*.bmp";
strFilter += (TCHAR)NULL;
strFilter += "*.bmp";
strFilter += (TCHAR)NULL;
strFilter += "*.*";
strFilter += (TCHAR)NULL;
strFilter += "*.*";
strFilter += (TCHAR)NULL;

dlgFile.m_ofn.lpstrFilter = strFilter; 


dlgFile.m_ofn.lpstrTitle ="选择作为Tile的素材";
dlgFile.m_ofn.lpstrFilter=strFilter;
	if (dlgFile.DoModal()==IDCANCEL) 
	return ; // open cancelled 
	else{
		CString s;
		s.Format("%s",dlgFile.m_ofn.lpstrFile);
		this->m_ctr_pic_path.SetWindowText(s);
		CMainFrame *pMf=(CMainFrame*)AfxGetMainWnd();
		pMf->m_bitmap_pathname=s;
	}

}



//##ModelId=4A1E84730336
void CImportTile::OnOK() 
{
	// TODO: Add extra validation here

struct tparam *tp=(struct tparam *)malloc(sizeof(struct tparam));
tp->bitmap_width=300;
CString th,tw,imagesrc;
AfxGetMainWnd()->GetActiveWindow()->GetDlgItemText(IDC_EDIT_TILE_H,th);
AfxGetMainWnd()->GetActiveWindow()->GetDlgItemText(IDC_EDIT_TILE_W,tw);
AfxGetMainWnd()->GetActiveWindow()->GetDlgItemText(IDC_EDIT_PIC_PATH,imagesrc);
tp->tile_height=atoi(th);

tp->tile_width=atoi(tw);

tp->imagesrc=(LPSTR)(LPCTSTR)imagesrc;



struct tiles * h;
	classtile clstile;

	h=clstile.CreateTilelist(tp);
	CMainFrame * pMf=(CMainFrame *)AfxGetMainWnd();
	pMf->m_Pt_tiles_linklist_headernode=h;
	//获取下方TILE选择区域的视类指针
//指向的这个指针保存malloc得到的链表
	CDialog::OnOK();
}
