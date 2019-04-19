#include "DXUT.h"
#include "CTopCannon.h"

#include "CPlayer.h"
#include "CDelayBullet.h"

CTopCannon::CTopCannon()
{
}


CTopCannon::~CTopCannon()
{
}

void CTopCannon::Init()
{
	AC(CTransform);
	AC(CRenderer);
}

void CTopCannon::Update()
{
	if (m_pPlayer)
	{
		m_pTransform->SetPosition(m_pPlayer->GetTransform()->GetPosition()
			+ Vector3(-15, -83, 0));

		Vector3 target = INPUT.GetMousePos();

		CAMERA.TranslateVector(&target, &target);

		Vector3 dir = target - m_pTransform->GetPosition();

		D3DXVec3Normalize(&dir, &dir);

		m_pTransform->SetRotation(atan2f(dir.y, dir.x));

		if (INPUT.GetKeyDown(VK_LBUTTON))
		{
			auto bul = Instantiate(EFFECT, CDelayBullet);
			bul->Fire(m_pTransform->GetPosition(), dir, "BULLET", 50, 1, 1000);
			bul->m_pRigidbody->SetVelocity(dir.x * 400 * DELTIME, dir.y * 400 * DELTIME, 0);
		}
	}
}

void CTopCannon::Destroy()
{
}

void CTopCannon::Setup(CPlayer * playerInfo)
{
	m_pTransform->SetPosition(playerInfo->GetTransform()->GetPosition());
	m_pTransform->SetScale(playerInfo->GetTransform()->GetScale());

	m_pRenderer->SetTexture("CANNON");

	m_pRenderer->SetRenderLayer(playerInfo->GetRenderer()->GetRenderLayer() - 1);

	m_pPlayer = playerInfo;

	m_pRenderer->m_vCenter = Vector3(26, 33, 0);
}
