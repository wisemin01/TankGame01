#pragma once
#include "CObject.h"
class CBackground :
	public CGameObject
{
public:
	CBackground();
	virtual ~CBackground();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;

	void Setting(ResourceID key, Vector3 position, int layer = 0);
	void Setting(CTexture* texture, Vector3 position, int layer = 0);
};

