#pragma once
#include "CObject.h"


class CExplode :
	public CGameObject
{
private:

public:
	CExplode();
	virtual ~CExplode();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Destroy() override;

	void Setup(Vector3 pos, ResourceID rsid, float delay);
};

