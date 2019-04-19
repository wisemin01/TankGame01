#include "DXUT.h"
#include "CExplode.h"

#include "CTexture.h"

CExplode::CExplode()
{
}


CExplode::~CExplode()
{
}

void CExplode::Init()
{
	AC(CTransform);
	AC(CRenderer);

	m_pRenderer->SetRenderLayer(12);
}

void CExplode::Update()
{
	if (m_pRenderer->GetNowFrame() == m_pRenderer->m_pTexture->GetSize())
	{
		m_bIsDisplay = false;
		Kill();
	}
}

void CExplode::Destroy()
{
}

void CExplode::Setup(Vector3 pos, ResourceID rsid, float delay)
{
	m_pTransform->SetPosition(pos);
	m_pRenderer->SetTexture(rsid);
	m_pRenderer->SetFrame(0, m_pRenderer->m_pTexture->GetSize(), delay);
}
