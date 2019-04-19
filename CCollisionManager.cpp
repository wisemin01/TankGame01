#include "DXUT.h"
#include "CCollisionManager.h"

#include "CCollider.h"
#include "CObject.h"

CCollisionManager::CCollisionManager()
{
	m_pHeightArray = nullptr;
	m_iHeightArraySize = 0;
}


CCollisionManager::~CCollisionManager()
{
	m_ColliderContainer.clear();

	SAFE_DELETE_ARRAY(m_pHeightArray);
}

void CCollisionManager::Update()
{
	if (m_ColliderContainer.size() < 1)
		return;

	for (auto col1 = m_ColliderContainer.begin(); col1 != std::prev(m_ColliderContainer.end(), 1); col1++)
	{
		std::list<CollideBox*>::iterator next_iter = std::next(col1);

		for (auto col2 = std::next(col1, 1); col2 != m_ColliderContainer.end(); col2++)
		{
			RECT overlap;
			
			RECT range1 = (*col1)->GetWorldRange();
			RECT range2 = (*col2)->GetWorldRange();

			if (IntersectRect(&overlap, &range1, &range2))
			{
				(*col1)->m_pLinkFunc(*col2);
				(*col2)->m_pLinkFunc(*col1);
			}
		}
	}
}

void CCollisionManager::Register(CollideBox * col)
{
	m_ColliderContainer.push_back(col);
}

void CCollisionManager::UnRegister(CollideBox * col)
{
	m_ColliderContainer.remove(col);
}

void CCollisionManager::LoadHeightArray(PIXEL_INFO* pArray, int iSize)
{
	ResizeArray(m_pHeightArray, iSize);

	memcpy(m_pHeightArray, pArray, sizeof(PIXEL_INFO) * iSize);
	m_iHeightArraySize = iSize;
}

PIXEL_INFO * CCollisionManager::GetHeightArray(int * pOutSize)
{
	*pOutSize = m_iHeightArraySize;
	return m_pHeightArray;
}

void CCollisionManager::SetObjectOnPixelMap(const string & objectTag, float minusIndexY)
{
	CGameObject* object = OBJECT.FindGameObject<CGameObject>(objectTag);
	SetObjectOnPixelMap(object, minusIndexY);
}

void CCollisionManager::SetObjectOnPixelMap(CGameObject * object, float minusIndexY)
{
	if (object) {

		Vector3* position = object->GetTransform()->GetPositionPtr();

		if (IsOutOfRange(position->x)) {
			position->y = 0;
			return;
		}

		if (m_pHeightArray[(int)position->x].second == PIXEL_TYPE::TYPE_TRAP ||
			m_pHeightArray[(int)position->x].second == PIXEL_TYPE::TYPE_NONE)
			position->y = 0;
		else
			position->y = m_pHeightArray[(int)position->x].first + minusIndexY;
	}
}

bool CCollisionManager::IsOnLoad(Vector3 position)
{
	if (IsOutOfRange(position.x)) {
		return false;
	}

	if (m_pHeightArray[(int)position.x].first <= position.y)
	{
		if (m_pHeightArray[(int)position.x].second == PIXEL_TYPE::TYPE_TRAP ||
			m_pHeightArray[(int)position.x].second == PIXEL_TYPE::TYPE_NONE)
			return false;
		else
			return true;
	}

	return false;
}

bool CCollisionManager::IsOutOfRange(float x)
{
	// 0 보다 작거나 배열 사이즈보다 크면 true.
	if (x < 0 || x > m_iHeightArraySize)
		return true;
	else
		return false;
}
