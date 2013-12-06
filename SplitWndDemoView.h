// SplitWndDemoView.h : interface of the CSplitWndDemoView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPLITWNDDEMOVIEW_H__693EE6D6_8F11_47B8_90FB_BDD739CEB85C__INCLUDED_)
#define AFX_SPLITWNDDEMOVIEW_H__693EE6D6_8F11_47B8_90FB_BDD739CEB85C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


//##ModelId=4A1E847300A9
class CSplitWndDemoView : public CView
{
protected: // create from serialization only
	//##ModelId=4A1E847300AB
	CSplitWndDemoView();
	DECLARE_DYNCREATE(CSplitWndDemoView)

// Attributes
public:
	//##ModelId=4A1E847300AC
	CSplitWndDemoDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSplitWndDemoView)
	public:
	//##ModelId=4A1E847300AD
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	//##ModelId=4A1E847300B0
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//##ModelId=4A1E847300B3
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	//##ModelId=4A1E847300B6
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	//##ModelId=4A1E847300BA
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	//##ModelId=4A1E847300BE
	virtual ~CSplitWndDemoView();
#ifdef _DEBUG
	//##ModelId=4A1E847300C0
	virtual void AssertValid() const;
	//##ModelId=4A1E847300C2
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSplitWndDemoView)
	//##ModelId=4A1E847300C5
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in SplitWndDemoView.cpp
inline CSplitWndDemoDoc* CSplitWndDemoView::GetDocument()
   { return (CSplitWndDemoDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPLITWNDDEMOVIEW_H__693EE6D6_8F11_47B8_90FB_BDD739CEB85C__INCLUDED_)
