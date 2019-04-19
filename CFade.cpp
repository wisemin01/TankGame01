#include "DXUT.h"
#include "CFade.h"


CFade::CFade()
{
}


CFade::~CFade()
{
}

void CFade::Init()
{
	AC(CTransform);
	AC(CRenderer);
}

void CFade::Update()
{
	if (m_iFadeCount <= 0)
	{
		Kill();
		return;
	}

	if (m_eType == FADE_TO_255)
	{
		m_pRenderer->SetAlpha(m_pRenderer->GetAlpha() + m_fSpeed);

		if (m_pRenderer->GetAlpha() >= 255) {

			m_iFadeCount--;
			m_eType = FADE_TO_0;

			m_pToChange255();
		}
	}
	else if (m_eType == FADE_TO_0)
	{
		m_pRenderer->SetAlpha(m_pRenderer->GetAlpha() - m_fSpeed);

		if (m_pRenderer->GetAlpha() <= 0) {

			m_iFadeCount--;
			m_eType = FADE_TO_255;

			m_pToChange0();
		}
	}
}

void CFade::Destroy()
{
}

void CFade::Fade(FADE_TYPE type, int fadeCount, float speed)
{
	m_eType = type;
	m_iFadeCount = fadeCount;
	m_fSpeed = speed;

	m_pRenderer->SetAlpha(type == FADE_TO_255 ? 0 : 255);
	m_pRenderer->SetTexture("BLACK");
	m_pRenderer->SetRenderLayer(100);
	m_pRenderer->SetRenderType(SCREEN);

	m_pTransform->SetPosition(V3CENTER);
}

void CFade::AddFunc(FADE_TYPE type, const std::function<void()>& func)
{
	if (type == FADE_TO_255)
		m_pToChange255 = func;
	if (type == FADE_TO_0)
		m_pToChange0 = func;
}
