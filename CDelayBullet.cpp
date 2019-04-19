#include "DXUT.h"
#include "CDelayBullet.h"
#include "CExplode.h"
#include "CLifeSystem.h"

CDelayBullet::CDelayBullet()
{
}


CDelayBullet::~CDelayBullet()
{
}

void CDelayBullet::Init()
{
	AC(CTransform);
	AC(CRenderer);
	AC(CRigidbody);
	AC(CCollider);

	m_pRenderer->SetRenderLayer(5);
	SetTag("BULLET");
}

void CDelayBullet::Update()
{
	m_pRigidbody->AddForce(m_vDirection, m_fSpeed);

	m_pTransform->SetRotation(VectorToRotation(m_vDirection));

	if (m_fEndTime <= GetNowTime())
	{
		Kill();
	}
}

void CDelayBullet::Destroy()
{

}

void CDelayBullet::Fire(Vector3 position, Vector3 direction, ResourceID rsid, float speed, float damage, float destTime)
{
	m_vDirection = direction;
	m_fSpeed = speed;
	m_fDamage = damage;
	m_fEndTime = destTime + GetNowTime();

	m_pTransform->SetPosition(position);
	m_pRenderer->SetTexture(rsid);
	m_pRigidbody->SetIsUseGravity(false);
	m_pCollider->AddColliderAsTexture(m_pRenderer->m_pTexture, V3ZERO, [&](CollideBox* other) { OnCollision(other); });

	m_pRigidbody->GetVelocity().x = speed * 20 * DELTIME;
}

void CDelayBullet::OnCollision(CollideBox * other)
{
	if (other->GO->CompareTag("ENEMY"))
	{
		if (m_szTag == "BULLET")
		{
			other->GO->GC(CLifeSystem)->TakeDamage(m_fDamage);
			Kill();
		}
	}

	else if (other->GO->CompareTag("MINE"))
	{
		if (m_szTag == "BULLET")
		{
			Kill();
		}
	}

	else if (other->GO->CompareTag("PLAYER"))
	{
		if (m_szTag == "ENEMY_BULLET")
		{
			other->GO->Kill();
			Kill();
		}
	}
}

void CDelayBullet::Kill()
{
	m_bIsLive = false;

	Instantiate(EFFECT, CExplode)->Setup(m_pTransform->GetPosition(), "EXPLODE", 50);
}
