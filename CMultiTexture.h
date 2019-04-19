#pragma once
#include "CTexture.h"
class CMultiTexture :
	public CTexture
{
private:
	vector<CTexture*> m_TextureVec;
public:
	CMultiTexture();
	virtual ~CMultiTexture();

	virtual CTexture* GetImage(int count = -1) override;
	virtual void AddImage(const string& path, int count = 0) override;

	virtual int GetSize() override;
};

