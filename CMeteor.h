#pragma once
#include "CObject.h"


class CMeteor :
	public CGameObject
{
private:
	Vector3 m_vDirection;
	float m_fSpeed;
public:
	CMeteor();
	virtual ~CMeteor();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Destroy() override;

	void Create(Vector3 position);
};

