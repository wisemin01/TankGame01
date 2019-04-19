#pragma once
#include "CScene.h"


class CIntroScene :
	public CScene
{
public:
	CIntroScene();
	virtual ~CIntroScene();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;
};

