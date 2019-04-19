#pragma once
#include "CObject.h"


class CButton
	: public CGameObject
{
public:
	enum BUTTON_STATE
	{
		IDLE	= 1 << 0,
		MOUSE	= 1 << 1,
		DOWN	= 1 << 2,
		CLICK	= 1 << 3
	};
private:
	std::function<void()> m_pOnClick;

	RECT m_rcRange;
	BUTTON_STATE m_eButtonState;

	bool m_bIsLerp;
public:
	CButton() {}
	virtual ~CButton() {}

	virtual void Init() override;
	virtual void Update() override;
	virtual void Destroy() override;

	void ButtonSetup(Vector3 position, ResourceID buttonImg,
		int width, int height, function<void()> onClick);

private:
	bool IsSelected();
};
