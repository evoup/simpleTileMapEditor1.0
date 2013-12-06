#if !defined(AFX_IMPORTTILE_H__FB4DA25A_6EBF_4D92_BDB3_47E2E4B98E85__INCLUDED_)
#define AFX_IMPORTTILE_H__FB4DA25A_6EBF_4D92_BDB3_47E2E4B98E85__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ImportTile.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CImportTile dialog

//##ModelId=4A1E84730316
class CImportTile : public CDialog
{
// Construction
public:
	//##ModelId=4A1E84730318
	CImportTile(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CImportTile)
	enum { IDD = IDD_DLG_SET_TILE_SIZE };
	//##ModelId=4A1E84730326
	CEdit	m_ctr_pic_path;
	//##ModelId=4A1E8473032A
	CString	m_tileid;
	//##ModelId=4A1E8473032B
	UINT	m_tilewidth;
	//##ModelId=4A1E8473032C
	UINT	m_tileheight;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImportTile)
	protected:
	//##ModelId=4A1E8473032D
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CImportTile)
	//##ModelId=4A1E84730330
	afx_msg void OnButtonSelectFile();
	//##ModelId=4A1E84730336
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMPORTTILE_H__FB4DA25A_6EBF_4D92_BDB3_47E2E4B98E85__INCLUDED_)
