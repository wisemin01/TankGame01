#include "DXUT.h"
#include "CRigidbody.h"

#include "CObject.h"
#include "CTransform.h"
#include "CPixelCollider.h"

Vector3 CRigidbody::g_vGravity = Vector3(0, 9.8f, 0);

CRigidbody::CRigidbody()
{
}


CRigidbody::~CRigidbody()
{
}

void CRigidbody::Init()
{
	GO->m_pRigidbody = this;
}

void CRigidbody::Update()
{
	if (m_bIsUseGravity)
		AddForce(g_vGravity, m_fMass);

	PhysicsCalculate();
}

void CRigidbody::Destroy()
{
	if (GO->m_pRigidbody == this)
		GO->m_pRigidbody = nullptr;
}

void CRigidbody::AddForce(float x, float y)
{
	m_vForce.x += x;
	m_vForce.y += y;
}

void CRigidbody::AddForce(float x, float y, float power)
{
	m_vForce.x += x * power;
	m_vForce.y += y * power;
}

void CRigidbody::AddForce(Vector3 force, float power)
{
	m_vForce += force * power;
}
             
void CRigidbody::PhysicsCalculate()
{
	m_vVelocity += m_vForce * DXUTGetElapsedTime();
	m_vForce = V3ZERO;

	GO->GetTransform()->AddPosition(m_vVelocity);

	m_vVelocity.x *= m_vAttenuation.x;
	m_vVelocity.y *= m_vAttenuation.y;
}
