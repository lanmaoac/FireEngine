D3DXHANDLE WorldViewProjHandle = 0;

D3DXHANDLE TexHandle0 = 0;
D3DXHANDLE TexHandle1 = 0;
D3DXHANDLE TexHandle2 = 0;

ID3DXEffect* DOFffect = 0;

IDirect3DTexture9*           NormalScene = NULL;
IDirect3DTexture9*           BlurScene = NULL;

D3DXMATRIX ProjMatrix;
LPDIRECT3DDEVICE9					Device = NULL;

void  DOFInit(LPDIRECT3DDEVICE9	Device)
{
	HRESULT hr = 0;
	ID3DXBuffer* errorBuffer = 0;
	hr = D3DXCreateEffectFromFile(
		Device,          
		L"depthoffield.txt", 
		0,              
		0,                
		D3DXSHADER_USE_LEGACY_D3DX9_31_DLL,
		0,               
		&DOFEffect,      
		&errorBuffer);   

	if (errorBuffer)
	{
		MessageBox(0, CString((char *)errorBuffer->GetBufferPointer()), 0, 0);
	}

	if (FAILED(hr))
	{
		MessageBox(0, CString((char *)errorBuffer->GetBufferPointer()), 0, 0);
		
	}

	D3DXMatrixPerspectiveFovLH(
		&ProjMatrix, D3DX_PI * 0.25f, 
		(float)WINDOW_WIDTH / (float)WINDOW_HEIGHT,
		1.0f, 30000.0f);

	IDirect3DTexture9* tex = 0;
	D3DXCreateTextureFromFile(Device, L"terrainstone.jpg", &tex);

	Device->CreateTexture(WINDOW_WIDTH, WINDOW_HEIGHT,
		1, D3DUSAGE_RENDERTARGET | D3DUSAGE_AUTOGENMIPMAP, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &NormalScene, NULL);

	Device->CreateTexture(WINDOW_WIDTH, WINDOW_HEIGHT,
		1, D3DUSAGE_RENDERTARGET | D3DUSAGE_AUTOGENMIPMAP, D3DFMT_X8R8G8B8, D3DPOOL_DEFAULT, &BlurScene, NULL);


	TexHandle0 = ToonEffect->GetParameterByName(0, "ShaderTexture");
	TexHandle1 = ToonEffect->GetParameterByName(0, "SceneNormal");
	TexHandle2 = ToonEffect->GetParameterByName(0, "SceneBlur");

	WorldViewProjHandle = ToonEffect->GetParameterByName(0, "WorldViewProjMatrix");

	ToonEffect->SetTexture(TexHandle0, tex);
	ToonEffect->SetTexture(TexHandle1, NormalScene);
	ToonEffect->SetTexture(TexHandle2, BlurScene);
}
void EffectDisplay()
{
	if (Device)
	{
		Device->BeginScene();

		D3DXMATRIX matView;
		g_pCamera->CalculateViewMatrix(&matView);
		D3DXMatrixTranslation(&g_matWorld, 0.0f, 0.0f, 0.0f);

		SetRenderTarget(0, NormalScene);

		Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0, 1.0f, 0);

		//Device->SetRenderState(D3DRS_ZENABLE, D3DZB_USEW);

		ToonEffect->SetTechnique("SceenCopy");
		UINT numPasses = 0;
		ToonEffect->Begin(&numPasses, 0);
		for (int i = 0; i < numPasses; i++)
		{
			ToonEffect->BeginPass(i);
			D3DXMATRIX now = matView *  g_matWorld * ProjMatrix;
			ToonEffect->SetMatrix("WorldViewProjMatrix", &now);
			now = matView *  g_matWorld;
			ToonEffect->SetMatrix("WorldViewMatrix", &now);
			//here to render your Target
			
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

		SetRenderTarget(0, BlurScene);
		Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0, 1.0f, 0);
		ToonEffect->SetTechnique("SceenBlur");
		numPasses = 0;
		ToonEffect->Begin(&numPasses, 0);
		for (int i = 0; i < numPasses; i++)
		{
			ToonEffect->BeginPass(i);
			//Device->SetFVF(D3DFVF_XYZRHW | D3DFVF_TEX1);

			//Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, axPlaneVertices, sizeof(PlaneVertex));
			ToonEffect->EndPass();
		}
		ToonEffect->End();
		Device->EndScene();


		IDirect3DSurface9* pd3dBackBufferSurface;

		Device->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &pd3dBackBufferSurface);
		Device->SetRenderTarget(0, pd3dBackBufferSurface);


		ToonEffect->SetTexture("SceneNormal", NormalScene);
		ToonEffect->SetTexture("SceneBlur", BlurScene);


		Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0, 1.0f, 0);
		ToonEffect->SetTechnique("Final");
		numPasses = 0;
		ToonEffect->Begin(&numPasses, 0);
		for (int i = 0; i < numPasses; i++)
		{
			ToonEffect->BeginPass(i);
			//here is your render target
			///Device->SetFVF(D3DFVF_XYZRHW | D3DFVF_TEX1);
			///Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, axPlaneVertices, sizeof(PlaneVertex
			//
			ToonEffect->EndPass();
		}
		ToonEffect->End();
		Device->EndScene();


		Device->Present(0, 0, 0, 0);
	}
}