#include "WaterClass.h"
D3DCOLOR BLUE = D3DCOLOR_XRGB(0, 0, 255);

WaterClass::WaterClass(IDirect3DDevice9* pd3dDevice)
{
	m_pd3dDevice = pd3dDevice;
	m_pIndexBuffer = NULL;
	m_pVertexBuffer = NULL;
	m_nCellsPerRow = 0;
	m_nCellsPerCol = 0;
	m_nVertsPerRow = 0;
	m_nVertsPerCol = 0;
	m_nNumVertices = 0;
	m_fWaterWidth = 0.0f;
	m_fWaterDepth = 0.0f;
	m_fCellSpacing = 0.0f;
	m_fHeightScale = 0.0f;
}

BOOL WaterClass::InitWater(INT nRows, INT nCols, FLOAT fSpace, FLOAT fScale)
{
	m_nCellsPerRow = nRows;  
	m_nCellsPerCol = nCols;  
	m_fCellSpacing = fSpace;    
	m_fHeightScale = fScale; 
	m_fWaterWidth = nRows * fSpace; 
	m_fWaterDepth = nCols * fSpace;  
	m_nVertsPerRow = m_nCellsPerCol + 1; 
	m_nVertsPerCol = m_nCellsPerRow + 1;
	m_nNumVertices = m_nVertsPerRow * m_nVertsPerCol;  

	
	if (FAILED(m_pd3dDevice->CreateVertexBuffer(m_nNumVertices * sizeof(WATERVERTEX),
		D3DUSAGE_WRITEONLY, WATERVERTEX::FVF, D3DPOOL_MANAGED, &m_pVertexBuffer, 0)))
		return FALSE;

	WATERVERTEX *pVertices = NULL;
	m_pVertexBuffer->Lock(0, 0, (void**)&pVertices, 0);

	FLOAT fStartX = -m_fWaterWidth / 2.0f, fEndX = m_fWaterWidth / 2.0f;       
	FLOAT fStartZ = m_fWaterDepth / 2.0f, fEndZ = -m_fWaterDepth / 2.0f;   

	int nIndex = 0, i = 0, j = 0;
	for (float z = fStartZ; z >= fEndZ; z -= m_fCellSpacing, i++)      
	{
		j = 0;
		for (float x = fStartX; x <= fEndX; x += m_fCellSpacing, j++)  
		{
			nIndex = i * m_nCellsPerRow + j;      
			pVertices[nIndex] = WATERVERTEX(x, 400.0f, z, BLUE);
			nIndex++;                                        
		}
	}

	m_pVertexBuffer->Unlock();


	if (FAILED(m_pd3dDevice->CreateIndexBuffer(m_nNumVertices * 6 * sizeof(WORD),
		D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_pIndexBuffer, 0)))
		return FALSE;

	WORD* pIndices = NULL;
	m_pIndexBuffer->Lock(0, 0, (void**)&pIndices, 0);
	
	nIndex = 0;
	for (int row = 0; row < m_nCellsPerRow - 1; row++)   
	{
		for (int col = 0; col < m_nCellsPerCol - 1; col++)  
		{
			
			pIndices[nIndex] = row * m_nCellsPerRow + col;         
			pIndices[nIndex + 1] = row * m_nCellsPerRow + col + 1;  
			pIndices[nIndex + 2] = (row + 1) * m_nCellsPerRow + col;   
		
			pIndices[nIndex + 3] = (row + 1) * m_nCellsPerRow + col;       
			pIndices[nIndex + 4] = row * m_nCellsPerRow + col + 1;      
			pIndices[nIndex + 5] = (row + 1) * m_nCellsPerRow + col + 1;
		
			nIndex += 6;  
		}
	}

	m_pIndexBuffer->Unlock();

	return TRUE;
}

BOOL WaterClass::RenderWater(D3DXMATRIX *pMatWorld, BOOL bRenderFrame)
{

	m_pd3dDevice->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(WATERVERTEX));
	m_pd3dDevice->SetFVF(WATERVERTEX::FVF);
	m_pd3dDevice->SetIndices(m_pIndexBuffer);

	m_pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);   
	m_pd3dDevice->SetTransform(D3DTS_WORLD, pMatWorld); 
	m_pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0,
		m_nNumVertices, 0, m_nNumVertices * 2);    

	m_pd3dDevice->SetRenderState(D3DRS_LIGHTING, TRUE);  


	if (bRenderFrame)  
	{
		m_pd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME); 
		m_pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0,
			m_nNumVertices, 0, m_nNumVertices * 2); 
		m_pd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);   
	}
	return TRUE;
}
WaterClass::~WaterClass(void)
{
	/*
	SAFE_RELEASE(m_pTexture);
	SAFE_RELEASE(m_pIndexBuffer);
	SAFE_RELEASE(m_pVertexBuffer);
	*/
}