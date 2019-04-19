#include "DXUT.h"
#include "CObjectManager.h"

#include "CObject.h"
#include "CRenderer.h"

CObjectManager::CObjectManager()
{
}


CObjectManager::~CObjectManager()
{
	Clear();
}

void CObjectManager::Update()
{
	m_RenderingList.clear();

	for (auto i = 0; i < OBJECT_TYPE::END; i++)
	{
		list<CGameObject*>& list = m_ObjectList[i];

		for (auto iter = list.begin(); iter != list.end();)
		{
			if ((*iter)->IsLive())
			{
				// 업데이트

				(*iter)->ComponentUpdate();
				(*iter)->Update();

				if ((*iter)->GetIsDisplay())
				{
					// 렌더링 리스트에 추가

					m_RenderingList.push_back(*iter);
				}

				iter++;
			}
			else
			{
				(*iter)->ComponentDestroy();
				(*iter)->Destroy();

				SAFE_DELETE(*iter);

				iter = list.erase(iter);
			}
		}
	}

	m_RenderingList.sort(CGameObject::CompareLayer);
	m_RenderingList.sort(CGameObject::CompareY);
}

void CObjectManager::Render()
{
	for (auto iter : m_RenderingList)
	{
		iter->ComponentRender();
		iter->Render();
	}
}

void CObjectManager::Clear()
{
	for (auto i = 0; i < OBJECT_TYPE::END; i++)
	{
		list<CGameObject*>& list = m_ObjectList[i];

		for (auto iter : list) {
		
			iter->ComponentDestroy();
			iter->Destroy();

			SAFE_DELETE(iter);
		}

		list.clear();
	}
}
