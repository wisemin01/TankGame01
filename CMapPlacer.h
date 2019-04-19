#pragma once
#include "CObject.h"
class CMapPlacer :
	public CGameObject
{
public:
	CMapPlacer();
	virtual ~CMapPlacer();

	void Init();

	void CreateMaps(CTexture* mapData, int* mapList, int mapCount, int renderLayer = 0);
	void CreateCheckPoints(CTexture* mapData, int* mapList, int flagCount, int renderLayer = 0);
};

