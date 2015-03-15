#include <d3d9.h>
#include <d3dx9.h>
#include <vector>
#include <fstream>

class WaterClass
{
private:
	LPDIRECT3DDEVICE9               m_pd3dDevice;           //D3D�豸
	LPDIRECT3DTEXTURE9          m_pTexture;             //����
	LPDIRECT3DINDEXBUFFER9  m_pIndexBuffer;         //���㻺��
	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer;        //��������

	int                             m_nCellsPerRow;     // ÿ�еĵ�Ԫ����
	int                             m_nCellsPerCol;         // ÿ�еĵ�Ԫ����
	int                             m_nVertsPerRow;     // ÿ�еĶ�����
	int                             m_nVertsPerCol;         // ÿ�еĶ�����
	int                             m_nNumVertices;     // ��������
	FLOAT                       m_fWaterWidth;      // ���εĿ��
	FLOAT                       m_fWaterDepth;      // ���ε����
	FLOAT                       m_fCellSpacing;         // ��Ԫ��ļ��
	FLOAT                       m_fHeightScale;         // �߶�����ϵ��

	struct WATERVERTEX
	{
		FLOAT _x, _y, _z;
		D3DCOLOR _c;
		WATERVERTEX(FLOAT x, FLOAT y, FLOAT z, D3DCOLOR c)
			:_x(x), _y(y), _z(z), _c(c) {}
		static const DWORD FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;
	};

public:
	WaterClass(IDirect3DDevice9 *pd3dDevice); //���캯��
	virtual ~WaterClass(void);        //��������

public:
	BOOL InitWater(INT nRows, INT nCols, FLOAT fSpace, FLOAT fScale); 
	BOOL RenderWater(D3DXMATRIX *pMatWorld, BOOL bDrawFrame = FALSE); 
	void WaterUpdate();
	void Disturb();
};
