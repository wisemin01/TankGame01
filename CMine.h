#pragma once
#include "CObject.h"


class CMine :
	public CGameObject
{
private:
	bool m_bIsDroping;
public:
	CMine();
	virtual ~CMine();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Destroy() override;

	void Place(float x);
	void Drop(Vector3 position);

	void OnCollision(CollideBox* other);

	virtual void Kill() override;
	void NoneExplodeKill() { m_bIsLive = false; }

public:
	static void CreateMines(int count, int start_x, int depth_min, int depth_max);
};

