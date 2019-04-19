#pragma once
class CScene
{
private:
	string m_szSceneName;
public:
	CScene();
	virtual ~CScene();

	virtual void Init() PURE;
	virtual void Update() PURE;
	virtual void Render() PURE;
	virtual void Destroy() PURE;

	string GetSceneKey() { return m_szSceneName; }
	void SetSceneKey(const string& key) { m_szSceneName = key; }
};

