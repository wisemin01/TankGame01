#include "DXUT.h"
#include "CStateTexture.h"


CStateTexture::CStateTexture()
{
	m_pAttack = nullptr;
	m_pIdle = nullptr;
	m_pMove = nullptr;
}


CStateTexture::~CStateTexture()
{
}

void CStateTexture::operator()(ResourceID key, ResourceID path, int frameCount)
{
	m_pAttack = ADDTEXTURE(key+"_A", path + "/A/(%d).png", frameCount);
	m_pIdle = ADDTEXTURE(key + "_I", path + "/I/(%d).png", frameCount);
	m_pMove = ADDTEXTURE(key + "_M", path + "/M/(%d).png", frameCount);
}

void CStateTexture::Get(ResourceID key)
{
	m_pAttack = GETTEXTURE(key + "_A");
	m_pIdle = GETTEXTURE(key + "_I");
	m_pMove = GETTEXTURE(key + "_M");
}
