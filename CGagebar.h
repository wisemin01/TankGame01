#pragma once
#include "CObject.h"
class CGagebar :
	public CGameObject
{
private:
	RECT m_rcRange;

	CTexture* m_pGageBar;
	CTexture* m_pIcon;

	float * m_pPercent;

	Vector3 m_vIconPos;
public:
	CGagebar();
	virtual ~CGagebar();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;

	void Setup(float* percent);
};

