#pragma once

class CGameObject
{
private:
	friend class CComponent;
	friend class CRenderer;
	friend class CTransform;
	friend class CRigidbody;
	friend class CCollider;
	friend class CPixelCollider;
	friend class CMultiPixelCollider;

public:
	bool m_bIsLive = true;
	bool m_bIsDisplay = true;

	string m_szTag;

	CRenderer*		m_pRenderer		 = nullptr;
	CTransform*		m_pTransform	 = nullptr;
	CRigidbody*		m_pRigidbody	 = nullptr;
	CCollider*		m_pCollider		 = nullptr;
	CPixelCollider* m_pPixelCollider = nullptr;

	map<string, CComponent*> m_ComponentMap;
public:
	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Destroy();

	void ComponentUpdate();
	void ComponentRender();
	void ComponentDestroy();
	
	virtual void Kill() { m_bIsLive = false; }
	void Kill(CGameObject* target) { target->Kill(); }

	bool IsLive() { return m_bIsLive; }
	
	const string& GetTag() const { return m_szTag; }
	void SetTag(const string& tag) { m_szTag = tag; }
	bool CompareTag(const string& tag) { return tag == m_szTag; }

	void SetDisplay(bool is_render) { m_bIsDisplay = is_render; }
	bool GetIsDisplay() { return m_bIsDisplay; }

	CRenderer * GetRenderer() { return m_pRenderer; }
	CTransform* GetTransform() { return m_pTransform; }

	template <typename T>
	T* AddComponent()
	{
		string key = typeid(T).name();
		auto find = m_ComponentMap.find(key);

		if (find == m_ComponentMap.end()) {
			T* com = new T;
			com->SetOwnerObject(this);

			com->Init();

			m_ComponentMap.insert(make_pair(key, com));
			return com;
		}
		else
		{
			return reinterpret_cast<T*>(find->second);
		}
	}

	template <typename T>
	T* GetComponent()
	{
		string key = typeid(T).name();
		auto find = m_ComponentMap.find(key);

		if (find == m_ComponentMap.end()) {
			return nullptr;
		}
		else
		{
			return reinterpret_cast<T*>(find->second);
		}
	}

public:

	static bool CompareLayer(CGameObject* _1, CGameObject* _2);
	static bool CompareY(CGameObject* _1, CGameObject* _2);
};