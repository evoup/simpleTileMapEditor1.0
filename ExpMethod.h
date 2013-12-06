#if !defined(AFX_EXPMETHOD_H__0CA6BE86_F168_405F_AB65_7035A56AD74A__INCLUDED_)
#define AFX_EXPMETHOD_H__0CA6BE86_F168_405F_AB65_7035A56AD74A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ExpMethod.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CExpMethod dialog

//##ModelId=4A1E84730338
class CExpMethod : public CDialog
{
// Construction
public:
	//##ModelId=4A1E8473033A
	CExpMethod(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CExpMethod)
	enum { IDD = IDD_DLG_EXP_METHOD };
	//##ModelId=4A1E84730346
	int		m_radio_h;
	//##ModelId=4A1E84730347
	int		m_radio_v;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExpMethod)
	protected:
	//##ModelId=4A1E84730348
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CExpMethod)
	//##ModelId=4A1E8473034B
	afx_msg void OnExpMethod();
	//##ModelId=4A1E8473034D
	afx_msg void OnExpSrcbmp();
	//##ModelId=4A1E8473034F
	afx_msg void OnRadioH_click();
	//##ModelId=4A1E84730355
	afx_msg void OnRadioV_click();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXPMETHOD_H__0CA6BE86_F168_405F_AB65_7035A56AD74A__INCLUDED_)
