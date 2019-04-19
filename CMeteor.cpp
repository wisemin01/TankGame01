#include "DXUT.h"
#include "CMeteor.h"

#include "CTexture.h"

CMeteor::CMeteor()
{
}


CMeteor::~CMeteor()
{
}

void CMeteor::Init()
{
	AC(CTransform);
	AC(CRenderer);
	AC(CRigidbody);

	SetTag("METEOR");

}

void CMeteor::Update()
{
	m_pRigidbody->AddForce(m_vDirection, m_fSpeed);

	if (m_pTransform->GetPosition().y >= WINSIZEY + 400)
		Kill();
}

void CMeteor::Destroy()
{
}

void CMeteor::Create(Vector3 position)
{
	m_pTransform->SetPosition(position);
	m_pRenderer->SetTexture("METEOR");
	m_pRenderer->SetRenderLayer(11);
	m_pRigidbody->SetMass(2.0f);

	float w = m_pRenderer->m_pTexture->GetImage(0)->info.Width;

	m_vDirection = Vector3(0, 1, 0);

	m_vDirection.x = FRandomNumber(-0.25, 0.25);
	m_fSpeed = RandomNumber(8, 12);

	m_pTransform->SetRotation(atan2f(m_vDirection.y, m_vDirection.x));
}
