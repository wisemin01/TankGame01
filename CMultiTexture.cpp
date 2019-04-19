#include "DXUT.h"
#include "CMultiTexture.h"

#include "CSingleTexture.h"

CMultiTexture::CMultiTexture()
{
}


CMultiTexture::~CMultiTexture()
{
	for (auto iter : m_TextureVec)
	{
		SAFE_DELETE(iter);
	}
	m_TextureVec.clear();
}

CTexture* CMultiTexture::GetImage(int count)
{
	if (count == -1)
		return this;
	else
		return m_TextureVec[count];
}

void CMultiTexture::AddImage(const string& path, int count)
{
	char string[128];

	for (int i = 1; i <= count; i++)
	{
		sprintf(string, path.c_str(), i);

		CTexture* tex = new CSingleTexture();

		tex->AddImage(string);
		m_TextureVec.emplace_back(tex);
	}
}

int CMultiTexture::GetSize()
{
	return m_TextureVec.size();
}
