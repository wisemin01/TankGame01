#pragma once
#include "CComponent.h"

enum class FLIP_MODE
{
	LEFT = -1,
	RIGHT = 1
};

class CTransform :
	public CComponent
{
private:
	Vector3 m_vPosition;
	Vector3 m_vScale;
	
	float m_fRot = 0;
	FLIP_MODE m_iFlip = FLIP_MODE::RIGHT;
public:
	CTransform();
	virtual ~CTransform();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Destroy() override;

	Vector3 GetPosition() { return m_vPosition; }
	void SetPosition(float x, float y, float z = 0.0f) { m_vPosition = Vector3(x, y, z); }
	void SetPosition(Vector3 pos) { m_vPosition = pos; }

	Vector3* GetPositionPtr() { return &m_vPosition; }
	float* GetRotationPtr() { return &m_fRot; }

	void AddPosition(float x, float y, float z = 0.0f) { m_vPosition += Vector3(x, y, z); }
	void AddPosition(Vector3 position) { m_vPosition += position; }
	void AddPositionAsPixelCollision(float x, float y);

	Vector3 GetScale() { return m_vScale; }
	Vector3* GetScalePtr() { return &m_vScale; }
	void SetScale(float x, float y, float z = 0.0f) { m_vScale = Vector3(x, y, z); }
	void SetScale(Vector3 scale) { m_vScale = scale; }

	float GetRotation() { return m_fRot; }
	void SetRotation(float r) { m_fRot = r; }

	FLIP_MODE GetFlip() { return m_iFlip; }
	void SetFlip(FLIP_MODE mode) { m_iFlip = mode; }

	void ApplyTransform(Vector3 offset = V3ZERO);
};

