#pragma once
#include "CObject.h"


class CCheckPoint :
	public CGameObject
{
private:
	bool m_bIsPassed = false;
public:
	CCheckPoint();
	virtual ~CCheckPoint();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Destroy() override;

	bool IsPassed() { return m_bIsPassed; }
	void Pass();
	void Place(Vector3 position);
};

