#include "WaterClass.h"
D3DCOLOR BLUE = D3DCOLOR_XRGB(0, 0, 255);

WaterClass::WaterClass(IDirect3DDevice9* pd3dDevice)
{
	//给各个成员变量赋初值
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
	m_nCellsPerRow = nRows;  //每行的单元格数目
	m_nCellsPerCol = nCols;  //每列的单元格数目
	m_fCellSpacing = fSpace;    //单元格间的间距j
	m_fHeightScale = fScale; //高度缩放系数
	m_fWaterWidth = nRows * fSpace;  //地形的宽度
	m_fWaterDepth = nCols * fSpace;  //地形的深度
	m_nVertsPerRow = m_nCellsPerCol + 1;  //每行的顶点数
	m_nVertsPerCol = m_nCellsPerRow + 1; //每列的顶点数
	m_nNumVertices = m_nVertsPerRow * m_nVertsPerCol;  //顶点总数

	
	if (FAILED(m_pd3dDevice->CreateVertexBuffer(m_nNumVertices * sizeof(WATERVERTEX),
		D3DUSAGE_WRITEONLY, WATERVERTEX::FVF, D3DPOOL_MANAGED, &m_pVertexBuffer, 0)))
		return FALSE;

	WATERVERTEX *pVertices = NULL;
	m_pVertexBuffer->Lock(0, 0, (void**)&pVertices, 0);

	FLOAT fStartX = -m_fWaterWidth / 2.0f, fEndX = m_fWaterWidth / 2.0f;        //指定起始点和结束点的X坐标值
	FLOAT fStartZ = m_fWaterDepth / 2.0f, fEndZ = -m_fWaterDepth / 2.0f;    //指定起始点和结束点的Z坐标值

	int nIndex = 0, i = 0, j = 0;
	for (float z = fStartZ; z >= fEndZ; z -= m_fCellSpacing, i++)       //Z坐标方向上起始顶点到结束顶点行间的遍历
	{
		j = 0;
		for (float x = fStartX; x <= fEndX; x += m_fCellSpacing, j++)   //X坐标方向上起始顶点到结束顶点行间的遍历
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
			
			pIndices[nIndex] = row * m_nCellsPerRow + col;          //顶点A
			pIndices[nIndex + 1] = row * m_nCellsPerRow + col + 1;  //顶点B
			pIndices[nIndex + 2] = (row + 1) * m_nCellsPerRow + col;    //顶点C
		
			pIndices[nIndex + 3] = (row + 1) * m_nCellsPerRow + col;        //顶点C
			pIndices[nIndex + 4] = row * m_nCellsPerRow + col + 1;      //顶点B
			pIndices[nIndex + 5] = (row + 1) * m_nCellsPerRow + col + 1;//顶点D
		
			nIndex += 6;  
		}
	}

	m_pIndexBuffer->Unlock();

	return TRUE;
}

BOOL WaterClass::RenderWater(D3DXMATRIX *pMatWorld, BOOL bRenderFrame)
{

	m_pd3dDevice->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(WATERVERTEX));
	m_pd3dDevice->SetFVF(WATERVERTEX::FVF);//指定我们使用的灵活顶点格式的宏名称
	m_pd3dDevice->SetIndices(m_pIndexBuffer);//设置索引缓存  

	m_pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);    //关闭光照
	m_pd3dDevice->SetTransform(D3DTS_WORLD, pMatWorld); //设置世界矩阵
	m_pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0,
		m_nNumVertices, 0, m_nNumVertices * 2);     //绘制顶点

	m_pd3dDevice->SetRenderState(D3DRS_LIGHTING, TRUE);  //打开光照


	if (bRenderFrame)  //如果要渲染出线框的话
	{
		m_pd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME); //把填充模式设为线框填充
		m_pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0,
			m_nNumVertices, 0, m_nNumVertices * 2); //绘制顶点  
		m_pd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);    //把填充模式调回实体填充
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