#include "DXUT.h"
#include "CInputManager.h"


CInputManager::CInputManager()
{
	memset(m_bCurKey, 0, sizeof(m_bCurKey));
	memset(m_bOldKey, 0, sizeof(m_bOldKey));
}


CInputManager::~CInputManager()
{
}

void CInputManager::Update()
{
	for (int i = 0; i < 256; i++)
	{
		m_bOldKey[i] = m_bCurKey[i];
		m_bCurKey[i] = (bool)GetAsyncKeyState(i);
	}
	
	GetCursorPos(&m_ptMouse);
	ScreenToClient(DXUTGetHWND(), &m_ptMouse);
}

bool CInputManager::GetKeyDown(int key_type)
{
	return !m_bOldKey[key_type] && m_bCurKey[key_type];
}

bool CInputManager::GetKeyUp(int key_type)
{
	return m_bOldKey[key_type] && !m_bCurKey[key_type];
}

bool CInputManager::GetKeyPress(int key_type)
{
	return m_bOldKey[key_type] && m_bCurKey[key_type];
}

Vector3 CInputManager::GetMousePos()
{
	return Vector3(m_ptMouse.x, m_ptMouse.y, 0);
}
