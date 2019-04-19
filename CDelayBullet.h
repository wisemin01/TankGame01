#pragma once
#include "CObject.h"
class CDelayBullet :
	public CGameObject
{
private:
	Vector3 m_vDirection;

	float m_fSpeed;
	float m_fDamage;
	float m_fEndTime;
public:
	CDelayBullet();
	virtual ~CDelayBullet();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Destroy() override;

	void Fire(Vector3 position, Vector3 direction, ResourceID rsid, float speed, float damage, float destTime);

	void OnCollision(CollideBox* other);

	virtual void Kill() override;
};

