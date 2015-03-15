#include <d3d9.h>
#include <d3dx9.h>
#include <vector>
#include <fstream>

class WaterClass
{
private:
	LPDIRECT3DDEVICE9               m_pd3dDevice;           //D3D设备
	LPDIRECT3DTEXTURE9          m_pTexture;             //纹理
	LPDIRECT3DINDEXBUFFER9  m_pIndexBuffer;         //顶点缓存
	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer;        //索引缓存

	int                             m_nCellsPerRow;     // 每行的单元格数
	int                             m_nCellsPerCol;         // 每列的单元格数
	int                             m_nVertsPerRow;     // 每行的顶点数
	int                             m_nVertsPerCol;         // 每列的顶点数
	int                             m_nNumVertices;     // 顶点总数
	FLOAT                       m_fWaterWidth;      // 地形的宽度
	FLOAT                       m_fWaterDepth;      // 地形的深度
	FLOAT                       m_fCellSpacing;         // 单元格的间距
	FLOAT                       m_fHeightScale;         // 高度缩放系数

	struct WATERVERTEX
	{
		FLOAT _x, _y, _z;
		D3DCOLOR _c;
		WATERVERTEX(FLOAT x, FLOAT y, FLOAT z, D3DCOLOR c)
			:_x(x), _y(y), _z(z), _c(c) {}
		static const DWORD FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;
	};

public:
	WaterClass(IDirect3DDevice9 *pd3dDevice); //构造函数
	virtual ~WaterClass(void);        //析构函数

public:
	BOOL InitWater(INT nRows, INT nCols, FLOAT fSpace, FLOAT fScale); 
	BOOL RenderWater(D3DXMATRIX *pMatWorld, BOOL bDrawFrame = FALSE); 
	void WaterUpdate();
	void Disturb();
};
