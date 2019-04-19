#pragma once
#include "CObject.h"

class CScrollBackground :
	public CGameObject
{
private:
	float m_fRed = 1.0f;

	Vector3 m_vPivotPos;

	float m_fWidth;
	float m_fHeight;
	float m_fRenderX;
	float m_fPrevCameraX;

	int m_iScroll = 0;

public:
	CScrollBackground();
	virtual ~CScrollBackground();

public:

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;

	void Setting(ResourceID key, Vector3 position, float red);
	void Setting(CTexture* texture, Vector3 position, float red);
};

