#pragma once
#define  PARTICLE_NUMBER  15000   
#define  SNOW_SYSTEM_LENGTH_X	20000  
#define  SNOW_SYSTEM_WIDTH_Z		20000   
#define  SNOW_SYSTEM_HEIGHT_Y     20000   


struct POINTVERTEX
{
	float x, y, z;    
	float u, v;		  
};
#define D3DFVF_POINTVERTEX (D3DFVF_XYZ|D3DFVF_TEX1)


struct  SNOWPARTICLE
{
	float x, y, z;     
	float RotationY;        
	float RotationX;       
	float FallSpeed;      
	float RotationSpeed;      
	int   TextureIndex;    
};


class SnowParticleClass
{
private:
	LPDIRECT3DDEVICE9				m_pd3dDevice;			
	SNOWPARTICLE						m_Snows[PARTICLE_NUMBER];    
	LPDIRECT3DVERTEXBUFFER9   m_pVertexBuffer;     
	LPDIRECT3DTEXTURE9			m_pTexture[6];  

public:
	SnowParticleClass(LPDIRECT3DDEVICE9 pd3dDevice);   
	~SnowParticleClass();					
	HRESULT InitSnowParticle();       
	HRESULT UpdateSnowParticle(float fElapsedTime);    
	HRESULT RenderSnowParticle();   
};

