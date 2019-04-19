#pragma once
#include "CSingleton.h"
class CInputManager :
	public CSingleton<CInputManager>
{
private:
	bool m_bOldKey[256];
	bool m_bCurKey[256];

	POINT m_ptMouse;
public:
	CInputManager();
	virtual ~CInputManager();

	void Update();

	bool GetKeyDown(int key_type);
	bool GetKeyUp(int key_type);
	bool GetKeyPress(int key_type);

	Vector3 GetMousePos();
};

#define INPUT (*CInputManager::Instance())