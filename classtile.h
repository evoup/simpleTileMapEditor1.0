// classtile.h: interface for the classtile class.
//
//////////////////////////////////////////////////////////////////////
#if !defined(AFX_CLASSTILE_H__F5A23E80_83E6_405C_BB76_D7535BFA498F__INCLUDED_)
#define AFX_CLASSTILE_H__F5A23E80_83E6_405C_BB76_D7535BFA498F__INCLUDED_

#if _MSC_VER > 1000

#endif // _MSC_VER > 1000

#ifndef TILE_TPARAM
#define TILE_TPARAM

//##ModelId=4A1E8473036B
extern struct tparam{//创建链表传递参数的结构
	//##ModelId=4A1E8473036D
	int bitmap_width;
	//##ModelId=4A1E84730374
	int tile_width;
	//##ModelId=4A1E84730375
	int tile_height;
	//##ModelId=4A1E84730376
	char *imagesrc;
} *tparam_struct;
#endif

#ifndef TILES_STRUCT
#define TILES_STRUCT
//##ModelId=4A1E84730377
extern struct tiles{//TILE链表
	//##ModelId=4A1E84730379
int tileiid;//内部标记
	//##ModelId=4A1E84730384
int tile_width;
	//##ModelId=4A1E84730385
int tile_height;
//char imagesrc[300];
	//##ModelId=4A1E84730386
char *imagesrc;//这样效率低，但是不用担心转换数组大小问题。
	//##ModelId=4A1E84730388
RECT tilerect;//所在的矩形位置
	//##ModelId=4A1E8473038F
tiles *next;
}*tiles_struct;
#endif

//用来创建TileSet选择链表
//##ModelId=4A1E84730393
class classtile  
{
public:
	//##ModelId=4A1E84730394
	struct tiles * gettile(struct tiles * s,int tileiid);
	//##ModelId=4A1E847303A5
	struct tiles * CreateTilelist(tparam * t);
	//##ModelId=4A1E847303A7
	bool GetTileInfo();
	//##ModelId=4A1E847303A8
	bool CheckOK();
	//##ModelId=4A1E847303A9
	classtile();
	//##ModelId=4A1E847303AA
	virtual ~classtile();

};

#endif // !defined(AFX_CLASSTILE_H__F5A23E80_83E6_405C_BB76_D7535BFA498F__INCLUDED_)
