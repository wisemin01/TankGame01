#pragma once
#include "CSingleton.h"

class CScene;
class CSceneManager
	: public CSingleton<CSceneManager>
{
private:
	map<string, CScene*> m_SceneMap;

	CScene* m_pNowScene		= nullptr;
	CScene* m_pNextScene	= nullptr;

public:
	CSceneManager();
	~CSceneManager();

	void AddScene(const string& key, CScene* scene);
	void ChangeScene(const string& key);

	void Update();
	void Render();

	CScene* GetNowScene() { return m_pNowScene; }
};

#define SCENE (*CSceneManager::Instance())