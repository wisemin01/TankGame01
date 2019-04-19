#pragma once
#include "CObject.h"

class CEnemy;
class CEnemyAdmin :
	public CGameObject
{
private:
	float m_fDelay;
	float m_fSpawnTime;

	CGameObject* m_pTarget;
public:
	CEnemyAdmin();
	virtual ~CEnemyAdmin();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Destroy() override;

	void Setup(float delay);
};

