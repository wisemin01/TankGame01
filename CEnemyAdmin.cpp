#include "DXUT.h"
#include "CEnemyAdmin.h"

#include "CEnemy.h"

CEnemyAdmin::CEnemyAdmin()
{
}


CEnemyAdmin::~CEnemyAdmin()
{
}

void CEnemyAdmin::Init()
{
	m_bIsDisplay = false;
}

void CEnemyAdmin::Update()
{
	if (auto value = FIND_DATA(bool, "PLAYER_LIFE"))
	{
		if (!(*value))
		{
			m_pTarget = nullptr;
		}
		else
		{
			if (!m_pTarget)
				m_pTarget = OBJECT.FindGameObject<CGameObject>("PLAYER");
		}
	}

	if (m_pTarget && m_fSpawnTime <= GetNowTime())
	{
		Vector3 spawn = (m_pTarget->GetTransform()->GetPosition());

		spawn.y = -100;
		spawn.x += 1000;

		int rEnemyType = RandomNumber(0, 1);

		CEnemy* pEnemy = Instantiate(ENEMY, CEnemy);

		if (rEnemyType == 0)
			pEnemy->SetupNormalEnemy(spawn, RandomNumber(180, 200));
		else if(rEnemyType == 1)
			pEnemy->SetupWithDropMineEnemy(spawn, RandomNumber(180, 200));

		pEnemy->SetTarget(m_pTarget);

		m_fSpawnTime = RandomNumber(m_fDelay, m_fDelay * 2) + GetNowTime();
	}
}

void CEnemyAdmin::Destroy()
{
}

void CEnemyAdmin::Setup(float delay)
{
	m_fDelay = delay;
	m_fSpawnTime = delay + GetNowTime();

	m_pTarget = OBJECT.FindGameObject<CGameObject>("PLAYER");
}
