// common.h: interface for the Ccommon class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMMON_H__A2C58883_D2DC_4434_B3E0_FF8701B79287__INCLUDED_)


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//##ModelId=4A1E84730357
class Ccommon  : public CWnd
{
public:
	//##ModelId=4A1E84730359
	bool Delay(int time);
	//##ModelId=4A1E84730364
	Ccommon();
	//##ModelId=4A1E84730365
	virtual ~Ccommon();
	//##ModelId=4A1E84730367
	getmaprect(UINT x,UINT y);
	//##ModelId=4A1E8473036A
	tile2vector();
};

#endif // !defined(AFX_COMMON_H__A2C58883_D2DC_4434_B3E0_FF8701B79287__INCLUDED_)
