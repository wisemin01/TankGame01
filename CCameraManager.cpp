#include "DXUT.h"
#include "CCameraManager.h"

#include "CObject.h"
#include "CTransform.h"

CCameraManager::CCameraManager()
{
}


CCameraManager::~CCameraManager()
{
}

void CCameraManager::Update()
{
	if (m_pTarget)
	{
		Vector3 targetPosition = m_pTarget->GetTransform()->GetPosition() + m_vOffset - V3CENTER;

		D3DXVec3Lerp(&m_vPosition, &m_vPosition, &targetPosition, DXUTGetElapsedTime() * m_fSpeed);
	}

	if(m_fShakeTime > GetNowTime())
	{ 
		float rx = RandomNumber(-m_fShakePower, m_fShakePower);
		float ry = RandomNumber(-m_fShakePower, m_fShakePower);

		m_vPosition += Vector3(rx, ry, 0);
	}

	if (m_bIsLockOnRange)
	{
		float cameraLeft = m_vPosition.x - WINSIZEX / 2.f;
		float cameraRight = m_vPosition.x + WINSIZEX / 2.f;
		float cameraTop = m_vPosition.y - WINSIZEY / 2.f;
		float cameraBottom = m_vPosition.y + WINSIZEY / 2.f;

		if (m_rcRange.left > cameraLeft)
			m_vPosition.x = m_rcRange.left + WINSIZEX / 2.f;
		if (m_rcRange.right < cameraRight)
			m_vPosition.x = m_rcRange.right - WINSIZEX / 2.f;

		if (m_rcRange.top > cameraTop)
			m_vPosition.y = m_rcRange.top + WINSIZEY / 2.f;
		if (m_rcRange.bottom < cameraBottom)
			m_vPosition.y = m_rcRange.bottom - WINSIZEY / 2.f;
	}
}

void CCameraManager::SetTarget(CGameObject * target)
{
	m_pTarget = target;
}

void CCameraManager::Init(Vector3 position, Vector3 scale)
{
	m_vPosition		= position;
	m_vScale		= scale;
	m_vOffset		= V3ZERO;
}

void CCameraManager::Shake(float time, float power)
{
	if (m_fShakeTime > GetNowTime())
	{
		if (m_fShakeDelay * m_fShakePower < time * power) {
			m_fShakeDelay = time;
			m_fShakeTime = time + GetNowTime();
			m_fShakePower = power;
		}
	}
	else
	{
		m_fShakeDelay = time;
		m_fShakeTime = time + GetNowTime();
		m_fShakePower = power;
	}
}

void CCameraManager::UseRange(float left, float top, float right, float bottom)
{
	SetRect(&m_rcRange, left, top, right, bottom);
	m_bIsLockOnRange = true;
}

void CCameraManager::UnuseRange()
{
	m_bIsLockOnRange = false;
}

void CCameraManager::LockInMap(Vector3 * target_position)
{
	if (!m_bIsLockOnRange)
		return;

	if (target_position->x < m_rcRange.left + WINSIZEX / 2.f)
		target_position->x = m_rcRange.left + WINSIZEX / 2.f;
	if (target_position->x > m_rcRange.right + WINSIZEX / 2.f)
		target_position->x = m_rcRange.right + WINSIZEX / 2.f;

	if (target_position->y < m_rcRange.top + WINSIZEY / 2.f)
		target_position->y = m_rcRange.top + WINSIZEY / 2.f;
	if (target_position->y > m_rcRange.bottom + WINSIZEY / 2.f)
		target_position->y = m_rcRange.bottom + WINSIZEY / 2.f;
}

void CCameraManager::TranslateVector(Vector3 * pOut, const Vector3 * p1)
{
	(*pOut) = (*p1) + m_vPosition;
}
