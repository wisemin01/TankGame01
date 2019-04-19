#pragma once
#include "CObject.h"

enum FADE_TYPE
{
	FADE_TO_255,
	FADE_TO_0,
	NOEE_FADE
};

class CFade :
	public CGameObject
{
private:
	FADE_TYPE m_eType;

	int m_iFadeCount;
	float m_fSpeed;

	std::function<void()> m_pToChange255;
	std::function<void()> m_pToChange0;
public:
	CFade();
	virtual ~CFade();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Destroy() override;

	void Fade(FADE_TYPE type, int fadeCount = 1, float speed = 1);

	void AddFunc(FADE_TYPE type, const std::function<void()>& func);
};

