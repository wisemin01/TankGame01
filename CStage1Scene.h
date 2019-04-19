#pragma once
#include "CScene.h"

class CStage1Scene :
	public CScene
{
public:
	CStage1Scene();
	virtual ~CStage1Scene();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;
};

