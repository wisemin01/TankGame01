#include "DXUT.h"
#include "CMapPlacer.h"

#include "CBackground.h"
#include "CTexture.h"

#include "CCheckPoint.h"

CMapPlacer::CMapPlacer()
{
}


CMapPlacer::~CMapPlacer()
{
}

void CMapPlacer::Init()
{
	m_bIsDisplay = false;

	AC(CTransform);
	m_pTransform->SetPosition(0, 0, 0);
}

void CMapPlacer::CreateMaps(CTexture * mapData, int * mapList, int mapCount, int renderLayer)
{
	if (!mapList) {
		Instantiate(BACKGROUND, CBackground)->Setting(mapData->GetImage(0), m_pTransform->GetPosition(), renderLayer);
		return;
	}

	int w = mapData->GetImage(0)->info.Width;

	int size = mapData->GetSize();

	for (int i = 0; i < mapCount; i++)
	{
		int index = mapList[i];

		if (index > size - 1)
			continue;

		CTexture* mapTex = mapData->GetImage(index);

		Instantiate(BACKGROUND, CBackground)->Setting(mapTex,
			m_pTransform->GetPosition() + Vector3(i * w, 0, 0), renderLayer);
	}

	Kill();
}

void CMapPlacer::CreateCheckPoints(CTexture * mapData, int * mapList, int flagCount, int renderLayer)
{
	int w = mapData->GetImage(0)->info.Width;

	int size = mapData->GetSize();

	for (int i = 1; i < flagCount; i++)
	{
		int index = mapList[i];

		if (index > size - 1)
			continue;

		CTexture* mapTex = mapData->GetImage(index);

		Instantiate(OBSTACLE, CCheckPoint)->Place(m_pTransform->GetPosition()
			+ Vector3(i * w + 200, 0, 0));
	}
	
	Kill();
}
