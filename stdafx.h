#pragma once

#include <iostream>
#include <map>
#include <list>
#include <vector>
#include <functional>
#include <array>
#include <stack>
#include <queue>
#include <string>

using namespace std;

using Vector2 = D3DXVECTOR2;
using Vector3 = D3DXVECTOR3;
using Vector4 = D3DXVECTOR4;

using ResourceID = const string&;

enum WINDOWSIZE {
	WINMODE = FALSE,
	WINSIZEX = 1280,
	WINSIZEY = 720,
	HALFSIZEX = WINSIZEX / 2,
	HALFSIZEY = WINSIZEY / 2
};


#define V3CENTER Vector3(HALFSIZEX, HALFSIZEY, 0)
#define V2CENTER Vector2(HALFSIZEX, HALFSIZEY)

#define V3ZERO Vector3(0, 0, 0)
#define V2ZERO Vector2(0, 0)

#define DELTIME DXUTGetElapsedTime()

void D3DXVec3Multiply(D3DXVECTOR3* pOut, CONST D3DXVECTOR3* p1, CONST D3DXVECTOR3* p2);
int   RandomNumber (int min, int max);
float FRandomNumber(float min, float max);
bool IntersectPointInRect(CONST RECT* pRect, CONST D3DXVECTOR3* pPt);

ostream& operator <<(ostream& os, const Vector3& pos);

template <typename T>
void Lerp(T& ref, const T& end, float speed)
{
	ref = ref + (end - ref) * speed;
}

template <typename T>
void ResizeArray(T *& arr, int size)
{
	if (arr)
	{
		delete arr;
		arr = nullptr;
	}

	arr = new T[size];
}

template <typename T>
float VectorToRotation(const T& dir)
{
	return (float)atan2f(dir.y, dir.x);
}

enum OBJECT_TYPE
{
	BACKGROUND,
	PLAYER,
	CANNON,
	OBSTACLE,
	SPAWNER,
	EFFECT,
	ENEMY,
	UI,
	END
};

enum RENDER_TYPE
{
	SCREEN = D3DXSPRITE_ALPHABLEND,
	SCROLL = D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE
};

enum ATTACK_MODE
{
	NORMAL_ATTACK,
	ATTACK_END
};

enum ITEM_TYPE
{
	DOUBLE_JUMP_BOOSTER = 0,
	RANGE_UPGRADE = 1,
	HOMING_MISSILE = 2,
	THREE_DIR_MISSILE = 3,
	ITEM_END = 4
};

enum TANK_MODE
{
	PANZER,
	WHIPPET,
	HEAVYTANK,
	TANK_END
};

#define GetNowTime() timeGetTime()
#define GameExit(exitCode) PostQuitMessage(exitCode)
#define GO GetGameObject()

#define AC(com) AddComponent<com>()
#define GC(com) GetComponent<com>()

#define VK_W (INT)('W')
#define VK_A (INT)('A')
#define VK_S (INT)('S')
#define VK_D (INT)('D')

#if DEBUG
#define CONSOLE_LOG(log) std::cout << log << std::endl;
#else
#define CONSOLE_LOG(log) 
#endif


#include "CResourceManager.h"
#include "CSceneManager.h"
#include "CObjectManager.h"
#include "CCameraManager.h"
#include "CInputManager.h"
#include "CCollisionManager.h"
#include "CSoundManager.h"
#include "CDataManager.h"

#include "CTransform.h"
#include "CRenderer.h"
#include "CCollider.h"
#include "CPixelCollider.h"
#include "CMultiPixelCollider.h"
#include "CRigidbody.h"
#include "CStateTexture.h"