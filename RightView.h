#if !defined(AFX_RIGHTVIEW_H__D81B8732_6ADA_4652_A0A1_55C15A2DF50C__INCLUDED_)
#define AFX_RIGHTVIEW_H__D81B8732_6ADA_4652_A0A1_55C15A2DF50C__INCLUDED_

#include "MainFrm.h"	// Added by ClassView
#include "classtile.h"
#if _MSC_VER > 1000
//#pragma once
#endif // _MSC_VER > 1000
// RightView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRightView view

//##ModelId=4A1E847300F3
class CRightView : public CScrollView
{
protected:
	//##ModelId=4A1E847300F5
	CRightView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CRightView)

// Attributes
public:

// Operations
public:
	//##ModelId=4A1E84730103
	bool invalidate_me();
	//##ModelId=4A1E84730104
	bool Export_src_bmp();
	//##ModelId=4A1E84730105
	struct tiles * find_tile(struct tiles *s,int x,int y);
	//##ModelId=4A1E84730109
	bool display_tile_linklist(struct tiles *s);
	//##ModelId=4A1E8473010B
	CPoint m_PtOrigin;
	//##ModelId=4A1E84730114
	CMainFrame *pMf;
	
	//##ModelId=4A1E84730118
	bool CheckOK();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRightView)
	public:
	//##ModelId=4A1E84730119
	virtual void OnInitialUpdate();
	protected:
	//##ModelId=4A1E8473011B
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	//##ModelId=4A1E84730124
	virtual ~CRightView();
#ifdef _DEBUG
	//##ModelId=4A1E84730126
	virtual void AssertValid() const;
	//##ModelId=4A1E84730133
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CRightView)
	//##ModelId=4A1E84730136
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//##ModelId=4A1E84730142
	afx_msg void OnExpSrcbmp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RIGHTVIEW_H__D81B8732_6ADA_4652_A0A1_55C15A2DF50C__INCLUDED_)
