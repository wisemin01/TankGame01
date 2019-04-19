#include "DXUT.h"
#include "CBackground.h"

#include "CTexture.h"

CBackground::CBackground()
{
}


CBackground::~CBackground()
{
}

void CBackground::Init()
{
	AddComponent<CTransform>();
	AddComponent<CRenderer>();
}

void CBackground::Update()
{
}

void CBackground::Render()
{
}

void CBackground::Destroy()
{
}

void CBackground::Setting(ResourceID key, Vector3 position, int layer)
{
	m_pRenderer->SetTexture(key);
	m_pRenderer->SetRenderType(SCROLL);
	m_pRenderer->SetRenderLayer(4);
	m_pTransform->SetPosition(position + Vector3(m_pRenderer->m_pTexture->info.Width / 2.f,
		m_pRenderer->m_pTexture->info.Height / 2.f, 0));
}

void CBackground::Setting(CTexture * texture, Vector3 position, int layer)
{
	m_pRenderer->SetTexture(texture);
	m_pRenderer->SetRenderType(SCROLL);
	m_pRenderer->SetRenderLayer(layer);
	m_pTransform->SetPosition(position + Vector3(m_pRenderer->m_pTexture->info.Width / 2.f,
		m_pRenderer->m_pTexture->info.Height / 2.f, 0));
}
