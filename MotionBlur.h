D3DXHANDLE WorldViewProjHandle = 0;

D3DXHANDLE TexHandle0 = 0;
D3DXHANDLE TexHandle1 = 0;
D3DXHANDLE TexHandle2 = 0;

ID3DXEffect* MBffect = 0;

IDirect3DTexture9*           TmpScene = NULL;
IDirect3DTexture9*           NowScene = NULL;
IDirect3DTexture9*          LastScene = NULL;

D3DXMATRIX ProjMatrix;

LPDIRECT3DDEVICE9					Device = NULL;

void  DOFInit(LPDIRECT3DDEVICE9	Device)
{
	HRESULT hr = 0;
	ID3DXBuffer* errorBuffer = 0;
	hr = D3DXCreateEffectFromFile(
		Device,           // associated device
		L"MotionBlureffect.txt", // effect filename
		0,                // no preprocessor definitions
		0,                // no ID3DXInclude interface
		D3DXSHADER_USE_LEGACY_D3DX9_31_DLL,
		0,                // don't share parameters
		&MBEffect,      // return effect
		&errorBuffer);    // return error messages

	// output any error messages
	if (errorBuffer)
	{
		MessageBox(0, CString((char *)errorBuffer->GetBufferPointer()), 0, 0);
	}

	if (FAILED(hr))
	{
		MessageBox(0, CString((char *)errorBuffer->GetBufferPointer()), 0, 0);
		//MessageBox(0, L"D3DXCreateEffectFromFile() - FAILED", 0, 0);
	}

	D3DXMatrixPerspectiveFovLH(
		&ProjMatrix, D3DX_PI * 0.25f, // 45 - degree
		(float)WINDOW_WIDTH / (float)WINDOW_HEIGHT,
		1.0f, 500000.0f);

	IDirect3DTexture9* tex = 0;
	D3DXCreateTextureFromFile(Device, L"terrainstone.jpg", &tex);

	Device->CreateTexture(WINDOW_WIDTH, WINDOW_HEIGHT,
		1, D3DUSAGE_RENDERTARGET | D3DUSAGE_AUTOGENMIPMAP, D3DFMT_X8R8G8B8, D3DPOOL_DEFAULT, &TmpScene, NULL);

	Device->CreateTexture(WINDOW_WIDTH, WINDOW_HEIGHT,
		1, D3DUSAGE_RENDERTARGET | D3DUSAGE_AUTOGENMIPMAP, D3DFMT_X8R8G8B8, D3DPOOL_DEFAULT, &NowScene, NULL);

	Device->CreateTexture(WINDOW_WIDTH, WINDOW_HEIGHT,
		1, D3DUSAGE_RENDERTARGET | D3DUSAGE_AUTOGENMIPMAP, D3DFMT_X8R8G8B8, D3DPOOL_DEFAULT, &LastScene, NULL);

	TexHandle0 = ToonEffect->GetParameterByName(0, "Texture0");
	TexHandle1 = ToonEffect->GetParameterByName(0, "Texture1");
	TexHandle2 = ToonEffect->GetParameterByName(0, "Texture2");

	WorldViewProjHandle = ToonEffect->GetParameterByName(0, "WorldViewProjMatrix");

	MBEffect->SetTexture(TexHandle0, tex);
	MBEffect->SetTexture(TexHandle1, NowScene);
	MBEffect->SetTexture(TexHandle2, LastScene);
	
}
void EffectDisplay()
{
	if (Device)
	{
		Device->BeginScene();

		D3DXMATRIX matView;
		g_pCamera->CalculateViewMatrix(&matView);
		D3DXMatrixTranslation(&g_matWorld, 0.0f, 0.0f, 0.0f);

		SetRenderTarget(0, NowScene);
		Device->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
		Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0, 1.0f, 0);
		ToonEffect->SetTechnique("Copy2Tmp");
		UINT numPasses = 0;
		ToonEffect->Begin(&numPasses, 0);
		for (int i = 0; i < numPasses; i++)
		{
			ToonEffect->BeginPass(i);
			D3DXMATRIX now = matView *  g_matWorld * ProjMatrix;
			ToonEffect->SetMatrix("WorldViewProjMatrix", &now);
			g_pTerrain->RenderTerrain(&g_matWorld, false);
			ToonEffect->EndPass();
		}
		ToonEffect->End();

		struct PlaneVertex {
			float x, y, z, w;
			float u, v;
		};
		PlaneVertex axPlaneVertices[] =
		{
			{ 0.0f, 0.0f, 0.5f, 1.0f, 0.0f + 0.5f / WINDOW_WIDTH, 0.0f + 0.5f / WINDOW_HEIGHT },
			{ WINDOW_WIDTH, 0.0f, 0.5f, 1.0f, 1.0f + 0.5f / WINDOW_WIDTH, 0.0f + 0.5f / WINDOW_HEIGHT },
			{ WINDOW_WIDTH, WINDOW_HEIGHT, 0.5f, 1.0f, 1.0f + 0.5f / WINDOW_WIDTH, 1.0f + 0.5f / WINDOW_HEIGHT },
			{ 0.0f, WINDOW_HEIGHT, 0.5f, 1.0f, 0.0f + 0.5f / WINDOW_WIDTH, 1.0f + 0.5f / WINDOW_HEIGHT }
		};

		ToonEffect->SetTexture("Texture1", NowScene);
		ToonEffect->SetTexture("Texture2", LastScene);
		//SetRenderTarget(0, NULL);

		IDirect3DSurface9* pd3dBackBufferSurface;

		Device->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &pd3dBackBufferSurface);
		Device->SetRenderTarget(0, pd3dBackBufferSurface);
		Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0, 1.0f, 0);
		ToonEffect->SetTechnique("Copy2FrameBuffer");
		numPasses = 0;
		ToonEffect->Begin(&numPasses, 0);
		for (int i = 0; i < numPasses; i++)
		{
			ToonEffect->BeginPass(i);
			Device->SetFVF(D3DFVF_XYZRHW | D3DFVF_TEX1);

			Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, axPlaneVertices, sizeof(PlaneVertex));
			ToonEffect->EndPass();
		}
		ToonEffect->End();
		Device->EndScene();

		SetRenderTarget(0, LastScene);
		Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0, 1.0f, 0);
		ToonEffect->SetTechnique("Copy2FrameBuffer");
		numPasses = 0;
		ToonEffect->Begin(&numPasses, 0);
		for (int i = 0; i < numPasses; i++)
		{
			ToonEffect->BeginPass(i);
			Device->SetFVF(D3DFVF_XYZRHW | D3DFVF_TEX1);
			Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, axPlaneVertices, sizeof(PlaneVertex));
			ToonEffect->EndPass();
		}
		ToonEffect->End();
		Device->EndScene();


		Device->Present(0, 0, 0, 0);
	}
}