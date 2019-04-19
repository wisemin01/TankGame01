#include "DXUT.h"
#include "CResourceManager.h"

#include "CSingleTexture.h"
#include "CMultiTexture.h"

CResourceManager::CResourceManager()
{
	D3DXCreateSprite(DXUTGetD3D9Device(), &m_pSprite);
}


CResourceManager::~CResourceManager()
{
	Clear();

	SAFE_RELEASE(m_pSprite);
}

CTexture* CResourceManager::AddTexture(ResourceID key, const string & path, int count)
{
	auto find = m_TextureMap.find(key);

	if (find == m_TextureMap.end())
	{
		CTexture* tex = nullptr;

		if (count == 0)
			tex = new CSingleTexture;
		else
			tex = new CMultiTexture;

		tex->AddImage(path, count);

		m_TextureMap.insert(make_pair(key, tex));

		return tex;
	}
	else
	{
		return find->second;
	}
}

CTexture* CResourceManager::GetTexture(ResourceID key, int count)
{
	return m_TextureMap[key]->GetImage(count);
}

void CResourceManager::Clear()
{
	for (auto iter : m_TextureMap)
	{	
		SAFE_DELETE(iter.second);
	}
	m_TextureMap.clear();
}

void CResourceManager::Begin(UINT d3dxsprite_type)
{
	m_pSprite->Begin(d3dxsprite_type);
}

void CResourceManager::End()
{
	m_pSprite->End();
}

void CResourceManager::Reset()
{
	m_pSprite->OnResetDevice();
}

void CResourceManager::Lost()
{
	m_pSprite->OnLostDevice();
}

void CResourceManager::Draw(CTexture * texture, D3DXCOLOR color)
{ 
	if (!texture->texture)
		return;

	DWORD dwC = D3DCOLOR_ARGB((int)(color.a),
		(int)(color.r),
		(int)(color.g),
		(int)(color.b));

	m_pSprite->Draw(texture->texture, nullptr,
		&Vector3(texture->info.Width / 2.f, texture->info.Height / 2.f, 0), nullptr, dwC);
}

void CResourceManager::CenterDraw(CTexture * texture, const Vector3 & center, D3DXCOLOR color)
{
	if (!texture->texture)
		return;

	DWORD dwC = D3DCOLOR_ARGB((int)(color.a),
		(int)(color.r),
		(int)(color.g),
		(int)(color.b));

	m_pSprite->Draw(texture->texture, nullptr,
		&center, nullptr, dwC);
}

void CResourceManager::RectDraw(CTexture * texture, const RECT & rc, D3DXCOLOR color)
{
	if (!texture->texture)
		return;

	DWORD dwC = D3DCOLOR_ARGB((int)(color.a),
		(int)(color.r),
		(int)(color.g),
		(int)(color.b));

	m_pSprite->Draw(texture->texture, &rc,
		&Vector3(texture->info.Width / 2.f, texture->info.Height / 2.f, 0), nullptr, dwC);
}

void CResourceManager::SetRenderType(UINT render_type)
{
	m_iRenderType = render_type;
}

void CResourceManager::ApplyWorldTransform(Vector3 pos, Vector3 size, float rot)
{
	D3DXMATRIX matWorld;

	D3DXMATRIX s, r, t;

	Vector3 cameraPos = CAMERA.m_vPosition;
	Vector3 cameraScale = CAMERA.m_vScale;

	if (m_iRenderType == SCROLL) {
		D3DXMatrixTranslation(&t, pos.x - cameraPos.x, pos.y - cameraPos.y, pos.z - cameraPos.z);
		D3DXMatrixRotationZ(&r, rot);
		D3DXMatrixScaling(&s, size.x * cameraScale.x, size.y * cameraScale.x, size.z * cameraScale.z);
	}
	else if (m_iRenderType == SCREEN)
	{
		D3DXMatrixTranslation(&t, pos.x, pos.y, pos.z);
		D3DXMatrixRotationZ(&r, rot);
		D3DXMatrixScaling(&s, size.x, size.y, size.z);
	}

	matWorld = s * r * t;

	m_pSprite->SetTransform(&matWorld);
}

void CResourceManager::DrawFont(const string & str, const string & fontPath, Vector3 pos, int fontSize, D3DXCOLOR color)
{
	LPD3DXFONT lpFont;
	D3DXMATRIX mat;

	D3DXCreateFontA(DXUTGetD3D9Device(), fontSize, 0, 0, 1, false, HANGUL_CHARSET, 0, 0, 0, fontPath.c_str(), &lpFont);

	D3DXMatrixTranslation(&mat, pos.x, pos.y, 0);

	m_pSprite->SetTransform(&mat);
	lpFont->DrawTextA(m_pSprite, str.c_str(), str.size(), NULL, DT_NOCLIP | DT_CENTER, color);
	SAFE_RELEASE(lpFont);
}
