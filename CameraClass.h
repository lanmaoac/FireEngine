#pragma once

#include <d3d9.h>
#include <d3dx9.h>

class CameraClass
{
private:
	
	D3DXVECTOR3				m_vRightVector;       
	D3DXVECTOR3				m_vUpVector;          
	D3DXVECTOR3				m_vLookVector;        
	D3DXVECTOR3				m_vCameraPosition;        
	D3DXVECTOR3				m_vTargetPosition;        
	D3DXMATRIX				m_matView;         
	D3DXMATRIX				m_matProj;          
	LPDIRECT3DDEVICE9		m_pd3dDevice;  

public:
	
	VOID CalculateViewMatrix(D3DXMATRIX *pMatrix);    

	VOID GetProjMatrix(D3DXMATRIX *pMatrix)  { *pMatrix = m_matProj; }  
	VOID GetCameraPosition(D3DXVECTOR3 *pVector)  { *pVector = m_vCameraPosition; } 
	VOID GetLookVector(D3DXVECTOR3 *pVector) { *pVector = m_vLookVector; } 

	VOID SetTargetPosition(D3DXVECTOR3 *pLookat = NULL);  
	VOID SetCameraPosition(D3DXVECTOR3 *pVector = NULL); 
	VOID SetViewMatrix(D3DXMATRIX *pMatrix = NULL); 
	VOID SetProjMatrix(D3DXMATRIX *pMatrix = NULL);  

public:
	
	VOID MoveAlongRightVec(FLOAT fUnits);   
	VOID MoveAlongUpVec(FLOAT fUnits);     
	VOID MoveAlongLookVec(FLOAT fUnits);   


	VOID RotationRightVec(FLOAT fAngle);    
	VOID RotationUpVec(FLOAT fAngle);       
	VOID RotationLookVec(FLOAT fAngle);   

public:
	
	CameraClass(IDirect3DDevice9 *pd3dDevice);  
	virtual ~CameraClass(void);  

};
