
#pragma once

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

class DInputClass
{
private:
	IDirectInput8					* m_pDirectInput;  
	IDirectInputDevice8		* m_KeyboardDevice; 
	char								m_keyBuffer[256];      

	IDirectInputDevice8		*m_MouseDevice;      
	DIMOUSESTATE				m_MouseState;			

public:
	HRESULT		Init(HWND hWnd, HINSTANCE hInstance, DWORD keyboardCoopFlags, DWORD mouseCoopFlags); 
	void				GetInput();   
	bool				IsKeyDown(int iKey);  

	bool				IsMouseButtonDown(int button);  
	float				MouseDX();  
	float				MouseDY();	
	float				MouseDZ();	


public:
	DInputClass(void);		//构造函数
	~DInputClass(void);	//析构函数
};
