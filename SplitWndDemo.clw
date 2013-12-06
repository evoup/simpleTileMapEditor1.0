; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMainFrame
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "splitwnddemo.h"
LastPage=0

ClassCount=10
Class1=CImportTile
Class2=CLeftTreeView
Class3=CMainFrame
Class4=CNewmap
Class5=CRightView
Class6=CSplitWndDemoApp
Class7=CAboutDlg
Class8=CSplitWndDemoDoc
Class9=CSplitWndDemoView

ResourceCount=6
Resource1=IDR_MAINFRAME
Resource2=IDD_ABOUTBOX
Resource3=IDD_DLG_NEW_MAP
Resource4=IDD_DIALOG1
Resource5=IDD_DLG_SET_TILE_SIZE
Class10=CExpMethod
Resource6=IDD_DLG_EXP_METHOD

[CLS:CImportTile]
Type=0
BaseClass=CDialog
HeaderFile=ImportTile.h
ImplementationFile=ImportTile.cpp
LastObject=IDOK
Filter=D
VirtualFilter=dWC

[CLS:CLeftTreeView]
Type=0
BaseClass=CScrollView
HeaderFile=LeftTreeView.h
ImplementationFile=LeftTreeView.cpp
LastObject=IDM_EXP_METHOD
Filter=C
VirtualFilter=VWC

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
VirtualFilter=fWC
LastObject=IDM_LAYER_NPC

[CLS:CNewmap]
Type=0
BaseClass=CDialog
HeaderFile=Newmap.h
ImplementationFile=Newmap.cpp
LastObject=IDOK

[CLS:CRightView]
Type=0
BaseClass=CScrollView
HeaderFile=RightView.h
ImplementationFile=RightView.cpp
Filter=C
VirtualFilter=VWC

[CLS:CSplitWndDemoApp]
Type=0
BaseClass=CWinApp
HeaderFile=SplitWndDemo.h
ImplementationFile=SplitWndDemo.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=SplitWndDemo.cpp
ImplementationFile=SplitWndDemo.cpp
LastObject=CAboutDlg

[CLS:CSplitWndDemoDoc]
Type=0
BaseClass=CDocument
HeaderFile=SplitWndDemoDoc.h
ImplementationFile=SplitWndDemoDoc.cpp

[CLS:CSplitWndDemoView]
Type=0
BaseClass=CView
HeaderFile=SplitWndDemoView.h
ImplementationFile=SplitWndDemoView.cpp

[DLG:IDD_DLG_SET_TILE_SIZE]
Type=1
Class=CImportTile
ControlCount=11
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT_TILE_W,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT_TILE_H,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EDIT_TILE_ID,edit,1350631552
Control9=IDC_STATIC,static,1342177287
Control10=IDC_EDIT_PIC_PATH,edit,1350631552
Control11=IDC_BUTTON_SELECT_FILE,button,1342279424

[DLG:IDD_DLG_NEW_MAP]
Type=1
Class=CNewmap
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_Mapid,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_htiles,edit,1350631552
Control8=IDC_vtiles,edit,1350631552

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342308480
Control2=IDC_STATIC,static,1342308352
Control3=IDOK,button,1342373889
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_MRU_FILE1
Command6=ID_APP_EXIT
Command7=IDM_IMPORT_TILES
Command8=IDM_CREATE_MAP
Command9=IDM_OPEN_MAP_FILE
Command10=IDM_LAYER_LAND
Command11=IDM_LAYER_OBJECT
Command12=IDM_LAYER_OBJECT2
Command13=IDM_LAYER_SKY
Command14=IDM_LAYER_NPC
Command15=IDM_VIEW_LAYER_LAND
Command16=IDM_VIEW_LAYER_OBJECT
Command17=IDM_VIEW_LAYER_OBJECT2
Command18=IDM_VIEW_LAYER_SKY
Command19=IDM_VIEW_LAYER_NPC
Command20=IDM_SHOW_ALL_LAYER
Command21=IDM_SET_OBSTACLE
Command22=IDM_EXPORT_CODE
Command23=IDM_EXP_METHOD
Command24=IDM_EXP_SRCBMP
Command25=IDM_ERASE_SMALL
Command26=IDM_ERASE_MIDDLE
Command27=IDM_ERASE_BIG
Command28=ID_VIEW_TOOLBAR
Command29=ID_VIEW_STATUS_BAR
Command30=ID_APP_ABOUT
CommandCount=30

[ACL:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[DLG:IDD_DIALOG1]
Type=1
Class=?
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816

[DLG:IDD_DLG_EXP_METHOD]
Type=1
Class=CExpMethod
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_RADIO_V,button,1342308361
Control4=IDC_RADIO_H,button,1342308361

[CLS:CExpMethod]
Type=0
HeaderFile=ExpMethod.h
ImplementationFile=ExpMethod.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDM_LAYER_LAND



