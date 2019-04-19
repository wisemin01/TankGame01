#pragma once

class CGameObject;
class CComponent
{
protected:
	CGameObject * m_pObject = nullptr;

	bool m_bIsActive = true;
public:
	CComponent();
	virtual ~CComponent();

	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Destroy();

	void SetOwnerObject(CGameObject* owner) { m_pObject = owner; }
	CGameObject* GetGameObject() { return m_pObject; }

	bool GetActive() { return m_bIsActive; }
	void SetActive(bool value) { m_bIsActive = value; }
};

#define GO GetGameObject()