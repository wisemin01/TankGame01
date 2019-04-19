#include "DXUT.h"
#include "CRenderer.h"

#include "CObject.h"
#include "CTransform.h"
#include "CTexture.h"

CRenderer::CRenderer()
{
}


CRenderer::~CRenderer()
{
}

void CRenderer::Init()
{
	GO->m_pRenderer = this;
	SetColor(255, 255, 255, 255);

	m_Frame.SetFrame(0, 0, 0);
}

void CRenderer::Update()
{
	m_Frame();
}

void CRenderer::Render()
{
	if (!m_pTexture)
		return;

	RESOURCE.SetRenderType(m_iRenderType);

	GetGameObject()->GetTransform()->ApplyTransform(m_vOffset);

	RESOURCE.CenterDraw(m_pTexture->GetImage(m_Frame.m_iCurrent), m_vCenter, D3DXCOLOR(m_ColorValue));
}

void CRenderer::Destroy()
{
	if (GO->m_pRenderer == this)
		GO->m_pRenderer = nullptr;
}

int CRenderer::Width(int index)
{
	return m_pTexture->GetImage(index)->info.Width;
}

int CRenderer::Height(int index)
{
	return m_pTexture->GetImage(index)->info.Height;
}

void CRenderer::SetFrame(int start, int end, DWORD delay)
{
	m_Frame.SetFrame(start, end, delay);
}

void CRenderer::SetFrameAsFixedDelay(int start, int end)
{
	m_Frame.m_iStartFrame = start;
	m_Frame.m_iMaxFrame = end;
}

void CRenderer::SetColor(int a, int r, int g, int b)
{
	m_ColorValue.a = a;
	m_ColorValue.r = r;
	m_ColorValue.g = g;
	m_ColorValue.b = b;
}

void CRenderer::SetAlpha(int a)
{
	if (a > 255)
		a = 255;
	else if (a < 0)
		a = 0;

	m_ColorValue.a = a;
}

void CRenderer::SetRed(int r)
{
	if (r > 255)
		r = 255;
	else if (r < 0)
		r = 0;

	m_ColorValue.r = r;
}

void CRenderer::SetGreen(int g)
{
	if (g > 255)
		g = 255;
	else if (g < 0)
		g = 0;

	m_ColorValue.g = g;
}

void CRenderer::SetBlue(int b)
{
	if (b > 255)
		b = 255;
	else if (b < 0)
		b = 0;

	m_ColorValue.b = b;
}

void CRenderer::SetTexture(ResourceID key, int count)
{
	m_pTexture = RESOURCE.GetTexture(key, count);
	m_vCenter = Vector3(m_pTexture->GetImage(0)->info.Width / 2.f, m_pTexture->GetImage(0)->info.Height / 2.f, 0);
}

void CRenderer::SetTexture(CTexture * texture)
{
	m_pTexture = texture;
	m_vCenter = Vector3(texture->GetImage(0)->info.Width / 2.f, texture->GetImage(0)->info.Height / 2.f, 0);
}

D3DCOLOR CRenderer::GetRealColor()
{
	return D3DXCOLOR(m_ColorValue);
}

void CRenderer::operator()(CTexture * texture)
{
	m_pTexture = texture;
}

void CRenderer::operator()(ResourceID rsid)
{
	m_pTexture = RESOURCE.GetTexture(rsid);
}
