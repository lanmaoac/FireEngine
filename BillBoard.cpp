
#include "d3dx9.h"
#include "BillBoard.h"
BillBoardClass::BillBoardClass(LPDIRECT3DDEVICE9  pDevice)
{
	m_pVertexBuffer = NULL;
	m_pd3dDevice = pDevice;
		m_pTexture = NULL;
	m_Length = 0.0f;
}


BOOL BillBoardClass::InitBillBoard(float Length)
{
	m_Length = Length;

	
	m_pd3dDevice->CreateVertexBuffer(4 * sizeof(BILLBOARDVERTEX), 0,
		D3DFVF_BILLBOARD, D3DPOOL_MANAGED, &m_pVertexBuffer, 0);

	BILLBOARDVERTEX vertices[] =
	{
		
		{ -m_Length / 2, 0.0f, 0.0f,        0.0f, 1.0f, },
		{ -m_Length / 2, m_Length ,0.0f, 0.0f, 0.0f, },
		{ m_Length  / 2, 0.0f, 0.0f,         1.0f, 1.0f, },
		{ m_Length  / 2, m_Length ,0.0f,  1.0f, 0.0f, },

	};
	void* pVertices;
	m_pVertexBuffer->Lock(0, 0, (void**)&pVertices, 0);
	memcpy(pVertices, vertices, sizeof(vertices));
	m_pVertexBuffer->Unlock();
	return TRUE;
}


BOOL BillBoardClass::LoadBillBoardTextureFromFile(
	wchar_t *pFrontTextureFile)
{
	D3DXCreateTextureFromFile(m_pd3dDevice, pFrontTextureFile, &m_pTexture);
	return TRUE;
}


void BillBoardClass::RenderBillBoard(D3DXVECTOR3 vDir, D3DXMATRIX *matView)
{
	
	D3DXMATRIX matRotion,matWorld,matProj;
	D3DXMatrixPerspectiveFovLH(
		&matProj, D3DX_PI * 0.25f, 
		(float)932 / (float)600,
		1.0f, 30000.0f);
	D3DXVECTOR3 now = vDir;
	if (now.x > 0.0f)

		D3DXMatrixRotationY(&matRotion, -atanf(vDir.z / vDir.x) + D3DX_PI*0.5);

	else

		D3DXMatrixRotationY(&matRotion, -atanf(vDir.z / vDir.x) - D3DX_PI*0.5);

	D3DXMatrixTranslation(&matWorld, 0.0f, 0.0f, 0.0f);

	matWorld = matRotion*matWorld;
	m_pd3dDevice->SetTransform(D3DTS_WORLD, &matWorld);
	m_pd3dDevice->SetTransform(D3DTS_VIEW, matView);
	m_pd3dDevice->SetTransform(D3DTS_PROJECTION, &matProj);
	m_pd3dDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
	m_pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);  

	m_pd3dDevice->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(BILLBOARDVERTEX));     
	m_pd3dDevice->SetFVF(D3DFVF_BILLBOARD);  

    m_pd3dDevice->SetTexture(0, m_pTexture);
	m_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);


}

BillBoardClass::~BillBoardClass(void)
{

}