#pragma once

#include <conio.h>



#include <windows.h>
#include <string.h>
#include<atlstr.h>  
#include <d3d9.h>
#include <d3dx9.h>
#include <tchar.h>
#include <time.h> 
struct BILLBOARDVERTEX
{
	float	x, y, z;
	float	u, v;
};
#define D3DFVF_BILLBOARD D3DFVF_XYZ|D3DFVF_TEX1


class BillBoardClass
{
private:
	LPDIRECT3DDEVICE9				m_pd3dDevice;			//D3D设备对象
	LPDIRECT3DVERTEXBUFFER9	m_pVertexBuffer;		//顶点缓存对象
	LPDIRECT3DTEXTURE9			m_pTexture;			//5个纹理接口对象
	float										m_Length;					//天空盒边长

public:
	BillBoardClass(LPDIRECT3DDEVICE9  pDevice);		//构造函数
	virtual ~BillBoardClass(void);								//析构函数

public:
	BOOL	InitBillBoard(float Length); 
	BOOL	LoadBillBoardTextureFromFile(wchar_t *pFrontTextureFile);
	VOID	RenderBillBoard(D3DXVECTOR3 vDir, D3DXMATRIX *matView);
};
