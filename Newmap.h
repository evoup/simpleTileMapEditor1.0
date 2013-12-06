#if !defined(AFX_NEWMAP_H__21BD5310_FC11_4061_BB59_EB027E6EE382__INCLUDED_)
#define AFX_NEWMAP_H__21BD5310_FC11_4061_BB59_EB027E6EE382__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Newmap.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNewmap dialog

//##ModelId=4A1E84730144
class CNewmap : public CDialog
{
// Construction
public:
	//##ModelId=4A1E84730151
	CNewmap(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNewmap)
	enum { IDD = IDD_DLG_NEW_MAP };
	//##ModelId=4A1E84730153
	CString	m_mapid;
	//##ModelId=4A1E84730154
	UINT	m_vtiles;
	//##ModelId=4A1E84730155
	UINT	m_htiles;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewmap)
	protected:
	//##ModelId=4A1E84730156
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNewmap)
	//##ModelId=4A1E84730159
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWMAP_H__21BD5310_FC11_4061_BB59_EB027E6EE382__INCLUDED_)
