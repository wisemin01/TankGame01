#pragma once
#include "CSingleton.h"

class CTexture;
class CResourceManager :
	public CSingleton<CResourceManager>
{
private:
	map<string, CTexture*> m_TextureMap;

	LPD3DXSPRITE m_pSprite;

	UINT m_iRenderType = SCROLL;
public:
	CResourceManager();
	virtual ~CResourceManager();

	CTexture* AddTexture(ResourceID key, const string& path, int count = 0);
	CTexture* GetTexture(ResourceID key, int count = -1);

	void Clear();

	void Begin(UINT d3dxsprite_type);
	void End();

	void Reset();
	void Lost();

	void Draw(CTexture* texture, D3DXCOLOR color);
	void CenterDraw(CTexture* texture, const Vector3& center, D3DXCOLOR color);
	void RectDraw(CTexture* texture, const RECT& rc, D3DXCOLOR color);
	void SetRenderType(UINT render_type);

	void ApplyWorldTransform(Vector3 pos, Vector3 size, float rot);

	void DrawFont(const string& str, const string& fontPath, Vector3 pos, int fontSize, D3DXCOLOR color);

};

#define RESOURCE (*CResourceManager::Instance())

#define ADDTEXTURE RESOURCE.AddTexture
#define GETTEXTURE RESOURCE.GetTexture