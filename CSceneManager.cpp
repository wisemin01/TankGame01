#include "DXUT.h"
#include "CSceneManager.h"

#include "CScene.h"

CSceneManager::CSceneManager()
{

}


CSceneManager::~CSceneManager()
{
	if (m_pNowScene)
		m_pNowScene->Destroy();

	for (auto iter : m_SceneMap)
	{
		SAFE_DELETE(iter.second);
	}

	m_SceneMap.clear();
}

void CSceneManager::AddScene(const string & key, CScene * scene)
{
	auto find = m_SceneMap.find(key);

	if (find == m_SceneMap.end())
	{
		scene->SetSceneKey(key);
		m_SceneMap.insert(make_pair(key, scene));
	}
	else
	{
		return;
	}
}

void CSceneManager::ChangeScene(const string & key)
{
	auto find = m_SceneMap.find(key);

	if (find != m_SceneMap.end())
	{
		m_pNextScene = find->second;
	}
}

void CSceneManager::Update()
{
	if (m_pNextScene)
	{
		if (m_pNowScene)
		{
			OBJECT.Clear();
			DATA.Clear();
			m_pNowScene->Destroy();
			m_pNowScene = nullptr;

			RESOURCE.Clear();
		}

		m_pNextScene->Init();
		m_pNowScene = m_pNextScene;
		m_pNextScene = nullptr;
	}

	if (m_pNowScene)
	{
		OBJECT.Update();
		COLLISION.Update();
		m_pNowScene->Update();
	}
}

void CSceneManager::Render()
{
	if (m_pNowScene) {
		OBJECT.Render();
		m_pNowScene->Render();
	}
}
