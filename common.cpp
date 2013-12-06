// common.cpp: implementation of the Ccommon class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SplitWndDemo.h"
#include "common.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//##ModelId=4A1E84730364
Ccommon::Ccommon()
{
	
}

//##ModelId=4A1E84730365
Ccommon::~Ccommon()
{

}

//##ModelId=4A1E84730367
Ccommon::getmaprect(UINT x,UINT y){//根据光标位置计算对应RECT结构
	CString cx,cy;
	cx.Format("%d",x);
	cy.Format("%d",y);
	::MessageBox(this->m_hWnd,cx,"",NULL);
	::MessageBox(this->m_hWnd,cy,"",NULL);
}

//##ModelId=4A1E8473036A
Ccommon::tile2vector(){//把MAP指定的TILE数量和大小，二维化到vector里

}

//延时函数，输入参数：毫秒
//##ModelId=4A1E84730359
bool Ccommon::Delay(int time)
{
	DWORD dwStart = GetTickCount();
	DWORD dwEnd = dwStart;
	do
	{  
		MSG  msg;  
		GetMessage(&msg,NULL,0,0);  
		TranslateMessage(&msg); 
		DispatchMessage(&msg); 
		dwEnd = GetTickCount(); 
	} while((dwEnd - dwStart)  <=  time); 
	return 1;
}
