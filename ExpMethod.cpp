// ExpMethod.cpp : implementation file
//

#include "stdafx.h"
#include "splitwnddemo.h"
#include "ExpMethod.h"
#include "MainFrm.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExpMethod dialog


//##ModelId=4A1E8473033A
CExpMethod::CExpMethod(CWnd* pParent /*=NULL*/)
	: CDialog(CExpMethod::IDD, pParent)
{
	//{{AFX_DATA_INIT(CExpMethod)
	m_radio_h = -1;
	m_radio_v = 0;
	//}}AFX_DATA_INIT
}


//##ModelId=4A1E84730348
void CExpMethod::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CExpMethod)
	DDX_Radio(pDX, IDC_RADIO_H, m_radio_h);
	DDX_Radio(pDX, IDC_RADIO_V, m_radio_v);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CExpMethod, CDialog)
	//{{AFX_MSG_MAP(CExpMethod)
	ON_COMMAND(IDM_EXP_METHOD, OnExpMethod)
	ON_COMMAND(IDM_EXP_SRCBMP, OnExpSrcbmp)
	ON_BN_CLICKED(IDC_RADIO_H, OnRadioH_click)
	ON_BN_CLICKED(IDC_RADIO_V, OnRadioV_click)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExpMethod message handlers

//##ModelId=4A1E8473034B
void CExpMethod::OnExpMethod() 
{
	// TODO: Add your command handler code here
	
}



//##ModelId=4A1E8473034D
void CExpMethod::OnExpSrcbmp() 
{
	// TODO: Add your command handler code here
	
}

//##ModelId=4A1E8473034F
void CExpMethod::OnRadioH_click() 
{
	// TODO: Add your control notification handler code here

	UpdateData(TRUE); 
	m_radio_v=-1;
	CMainFrame *pMf=(CMainFrame *)AfxGetMainWnd();
	pMf->m_exp_method=0;
	UpdateData(FALSE); 
}

//##ModelId=4A1E84730355
void CExpMethod::OnRadioV_click() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); 
	m_radio_h=-1;
	CMainFrame *pMf=(CMainFrame *)AfxGetMainWnd();
	pMf->m_exp_method=1;
	UpdateData(FALSE); 
}
