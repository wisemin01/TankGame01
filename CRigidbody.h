#pragma once
#include "CComponent.h"


class CRigidbody :
	public CComponent
{
private:
	Vector3 m_vForce		= V3ZERO;
	Vector3 m_vVelocity		= V3ZERO;
	Vector3 m_vAttenuation = Vector3(0.98f, 0.98f, 0);

	bool m_bIsUseGravity	= true;

	float m_fMass			= 1.0f;

public:
	CRigidbody();
	virtual ~CRigidbody();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Destroy() override;

	void AddForce(float x, float y);
	void AddForce(float x, float y, float power);
	void AddForce(Vector3 force, float power = 1.0f);

	void SetMass(float mass) { m_fMass = mass; }
	void SetIsUseGravity(bool use_gravity) { m_bIsUseGravity = use_gravity; }
	void SetAttenuation(float x, float y) { m_vAttenuation = Vector3(x, y, 0); }
	void SetVelocity(float x, float y, float z = 0.0f) { m_vVelocity = Vector3(x, y, z); }

	Vector3 &GetVelocity() { return m_vVelocity; }
	Vector3 &GetForce() { return m_vForce; }
	Vector3 &GetAttenuation() { return m_vAttenuation; }
	Vector3* GetForcePtr() { return &m_vForce; }

	float GetMass() { return m_fMass; }
	bool GetIsUseGravity() { return m_bIsUseGravity; }

	void PhysicsCalculate();

	float GetTotalForce() { return m_vForce.x + m_vForce.y + m_vForce.z; }

public:
	static Vector3 g_vGravity;

	static void SetGravity(Vector3 gravity) { g_vGravity = gravity; }
};
