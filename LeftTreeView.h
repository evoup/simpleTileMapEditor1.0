#if !defined(AFX_LEFTTREEVIEW_H__4B72CF8E_E72D_4906_A876_4881C232236F__INCLUDED_)
#define AFX_LEFTTREEVIEW_H__4B72CF8E_E72D_4906_A876_4881C232236F__INCLUDED_
#pragma   warning(disable:4786)
#include "MainFrm.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LeftTreeView.h : header file
//
#include   <afxcview.h>
#include <vector>

using namespace std;

#ifndef STRUCT_MAP_MATRIX
#define STRUCT_MAP_MATRIX
//##ModelId=4B06766A035B
extern struct map_matrix{
	//##ModelId=4B06766A036D
RECT therect;
	//##ModelId=4B06766A0371
int tileiid;//地面层的id
	//##ModelId=4B06766A03C8
int layer_obj_tileiid;//物件层1的id
	//##ModelId=4B06766A03C9
int layer_obj2_tileiid;//物件层2的id
	//##ModelId=4B06766A03D8
int layer_sky_tileiid;//天空层的id
int layer_obstacle;//障碍层的
}*map_matrix_struct;
#endif

const int DEF_H=500;//水平TILE数量上限
const int DEF_V=500;//垂直TILE数量上限	
/////////////////////////////////////////////////////////////////////////////
// CLeftTreeView view

//##ModelId=4A1E8473023C
class CLeftTreeView : public CScrollView
{
protected:
	//##ModelId=4A1E8473024B
	CLeftTreeView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CLeftTreeView)

// Attributes
public:

// Operations
public:
	//##ModelId=4A1E8473025B
	bool DrawTile(CPoint point);
	//##ModelId=4A1E8473025D
	bool getMatrix(vector<vector<map_matrix> >& v);
//	CString m_pathname;
	//##ModelId=4A1E8473025F
	bool CheckOK();
	//##ModelId=4A1E8473026B
	CMainFrame *pMf;
	//##ModelId=4A1E8473026F
	void InitialDBB();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLeftTreeView)
	public:
	//##ModelId=4A1E8473027A
	virtual void OnInitialUpdate();
	//##ModelId=4A1E8473027C
	virtual BOOL OnScroll(UINT nScrollCode, UINT nPos, BOOL bDoScroll = TRUE);
	protected:
	//##ModelId=4A1E8473028C
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	//##ModelId=4A1E84730299
	virtual ~CLeftTreeView();
#ifdef _DEBUG
	//##ModelId=4A1E847302A9
	virtual void AssertValid() const;
	//##ModelId=4A1E847302B9
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CLeftTreeView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnExportCode();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnEraseSmall();
	afx_msg void OnEraseMiddle();
	afx_msg void OnEraseBig();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	//##ModelId=4B06766B00EA
	int m_erase;
	
	//##ModelId=4A1E847302EB
	bool m_lbutton_is_down;
	//##ModelId=4A1E847302EC
	CPoint m_ptOrigin;
	//##ModelId=4A1E847302F8
	CBitmap m_Bmp;
	//##ModelId=4A1E847302FD
	CDC m_dcMemory;
	//##ModelId=4A1E84730301
	BOOL m_bUseDBB;

public:
	HCURSOR cur;
	//##ModelId=4A1E84730302
	void load_map2matrix_element(int V,int H,int layer,int value);
	//##ModelId=4A1E8473030B
	bool FillAllTTiles();
	//##ModelId=4A1E8473030C
	int m_view_which_layer;
	//##ModelId=4A1E8473030D
	int m_draw_which_layer;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LEFTTREEVIEW_H__4B72CF8E_E72D_4906_A876_4881C232236F__INCLUDED_)
