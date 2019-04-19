#pragma once
#include "CSingleton.h"

class CGameObject;
class CObjectManager :
	public CSingleton<CObjectManager>
{
private:
	list<CGameObject*> m_ObjectList[OBJECT_TYPE::END];
	list<CGameObject*> m_RenderingList;
public:
	CObjectManager();
	virtual ~CObjectManager();

	template <typename T>
	T* AddObject(OBJECT_TYPE type)
	{
		T* new_object = new T;
		new_object->Init();

		m_ObjectList[type].push_back(new_object);
		return new_object;
	}

	void Update();
	void Render();

	void Clear();

	template <class T>
	T* FindGameObject(const string& tag)
	{
		if (!std::is_base_of<CGameObject, T>::value)
			return nullptr;

		for (auto iter : m_ObjectList)
		{
			for (auto find : iter)
			{
				if (find->CompareTag(tag))
					return reinterpret_cast<T*>(find);
			}
		}

		return nullptr;
	}
};

#define OBJECT (*CObjectManager::Instance())
#define Instantiate(type, obj) OBJECT.AddObject<obj>(type)