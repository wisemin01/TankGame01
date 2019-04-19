#include "DXUT.h"
#include "CTransform.h"

#include "CObject.h"

CTransform::CTransform()
	: m_vPosition(Vector3(0, 0, 0)), m_vScale(Vector3(1.0f, 1.0f, 1.0f))
{

}


CTransform::~CTransform()
{
}

void CTransform::Init()
{
	GO->m_pTransform = this;
}

void CTransform::Update()
{
}

void CTransform::Destroy()
{
	if (GO->m_pTransform == this)
		GO->m_pTransform = nullptr;
}

void CTransform::AddPositionAsPixelCollision(float x, float y)
{
	/*Vector3 end = m_vPosition + Vector3(x, y, 0);

	if (COLLISION.IsCollision(end))
	{
		;
	}
	else
	{
		m_vPosition = end;
	}*/
}

void CTransform::ApplyTransform(Vector3 offset)
{
	Vector3 f_scale = m_vScale;
	f_scale.x *= (INT)m_iFlip;

	RESOURCE.ApplyWorldTransform(m_vPosition + offset, f_scale, m_fRot);
}
