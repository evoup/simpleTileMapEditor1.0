// SplitWndDemo.h : main header file for the SPLITWNDDEMO application
//

#if !defined(AFX_SPLITWNDDEMO_H__72E0CE96_F07C_47A9_87F7_1BF20768531F__INCLUDED_)
#define AFX_SPLITWNDDEMO_H__72E0CE96_F07C_47A9_87F7_1BF20768531F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSplitWndDemoApp:
// See SplitWndDemo.cpp for the implementation of this class
//

//##ModelId=4A1E847300D7
class CSplitWndDemoApp : public CWinApp
{
public:
	//##ModelId=4A1E847300D9
	CSplitWndDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSplitWndDemoApp)
	public:
	//##ModelId=4A1E847300DA
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CSplitWndDemoApp)
	//##ModelId=4A1E847300E5
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPLITWNDDEMO_H__72E0CE96_F07C_47A9_87F7_1BF20768531F__INCLUDED_)
