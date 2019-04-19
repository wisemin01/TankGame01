#pragma once
#include "CSingleton.h"

class CGameObject;
class CCameraManager :
	public CSingleton<CCameraManager>
{
	friend class CResourceManager;
private:
	Vector3 m_vPosition;
	Vector3 m_vScale;
	Vector3 m_vOffset;

	float m_fSpeed = 3;
	float m_fShakePower = 0;
	float m_fShakeTime = 0;
	float m_fShakeDelay = 0;

	CGameObject* m_pTarget = nullptr;

	RECT m_rcRange;
	bool m_bIsLockOnRange = false;

public:
	CCameraManager();
	virtual ~CCameraManager();
	
	void Update();

	void SetTarget(CGameObject* target);
	CGameObject* GetTarget() { return m_pTarget; }

	void Init(Vector3 position = Vector3(0, 0, 0), Vector3 scale = Vector3(1, 1, 1));

	void Shake(float time, float power);

	Vector3 GetPosition() { return m_vPosition; }
	Vector3 GetScale() { return m_vScale; }
	float GetSpeed() { return m_fSpeed; }

	void SetPosition(Vector3 pos) { m_vPosition = pos; }
	void SetScale(Vector3 scale) { m_vScale = scale; }
	void SetSpeed(float speed) { m_fSpeed = speed; }

	void UseRange(float left, float top, float right, float bottom);
	void UnuseRange();

	void LockInMap(Vector3* target_position);

	Vector3& GetCameraOffset() { return m_vOffset; }
	void SetCameraOffset(Vector3 offset) { m_vOffset = offset; }

	void TranslateVector(Vector3 *pOut, CONST Vector3* p1);
};

#define CAMERA (*CCameraManager::Instance())