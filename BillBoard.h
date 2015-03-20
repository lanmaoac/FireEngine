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
	LPDIRECT3DDEVICE9				m_pd3dDevice;			
	LPDIRECT3DVERTEXBUFFER9	m_pVertexBuffer;		
	LPDIRECT3DTEXTURE9			m_pTexture;			
	float										m_Length;	
	ID3DXEffect* BillEffect = 0;

public:
	BillBoardClass(LPDIRECT3DDEVICE9  pDevice);		
	virtual ~BillBoardClass(void);								

public:
	BOOL	InitBillBoard(float Length); 
	BOOL	LoadBillBoardTextureFromFile(wchar_t *pFrontTextureFile);
	VOID	RenderBillBoard(D3DXVECTOR3 vDir, D3DXMATRIX *matView);
};
