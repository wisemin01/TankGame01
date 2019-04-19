#include "DXUT.h"
#include "CGuiededBullet.h"
#include "CLifeSystem.h"

CGuiededBullet::CGuiededBullet()
{
}


CGuiededBullet::~CGuiededBullet()
{
}

void CGuiededBullet::Init()
{
	AC(CTransform);
	AC(CRigidbody);
	AC(CRenderer);
	AC(CCollider);

	m_pRenderer->SetRenderLayer(5);
	SetTag("BULLET");
}

void CGuiededBullet::Update()
{
	if (m_pTarget)
	{
		if (m_pTarget->IsLive())
		{
			m_vDirection = m_pTarget->GetTransform()->GetPosition() - m_pTransform->GetPosition();

			D3DXVec3Normalize(&m_vDirection, &m_vDirection);
		}
		else
		{
			m_pTarget = nullptr;
			Kill();
		}
	}
	else
	{
		m_fLostTime += DELTIME;
	
		m_vDirection = Vector3(1, 0, 0);
	}

	if (m_fLostTime >= 200)
		Kill();

	m_pRigidbody->AddForce(m_vDirection, m_fSpeed);
	m_pTransform->SetRotation(VectorToRotation(m_vDirection));
}

void CGuiededBullet::Destroy()
{

}

void CGuiededBullet::Fire(Vector3 position, ResourceID rsid, float speed, float damage)
{
	m_vDirection = V3ZERO;
	m_pTarget = nullptr;
	m_fSpeed = speed;
	m_fDamage = damage;

	m_pTransform->SetPosition(position);
	m_pRenderer->SetTexture(rsid);
	m_pRigidbody->SetIsUseGravity(false);

	m_pRigidbody->AddForce(Vector3(1, 0, 0), 100);

	m_pCollider->AddCollider(2000, 2000, V3ZERO, [&](CollideBox* other) {
		if (other->GO->IsLive() == false)
			return;

		if (other->GO->CompareTag("ENEMY"))
			if (!m_pTarget)
				m_pTarget = other->GO;
			}, true);

	m_pCollider->AddColliderAsTexture(m_pRenderer->m_pTexture, V3ZERO, [&](CollideBox* other) { OnCollision(other); });
}

void CGuiededBullet::OnCollision(CollideBox * other)
{
	if (other->GO->CompareTag("ENEMY"))
	{
		other->GO->GC(CLifeSystem)->TakeDamage(m_fDamage);
		Kill();
	}

	if (other->GO->CompareTag("MINE"))
	{
		Kill();
	}
}
