// Newmap.cpp : implementation file
//

#include "stdafx.h"
#include "SplitWndDemo.h"
#include "Newmap.h"
//#include "MainFrm.h"
//#include "RightView.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNewmap dialog


//##ModelId=4A1E84730151
CNewmap::CNewmap(CWnd* pParent /*=NULL*/)
	: CDialog(CNewmap::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNewmap)
	m_mapid = _T("map1");
	m_vtiles = 500;
	m_htiles = 500;
	//}}AFX_DATA_INIT
}


//##ModelId=4A1E84730156
void CNewmap::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewmap)
	DDX_Text(pDX, IDC_Mapid, m_mapid);
	DDX_Text(pDX, IDC_vtiles, m_vtiles);
	DDX_Text(pDX, IDC_htiles, m_htiles);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNewmap, CDialog)
	//{{AFX_MSG_MAP(CNewmap)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewmap message handlers

//##ModelId=4A1E84730159
void CNewmap::OnOK() 
{
	// TODO: Add extra validation here

	CDialog::OnOK();
}
