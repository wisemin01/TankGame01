#include "DXUT.h"
#include "CCheckPoint.h"


CCheckPoint::CCheckPoint()
{
}


CCheckPoint::~CCheckPoint()
{
}

void CCheckPoint::Init()
{
	AC(CTransform);
	AC(CRenderer);
	AC(CCollider);

	SetTag("CHECKPOINT");
	m_pRenderer->SetFrame(0, 0, 0);
}

void CCheckPoint::Update()
{

}

void CCheckPoint::Destroy()
{
}

void CCheckPoint::Pass()
{
	if (m_bIsPassed)
		return;

	m_bIsPassed = true;
	INSERT_DATA("PLAYER_RESPAWN", new Vector3(m_pTransform->GetPosition()));
	m_pRenderer->SetFrame(1, 1, 0);
}

void CCheckPoint::Place(Vector3 position)
{
	m_pTransform->SetPosition(position);
	m_pTransform->SetScale(2.0, 2.0, 2.0);
	m_pRenderer->SetTexture("CHECKPOINT");

	COLLISION.SetObjectOnPixelMap(this, -m_pRenderer->Height() / 2.f);

	m_pCollider->AddColliderAsTexture(m_pRenderer->m_pTexture, V3ZERO, [&](CollideBox* other) {
		if (other->GO->CompareTag("PLAYER"))
			Pass();
		}, true);
}
