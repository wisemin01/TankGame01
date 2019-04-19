#pragma once
#include "CComponent.h"
class CLifeSystem :
	public CComponent
{
public:
	int m_iMaxHp;
	int m_iCurHp;

public:
	CLifeSystem();
	virtual ~CLifeSystem();

	virtual void Init() override;

	void TakeDamage(int damage) { m_iCurHp -= damage; }

	void LifeSetup(int hp) { m_iMaxHp = m_iCurHp = hp; }

	bool IsDeath() { return (bool)(m_iCurHp <= 0); }
};

