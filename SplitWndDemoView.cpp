// SplitWndDemoView.cpp : implementation of the CSplitWndDemoView class
//

#include "stdafx.h"
#include "SplitWndDemo.h"

#include "SplitWndDemoDoc.h"
#include "SplitWndDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSplitWndDemoView

IMPLEMENT_DYNCREATE(CSplitWndDemoView, CView)

BEGIN_MESSAGE_MAP(CSplitWndDemoView, CView)
	//{{AFX_MSG_MAP(CSplitWndDemoView)
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSplitWndDemoView construction/destruction

//##ModelId=4A1E847300AB
CSplitWndDemoView::CSplitWndDemoView()
{
	// TODO: add construction code here

}

//##ModelId=4A1E847300BE
CSplitWndDemoView::~CSplitWndDemoView()
{
}

//##ModelId=4A1E847300B0
BOOL CSplitWndDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CSplitWndDemoView drawing

//##ModelId=4A1E847300AD
void CSplitWndDemoView::OnDraw(CDC* pDC)
{
	CSplitWndDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CSplitWndDemoView printing

//##ModelId=4A1E847300B3
BOOL CSplitWndDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

//##ModelId=4A1E847300B6
void CSplitWndDemoView::OnBeginPrinting(CDC *pDC /*pDC*/, CPrintInfo *pInfo /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

//##ModelId=4A1E847300BA
void CSplitWndDemoView::OnEndPrinting(CDC *pDC /*pDC*/, CPrintInfo *pInfo /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CSplitWndDemoView diagnostics

#ifdef _DEBUG
//##ModelId=4A1E847300C0
void CSplitWndDemoView::AssertValid() const
{
	CView::AssertValid();
}

//##ModelId=4A1E847300C2
void CSplitWndDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

//##ModelId=4A1E847300AC
CSplitWndDemoDoc* CSplitWndDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSplitWndDemoDoc)));
	return (CSplitWndDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSplitWndDemoView message handlers

//##ModelId=4A1E847300C5
BOOL CSplitWndDemoView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	//#####################

	//#####################
	return CView::OnEraseBkgnd(pDC);
}
