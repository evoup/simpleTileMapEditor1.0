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
extern struct tparam{//���������ݲ����Ľṹ
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
extern struct tiles{//TILE����
	//##ModelId=4A1E84730379
int tileiid;//�ڲ����
	//##ModelId=4A1E84730384
int tile_width;
	//##ModelId=4A1E84730385
int tile_height;
//char imagesrc[300];
	//##ModelId=4A1E84730386
char *imagesrc;//����Ч�ʵͣ����ǲ��õ���ת�������С���⡣
	//##ModelId=4A1E84730388
RECT tilerect;//���ڵľ���λ��
	//##ModelId=4A1E8473038F
tiles *next;
}*tiles_struct;
#endif

//��������TileSetѡ������
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
