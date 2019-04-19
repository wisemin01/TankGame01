#pragma once
#include "CObject.h"
class CGuiededBullet :
	public CGameObject
{
private:
	Vector3 m_vDirection;

	float m_fSpeed;
	float m_fDamage;

	CGameObject* m_pTarget;

	float m_fLostTime;
public:
	CGuiededBullet();
	virtual ~CGuiededBullet();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Destroy() override;
	
	void Fire(Vector3 position, ResourceID rsid, float speed, float damage);

	void OnCollision(CollideBox* other);
};

