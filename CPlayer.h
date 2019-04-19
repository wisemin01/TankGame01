#pragma once
#include "CObject.h"

class CTopCannon;
class CPlayer :
	public CGameObject
{
private:
	Vector3 m_vBarrel;

	bool m_bIsCanDoubleJump = false;
	bool m_bIsCanUserControl = true;
	bool m_bIsInvinc = false;

	float m_fFrontSpeed;
	float m_fBackSpeed;
	float m_fJumpPower;

	int m_iNuclearCount;

	ATTACK_MODE m_eAttackMode = NORMAL_ATTACK;
	TANK_MODE	m_eTankMode = PANZER;

	map<ITEM_TYPE, float>* m_pItemMap;

	STATE m_eState = IDLE;

	CStateTexture m_StateTex[TANK_MODE::TANK_END];

	CTopCannon* m_pCannon;

public:
	CPlayer();
	virtual ~CPlayer();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;

	void MapSettingOnStage(int stage_number);
	void SettingMinimap(int stage_number);

	Vector3 GetBarrelPos();

	bool UpgradeTank();
	bool DegradeTank();

	void SetInvinc(bool invinc) { m_bIsInvinc = invinc; }
	bool GetInvinc() { return m_bIsInvinc; }

	bool IsCanUserControl() { return m_bIsCanUserControl; }
	void SetIsCanUserControl(bool value) { m_bIsCanUserControl = value; }

	void AddItem(ITEM_TYPE item, float duration) { m_pItemMap->insert(make_pair(item, duration + GetNowTime())); }

	void SpeedUp() { m_fFrontSpeed *= 1.5f; m_fBackSpeed *= 1.5f; }

	bool ItemCheck(ITEM_TYPE item);

	map<ITEM_TYPE, float>& GetItemMap() { return *m_pItemMap; }

private:
	void ChangeTank(TANK_MODE tank);
	void ChangeTextureAsState();

	void UpdatingItemList();

	void CalcPlayer();
	void CalcInput();
	void CalcState();

	virtual void Kill() override;
};

