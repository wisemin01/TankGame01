#include "DXUT.h"
#include "CEnemy.h"
#include "CPlayer.h"
#include "CLifeSystem.h"
#include "CExplode.h"
#include "CDelayBullet.h"

#include "CMine.h"

CEnemy::CEnemy()
{
}


CEnemy::~CEnemy()
{
}

void CEnemy::Init()
{
	AC(CTransform);
	AC(CRenderer);
	AC(CCollider);
	AC(CRigidbody);

	m_pLife = AC(CLifeSystem);

	SetTag("ENEMY");
}

void CEnemy::Update()
{
	if (auto value = FIND_DATA(bool, "PLAYER_LIFE"))
	{
		if (!(*value))
		{
			m_pTarget = nullptr;
		}
	}

	if (m_pTarget)
	{
		switch (m_eState) {
		case MOVE:
			MoveUpdate();
			break;
		case ATTACK:
			AttackUpdate();
			break;
		}
	}
	else
	{
		Vector3 direction = Vector3(0, -1, 0);

		m_pRigidbody->AddForce(direction, m_fSpeed);

		if (m_pTransform->GetPosition().y <= -200)
			Kill();
	}

	if (m_pLife->IsDeath())
		Kill();
}

void CEnemy::Destroy()
{

}

void CEnemy::MoveUpdate()
{
	Vector3 endPos = m_pTarget->GetTransform()->GetPosition();

	endPos.y = m_fYIndex;
	endPos.x += m_fXIndex;

	Vector3 direction = endPos - m_pTransform->GetPosition();

	float length = D3DXVec3Length(&direction);

	if (length < 100)
	{
		m_eState = ATTACK;

		m_pRenderer->SetFrame(0, 5, 150);
		m_pRenderer->SetTexture(m_StateTex.GetAttack());
	}

	D3DXVec3Normalize(&direction, &direction);

	m_pRigidbody->AddForce(direction, length > 500 ? m_fSpeed * 2 : m_fSpeed);
}

void CEnemy::AttackUpdate()
{
	if (m_pRenderer->GetNowFrame() == 5) {
		m_eState = MOVE;
		m_StateTex.GetMove();

		if (m_eType == DROP_MINE)
		{
			Instantiate(ENEMY, CMine)->Drop(m_pTransform->GetPosition());
		}
		else if (m_eType == NORMAL)
		{
			auto bul = Instantiate(EFFECT, CDelayBullet);
			bul->Fire(m_pTransform->GetPosition(), Vector3(0, 1, 0), "BULLET", 20, 1, 1000);
			bul->m_pRigidbody->SetVelocity(0, 400 * DELTIME, 0);
			bul->SetTag("ENEMY_BULLET");
		}
	}
}

void CEnemy::Setup(Vector3 position, float yRange)
{
	m_fXIndex = RandomNumber(200, 400);
	m_fYIndex = yRange;

	m_eState = MOVE;

	m_pTransform->SetPosition(position);

	m_pRenderer->SetTexture(m_StateTex.GetMove());
	m_pTransform->SetScale(Vector3(0.5f, 0.5f, 0.5f));

	m_pRenderer->SetFrame(0, 5, 200);
	m_pRenderer->SetRenderLayer(11);

	m_pRigidbody->SetIsUseGravity(false);

	m_pCollider->AddColliderAsTexture(m_pRenderer->m_pTexture, V3ZERO,
		[&](CollideBox* other) {});
}

void CEnemy::SetupWithDropMineEnemy(Vector3 position, float yRange)
{
	m_StateTex.Get("MINE_ENEMY");
	m_eType = DROP_MINE;
	m_fSpeed = 12;

	m_pLife->LifeSetup(5);
	Setup(position, yRange);
}

void CEnemy::SetupNormalEnemy(Vector3 position, float yRange)
{
	m_StateTex.Get("ENEMY");
	m_eType = NORMAL;
	m_fSpeed = 18;

	m_pLife->LifeSetup(10);
	Setup(position, yRange);
}

void CEnemy::Kill()
{
	auto explode = Instantiate(EFFECT, CExplode);
	explode->Setup(m_pTransform->GetPosition(), "PLASMA", 100);
	explode->GetTransform()->SetScale(3, 3, 3);
	explode->GetRenderer()->SetRenderLayer(13);
	m_bIsLive = false;
}
