// SplitWndDemoDoc.h : interface of the CSplitWndDemoDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPLITWNDDEMODOC_H__5BC48B4A_C102_4C65_9198_ECD2DB51A1A9__INCLUDED_)
#define AFX_SPLITWNDDEMODOC_H__5BC48B4A_C102_4C65_9198_ECD2DB51A1A9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


//##ModelId=4A1E847300C8
class CSplitWndDemoDoc : public CDocument
{
protected: // create from serialization only
	//##ModelId=4A1E847300CA
	CSplitWndDemoDoc();
	DECLARE_DYNCREATE(CSplitWndDemoDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSplitWndDemoDoc)
	public:
	//##ModelId=4A1E847300CB
	virtual BOOL OnNewDocument();
	//##ModelId=4A1E847300CD
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	//##ModelId=4A1E847300D0
	virtual ~CSplitWndDemoDoc();
#ifdef _DEBUG
	//##ModelId=4A1E847300D2
	virtual void AssertValid() const;
	//##ModelId=4A1E847300D4
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSplitWndDemoDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPLITWNDDEMODOC_H__5BC48B4A_C102_4C65_9198_ECD2DB51A1A9__INCLUDED_)
