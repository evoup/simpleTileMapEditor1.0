// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////
#include "classtile.h"
#include "SplitWndDemo.h"
#include "LeftTreeView.h"
#include "RightView.h"
#include "ImportTile.h"
#include "Newmap.h"
#include "common.h"
#include "ExpMethod.h"
#include <vector>
using namespace std;
#if !defined(AFX_MAINFRM_H__CD56549E_8C3F_4703_8C20_9AD084B85B65__INCLUDED_)
#define AFX_MAINFRM_H__CD56549E_8C3F_4703_8C20_9AD084B85B65__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//ע������ṹ����һ�������ˣ���LeftTreeView.h�2����һ���ģ��������Ҳ����ṹ����ʱ���������
//Todo:��һ�½ṹ�Ķ���ĵط�
#ifndef STRUCT_MAP_MATRIX
#define STRUCT_MAP_MATRIX
//����ṹ
//##ModelId=4A1E8473015B
typedef struct map_matrix{
	//##ModelId=4A1E84730163
RECT therect;
	//##ModelId=4A1E84730167
int tileiid;//������id
	//##ModelId=4A1E84730168
int layer_obj_tileiid;//�����1��id
	//##ModelId=4A1E84730169
int layer_obj2_tileiid;//�����2��id
	//##ModelId=4A1E84730170
int layer_sky_tileiid;//��ղ��id
int layer_obstacle;//�ϰ����
}*map_matrix_struct;
#endif

//##ModelId=4A1E84730190
class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	//##ModelId=4A1E84730192
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	//##ModelId=4A1E84730193
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//##ModelId=4A1E8473019F
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
public:
	//##ModelId=4A1E847301A4
	CSplitterWnd m_wndSplitter;
	//##ModelId=4A1E847301A8
	virtual ~CMainFrame();
#ifdef _DEBUG
	//##ModelId=4A1E847301AF
	virtual void AssertValid() const;
	//##ModelId=4A1E847301B1
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	//##ModelId=4A1E847301B5
	CStatusBar  m_wndStatusBar;
	//##ModelId=4A1E847301C0
	CToolBar    m_wndToolBar;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	//##ModelId=4A1E847301C4
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//##ModelId=4A1E847301C7
	afx_msg void OnImportTiles();
	//##ModelId=4A1E847301CE
	afx_msg void OnCreateMap();
	//##ModelId=4A1E847301D0
	afx_msg void OnExpMethod();
	//##ModelId=4A1E847301D2
	afx_msg void OnLayerLand();
	//##ModelId=4A1E847301D4
	afx_msg void OnLayerObject();
	//##ModelId=4A1E847301DE
	afx_msg void OnLayerSky();
	//##ModelId=4A1E847301E0
	afx_msg void OnViewLayerLand();
	//##ModelId=4A1E847301E2
	afx_msg void OnViewLayerObject();
	//##ModelId=4A1E847301E4
	afx_msg void OnViewLayerSky();
	//##ModelId=4A1E847301E6
	afx_msg void OnShowAllLayer();
	//##ModelId=4A1E847301EE
	afx_msg void OnFillalltile();
	//##ModelId=4A1E847301F0
	afx_msg void OnOpenMapFile();
	//##ModelId=4A1E847301F2
	afx_msg void OnLayerObject2();
	//##ModelId=4A1E847301F4
	afx_msg void OnViewLayerObject2();
	//##ModelId=4B06766A02FD
	afx_msg void OnExportCode();
	//##ModelId=4B06766A031D
	afx_msg void OnExpSrcbmp();
	//##ModelId=4B06766A033D
	afx_msg void OnSetObstacle();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	int erasersur;
	//##ModelId=4A1E847301F6
	CString m_map_file_str;
	//##ModelId=4A1E847301F7
	bool m_show_control_point;
	//##ModelId=4A1E847301FD
	int m_exp_method;
	//##ModelId=4A1E847301FE
	bool m_b_is_transok;//���󴫵ݱ�ǣ�������ֹδ��ʼ������
	//##ModelId=4A1E847301FF
	UINT m_srcbmp_width;//�زĿ��
	//##ModelId=4A1E84730200
	UINT m_srcbmp_height;//�زĸ߶�
	//##ModelId=4A1E84730201
	CString m_bitmap_pathname;
	//##ModelId=4A1E84730202
	UINT m_setmapok;
	//##ModelId=4A1E84730203
	UINT m_settileok;
	//##ModelId=4A1E8473020D
	UINT m_maphtiles;
	//##ModelId=4A1E8473020E
	UINT m_mapvtiles;
	//##ModelId=4A1E8473020F
	CString m_tileid;
	//##ModelId=4A1E84730210
	UINT m_tilewidth;
	//##ModelId=4A1E84730211
	UINT m_tileheight;
	//##ModelId=4A1E84730213
	struct tiles *m_Pt_tiles_linklist_headernode;//�������ش���ѡ��TILE�������ķ���ֵ(����ͷ���)
	//##ModelId=4A1E8473021D
	struct tiles *m_Pt_blttile;
	//vector<vector<map_matrix> > Matrix0;//����������������Ϻ�һ���Ӷ���40��Warning��
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__CD56549E_8C3F_4703_8C20_9AD084B85B65__INCLUDED_)
