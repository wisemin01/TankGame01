#pragma once
#include "CObject.h"

class CPlayer;
class CPlayerController :
	public CGameObject
{
private:
	int m_iHealth;
	int m_iStage;

	CPlayer* m_pNowPlayer;

	float m_fPlayTime;

	float m_fProgress;

	string* m_szString;

	CTexture* m_pItemTexture;
	CTexture* m_pHeart;

	bool m_bIsGameEnd;
	bool m_bIsStageClear;

public:
	CPlayerController();
	virtual ~CPlayerController();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;

	void Setting(int stage);

	void RespawnPlayer();

	void DrawItemMap();
	void DrawHeart();
};

