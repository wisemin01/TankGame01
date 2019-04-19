#include "DXUT.h"
#include "CSingleTexture.h"


CSingleTexture::CSingleTexture()
{
}


CSingleTexture::~CSingleTexture()
{
	SAFE_RELEASE(texture);
}

CTexture* CSingleTexture::GetImage(int count)
{
	return this;
}

void CSingleTexture::AddImage(const string& path, int count)
{
	D3DXCreateTextureFromFileExA(DXUTGetD3D9Device(), path.c_str(),
		D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 0, 0, D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(10, 10, 10),
		&info, 0, &texture);
}

int CSingleTexture::GetSize()
{
	return 1;
}
