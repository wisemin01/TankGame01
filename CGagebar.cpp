#include "DXUT.h"
#include "CGagebar.h"
#include "CTexture.h"

CGagebar::CGagebar()
{
}


CGagebar::~CGagebar()
{
}

void CGagebar::Init()
{
	AC(CTransform);
	AC(CRenderer);

	m_pRenderer->SetRenderLayer(30);

	m_pTransform->SetPosition(WINSIZEX / 2.f, 670, 0);

	m_pGageBar = GETTEXTURE("GAGEBAR");
	m_pIcon = GETTEXTURE("MINITANK");
}

void CGagebar::Update()
{
	float w = m_pGageBar->GetImage(1)->info.Width;

	SetRect(&m_rcRange, 0, 0, (*m_pPercent) * w,
		m_pGageBar->GetImage(1)->info.Height);

	m_vIconPos = Vector3(m_pTransform->GetPosition().x - w / 2.f +
		w * (*m_pPercent), m_pTransform->GetPosition().y, 0);
}

void CGagebar::Render()
{
	RESOURCE.SetRenderType(SCREEN);

	RESOURCE.ApplyWorldTransform(m_pTransform->GetPosition(), m_pTransform->GetScale(), 0);
	RESOURCE.Draw(m_pGageBar->GetImage(0), D3DXCOLOR(255, 255, 255, 255));

	RESOURCE.ApplyWorldTransform(m_pTransform->GetPosition(), m_pTransform->GetScale(), 0);
	RESOURCE.RectDraw(m_pGageBar->GetImage(1), m_rcRange, D3DXCOLOR(255, 255, 255, 255));

	RESOURCE.ApplyWorldTransform(m_vIconPos, Vector3(1, 1, 1), 0);
	RESOURCE.Draw(m_pIcon, D3DXCOLOR(255, 255, 255, 255));
}

void CGagebar::Destroy()
{
}

void CGagebar::Setup(float * percent)
{
	m_pPercent = percent;
}
