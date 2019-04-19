#pragma once
#include "CSingleton.h"

using DataKey = const string&;

class CDataManager :
	public CSingleton<CDataManager>
{
private:
	std::map<string, LPVOID> m_DataMap;
public:
	CDataManager();
	virtual ~CDataManager();

	template <typename T>
	T* InsertData(DataKey key, T* pData)
	{
		auto find = m_DataMap.find(key);

		if (find == m_DataMap.end())
		{
			// 저장된 데이터가 없다면 새로 생성 후 삽입.
			m_DataMap.insert(make_pair(key, (LPVOID)pData));
		}
		else
		{
			// 있다면 기존 키의 데이터 삭제 후
			// 새 데이터 삽입.
			SAFE_DELETE(find->second);
			find->second = pData;
		}

		return pData;
	}

	void DeleteData(DataKey key);

	template <typename T>
	T* FindData(DataKey key)
	{
		auto find = m_DataMap.find(key);

		if (find == m_DataMap.end())
			return nullptr;

		return (T*)find->second;
	}

	void Clear();
};

#define DATA (*CDataManager::Instance())

#define FIND_DATA(type, key) (DATA.FindData<type>(key))
#define INSERT_DATA(key , data) (DATA.InsertData(key, data));