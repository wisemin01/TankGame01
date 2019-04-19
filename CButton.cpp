#include "DXUT.h"
#include "CButton.h"

#define BUTTON_KEY (VK_LBUTTON)

void CButton::Init()
{
	AC(CTransform);
	AC(CRenderer);

	m_pRenderer->SetRenderType(SCREEN);
	m_eButtonState = IDLE;
	m_bIsLerp = true;
}

void CButton::Update()
{
	bool result = IsSelected();

	if (result)
	{
		if (m_eButtonState & IDLE || m_eButtonState & CLICK)
			m_eButtonState = MOUSE;
	}
	else
		m_eButtonState = IDLE;

	if (INPUT.GetKeyDown(BUTTON_KEY))
	{
		if (result)
			m_eButtonState = DOWN;
		else
			m_eButtonState = IDLE;
	}

	if (m_eButtonState & DOWN)
	{
		if (INPUT.GetKeyUp(BUTTON_KEY))
		{
			if (result)
			{
				m_pOnClick();
				m_eButtonState = CLICK;
			}
		}
	}

	if (m_bIsLerp)
	{
		if (m_eButtonState & MOUSE)
			Lerp(*m_pTransform->GetScalePtr(), Vector3(1.2, 1.2, 1.2), 7 * DELTIME);
		else
			Lerp(*m_pTransform->GetScalePtr(), Vector3(1.0, 1.0, 1.0), 7 * DELTIME);
	}

	switch (m_eButtonState)
	{
	case IDLE: *m_pRenderer->GetRenderFramePtr() = 0;
		break;
	case MOUSE: *m_pRenderer->GetRenderFramePtr() = 1;
		break;
	case DOWN: *m_pRenderer->GetRenderFramePtr() = 2;
		break;
	case CLICK: *m_pRenderer->GetRenderFramePtr() = 0;
		break;
	}
}

void CButton::Destroy()
{
}

void CButton::ButtonSetup(Vector3 position, ResourceID buttonImg, int width, int height, function<void()> onClick)
{
	m_pTransform->SetPosition(position);

	m_pRenderer->SetTexture(buttonImg);

	SetRect(&m_rcRange, -width / 2.f, -height / 2.f, width / 2.f, height / 2.f);

	m_pOnClick = onClick;
}

bool CButton::IsSelected()
{
	Vector3 mousePt = INPUT.GetMousePos();
	Vector3 myPt = m_pTransform->GetPosition();

	RECT realRange;

	SetRect(&realRange, m_rcRange.left + myPt.x,
		m_rcRange.top + myPt.y,
		m_rcRange.right + myPt.x,
		m_rcRange.bottom + myPt.y);

	if (m_pRenderer->CompareRenderType(SCROLL))
		CAMERA.TranslateVector(&mousePt, &mousePt);

	return (bool)(IntersectPointInRect(&realRange, &mousePt));
}
