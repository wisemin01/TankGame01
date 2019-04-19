#pragma once
#include "CPixelCollider.h"


class CMultiPixelCollider :
	public CPixelCollider
{
protected:

	int* m_iMapDataArray = nullptr;
	int  m_iMapKindCount = 0;
	int  m_iMapCount = 0;

public:
	CMultiPixelCollider();
	virtual ~CMultiPixelCollider();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Destroy() override;

	virtual void CreatePixelCollider(CTexture* minimapTex, int minimapMaxCnt, int mapCount);
	virtual void CreateMapsAsPixelMap(CTexture* realMapTex, int renderLayer = 0);
	virtual void CreateCheckPoints(CTexture * minimapTex, int renderLayer = 0);

	int* GetMapDataArray() { return m_iMapDataArray; }

	virtual bool IsCollisionOnFloor(Vector3 position);
	virtual bool IsCollision(Vector3 position);

	virtual Vector3 GetNormalVector(Vector3 position);
	virtual Vector3 GetLineVector(Vector3 position);
	virtual Vector3 GetSlipVector(Vector3 position, Vector3 force);

	virtual void CalcOnHeightMap(Vector3 *position, Vector3 *force);

	virtual void GetLineRotation(const Vector3& position, float* rot);
};

