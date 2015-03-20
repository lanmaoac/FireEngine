
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


	HRESULT hr1 = 0;
	ID3DXBuffer* errorBuffer1 = 0;
	hr1 = D3DXCreateEffectFromFile(
		m_pd3dDevice,           // associated device
		L"billboard.txt", // effect filename
		0,                // no preprocessor definitions
		0,                // no ID3DXInclude interface
		D3DXSHADER_USE_LEGACY_D3DX9_31_DLL,
		0,                // don't share parameters
		&BillEffect,      // return effect
		&errorBuffer1);    // return error messages

	// output any error messages
	if (errorBuffer1)
	{
		MessageBox(0, CString((char *)errorBuffer1->GetBufferPointer()), 0, 0);
	}

	if (FAILED(hr1))
	{
		MessageBox(0, CString((char *)errorBuffer1->GetBufferPointer()), 0, 0);
		//MessageBox(0, L"D3DXCreateEffectFromFile() - FAILED", 0, 0);
	}

	return TRUE;
}


BOOL BillBoardClass::LoadBillBoardTextureFromFile(
	wchar_t *pFrontTextureFile)
{
	D3DXHANDLE BillTexHandle;
	D3DXCreateTextureFromFile(m_pd3dDevice, pFrontTextureFile, &m_pTexture);
	BillTexHandle = BillEffect->GetParameterByName(0, "ShaderTexture");
	BillEffect->SetTexture(BillTexHandle, m_pTexture);
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

	D3DXMatrixTranslation(&matWorld, 0.0f, 10500.0f, 5000.0f);

	matWorld = matRotion*matWorld * (*matView) * matProj;
	
	BillEffect->SetTechnique("Normal");
	UINT numPasses = 0;
	BillEffect->Begin(&numPasses, 0);

	for (int i = 0; i < numPasses; i++)
	{
		BillEffect->BeginPass(i);
		BillEffect->SetMatrix("WorldViewProjMatrix", &matWorld);
		m_pd3dDevice->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(BILLBOARDVERTEX));
		m_pd3dDevice->SetFVF(D3DFVF_BILLBOARD);
		m_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
		BillEffect->EndPass();
	}
	BillEffect->End();
}

BillBoardClass::~BillBoardClass(void)
{

}