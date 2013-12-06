// SplitWndDemoDoc.cpp : implementation of the CSplitWndDemoDoc class
//

#include "stdafx.h"
#include "SplitWndDemo.h"

#include "SplitWndDemoDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSplitWndDemoDoc

IMPLEMENT_DYNCREATE(CSplitWndDemoDoc, CDocument)

BEGIN_MESSAGE_MAP(CSplitWndDemoDoc, CDocument)
	//{{AFX_MSG_MAP(CSplitWndDemoDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSplitWndDemoDoc construction/destruction

//##ModelId=4A1E847300CA
CSplitWndDemoDoc::CSplitWndDemoDoc()
{
	// TODO: add one-time construction code here

}

//##ModelId=4A1E847300D0
CSplitWndDemoDoc::~CSplitWndDemoDoc()
{
}

//##ModelId=4A1E847300CB
BOOL CSplitWndDemoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CSplitWndDemoDoc serialization

//##ModelId=4A1E847300CD
void CSplitWndDemoDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CSplitWndDemoDoc diagnostics

#ifdef _DEBUG
//##ModelId=4A1E847300D2
void CSplitWndDemoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

//##ModelId=4A1E847300D4
void CSplitWndDemoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSplitWndDemoDoc commands
