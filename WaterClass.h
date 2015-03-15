#include <d3d9.h>
#include <d3dx9.h>
#include <vector>
#include <fstream>

class WaterClass
{
private:
	LPDIRECT3DDEVICE9               m_pd3dDevice;        
	LPDIRECT3DTEXTURE9          m_pTexture;           
	LPDIRECT3DINDEXBUFFER9  m_pIndexBuffer;         
	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer;       

	int                             m_nCellsPerRow;    
	int                             m_nCellsPerCol;       
	int                             m_nVertsPerRow;    
	int                             m_nVertsPerCol;        
	int                             m_nNumVertices;     
	FLOAT                       m_fWaterWidth;     
	FLOAT                       m_fWaterDepth;     
	FLOAT                       m_fCellSpacing;        
	FLOAT                       m_fHeightScale;        

	struct WATERVERTEX
	{
		FLOAT _x, _y, _z;
		D3DCOLOR _c;
		WATERVERTEX(FLOAT x, FLOAT y, FLOAT z, D3DCOLOR c)
			:_x(x), _y(y), _z(z), _c(c) {}
		static const DWORD FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;
	};

public:
	WaterClass(IDirect3DDevice9 *pd3dDevice); 
	virtual ~WaterClass(void);       

public:
	BOOL InitWater(INT nRows, INT nCols, FLOAT fSpace, FLOAT fScale); 
	BOOL RenderWater(D3DXMATRIX *pMatWorld, BOOL bDrawFrame = FALSE); 
	void WaterUpdate();
	void Disturb();
};
