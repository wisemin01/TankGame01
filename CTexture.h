#pragma once
class CTexture
{
public:
	LPDIRECT3DTEXTURE9 texture;
	D3DXIMAGE_INFO info;
public:
	CTexture();
	virtual ~CTexture();

	virtual CTexture* GetImage(int count = -1) PURE;
	virtual void AddImage(const string& path, int count = 0) PURE;

	virtual int GetSize() PURE;
};

