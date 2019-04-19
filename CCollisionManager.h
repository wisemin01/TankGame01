#pragma once
#include "CSingleton.h"

enum PIXEL_TYPE
{
	TYPE_NONE = 1 << 0,
	TYPE_FLOOR = 1 << 1,
	TYPE_TRAP = 1 << 2
};

using PIXEL_INFO = std::pair<int, PIXEL_TYPE>;

class CollideBox;
class CCollisionManager :
	public CSingleton<CCollisionManager>
{
private:
	std::list<CollideBox*> m_ColliderContainer;

	PIXEL_INFO* m_pHeightArray;
	int m_iHeightArraySize;
public:
	CCollisionManager();
	virtual ~CCollisionManager();

	void Update();

	void Register(CollideBox* col);
	void UnRegister(CollideBox* col);

	void LoadHeightArray(PIXEL_INFO* pArray, int iSize);
	PIXEL_INFO* GetHeightArray(int* pOutSize);
	int GetMapWidth() { return m_iHeightArraySize; }

	void SetObjectOnPixelMap(const string& objectTag, float minusIndexY = -50);
	void SetObjectOnPixelMap(CGameObject* object, float minusIndexY = -50);

	bool IsOnLoad(Vector3 position);

	bool IsOutOfRange(float x);
};

#define COLLISION (*CCollisionManager::Instance())