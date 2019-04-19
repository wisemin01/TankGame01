#pragma once
#include "CComponent.h"

class CRigidbody;
class CPixelCollider :
	public CComponent
{
protected:
	LPDIRECT3DTEXTURE9 m_lpTexture;
	
	float m_fWidth;
	float m_fHeight;

	bool m_bIsOnFloor = true;

	int m_iArraySize;
	PIXEL_INFO* m_pHeightArray;

	float m_fDepth;
public:
	CPixelCollider();
	virtual ~CPixelCollider();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Destroy() override;

	void RegisterMinimap(ResourceID map_id);
	void RegisterMinimap(CTexture* map_texture);

	virtual void CreatePixelCollider(CTexture* minimapTex, int minimapMaxCnt = 0, int mapLength = 0);
	virtual void CreateMapsAsPixelMap(CTexture* realMapTex, int renderLayer = 0);
	virtual void CreateCheckPoints(CTexture * minimapTex, int renderLayer = 0);

	void UnRegisterMinimap();

	virtual bool IsCollisionOnFloor(Vector3 position);
	virtual bool IsCollision(Vector3 position);

	virtual Vector3 GetNormalVector(Vector3 position);
	virtual Vector3 GetLineVector(Vector3 position);
	virtual Vector3 GetSlipVector(Vector3 position, Vector3 force);

	virtual void CalcOnHeightMap(Vector3 *position, Vector3 *force);

	virtual void GetLineRotation(const Vector3& position, float* rot);

	PIXEL_INFO* GetHeightArray() { return m_pHeightArray; }

	PIXEL_TYPE GetPixelType(Vector3 position);

	void CreateHeightMap(CTexture* targetTex, PIXEL_INFO* array, int indexX = 0);
	void SetCameraInMap();

	bool IsOnFloor() { return m_bIsOnFloor; }
	void SetObjectOnPixelMap(const string& objectTag, float minusIndexY = -50);

	void UploadMinimapData();
	void DownloadMinimapData();

	bool IsOutOfRange(int x);

	void SetLineDepth(float depth);
};

