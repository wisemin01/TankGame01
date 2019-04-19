#include "DXUT.h"
#include "CDataManager.h"


CDataManager::CDataManager()
{
}


CDataManager::~CDataManager()
{
	Clear();
}

void CDataManager::DeleteData(DataKey key)
{
	auto find = m_DataMap.find(key);

	if (find == m_DataMap.end())
		return;

	SAFE_DELETE(find->second);

	m_DataMap.erase(find);
}

void CDataManager::Clear()
{
	for (auto iter : m_DataMap)
	{
		SAFE_DELETE(iter.second);
	}
	m_DataMap.clear();
}
