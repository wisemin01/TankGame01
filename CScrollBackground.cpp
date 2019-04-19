#include "DXUT.h"
#include "CScrollBackground.h"

#include "CTexture.h"

CScrollBackground::CScrollBackground()
{
}


CScrollBackground::~CScrollBackground()
{
}

void CScrollBackground::Init()
{
	AddComponent<CTransform>();
	AddComponent<CRenderer>();
}

void CScrollBackground::Update()
{
	m_iScroll -= DELTIME * m_fRed;

	m_fRenderX = (int)m_iScroll % (int)m_fWidth + m_vPivotPos.x;

	GetTransform()->SetPosition(m_fRenderX + m_fWidth, m_vPivotPos.y, 0);
}

void CScrollBackground::Render()
{
	RESOURCE.ApplyWorldTransform(Vector3(m_fRenderX, m_vPivotPos.y, 0), m_pTransform->GetScale(), m_pTransform->GetRotation());

	RESOURCE.Draw(m_pRenderer->m_pTexture, m_pRenderer->GetColor());
}

void CScrollBackground::Destroy()
{
}

void CScrollBackground::Setting(ResourceID key, Vector3 position, float red)
{
	CTexture* texture = RESOURCE.GetTexture(key);

	Vector3 pos = position + Vector3(texture->info.Width / 2.f, 0, 0);

	m_pTransform->SetPosition(pos);
	m_pRenderer->SetRenderType(SCREEN);
	m_pRenderer->SetTexture(texture);

	m_fRed = red;
	m_vPivotPos = pos;

	m_fWidth = m_pRenderer->m_pTexture->info.Width;
	m_fHeight = m_pRenderer->m_pTexture->info.Height;
}

void CScrollBackground::Setting(CTexture * texture, Vector3 position, float red)
{
	Vector3 pos = position + Vector3(texture->info.Width / 2.f, 0, 0);

	m_pTransform->SetPosition(pos);
	m_pRenderer->SetRenderType(SCREEN);
	m_pRenderer->SetTexture(texture);

	m_fRed = red;
	m_vPivotPos = pos;

	m_fWidth = m_pRenderer->m_pTexture->info.Width;
	m_fHeight = m_pRenderer->m_pTexture->info.Height;
}
