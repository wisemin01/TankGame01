#pragma once
#include "CScene.h"

class CStage2Scene :
	public CScene
{
private:

public:
	CStage2Scene();
	~CStage2Scene();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;
};

