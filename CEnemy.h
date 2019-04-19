#pragma once
#include "CObject.h"

enum ENEMY_TYPE
{
	NORMAL,
	DROP_MINE,
	ENEMY_END
};

class CLifeSystem;
class CEnemy :
	public CGameObject
{
private:
	CGameObject * m_pTarget = nullptr;
	CLifeSystem* m_pLife = nullptr;

	float m_fSpeed;

	ENEMY_TYPE m_eType;
	STATE m_eState;
	CStateTexture m_StateTex;


	float m_fXIndex;
	float m_fYIndex;
public:
	CEnemy();
	virtual ~CEnemy();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Destroy() override;

	void MoveUpdate();
	void AttackUpdate();

	void Setup(Vector3 position, float yRange);

	void SetupWithDropMineEnemy(Vector3 position, float yRange);
	void SetupNormalEnemy(Vector3 position, float yRange);

	void SetTarget(CGameObject* target) { m_pTarget = target; }

	virtual void Kill() override;
};

