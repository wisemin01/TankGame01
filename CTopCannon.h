#pragma once
#include "CObject.h"

class CPlayer;
class CTopCannon :
	public CGameObject
{
private:
	CPlayer * m_pPlayer;
public:
	CTopCannon();
	virtual ~CTopCannon();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Destroy() override;

	void Setup(CPlayer* playerInfo);
};

