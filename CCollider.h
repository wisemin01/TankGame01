#pragma once
#include "CComponent.h"

struct CollideBox : public RECT
{
	std::function<void(CollideBox*)> m_pLinkFunc;

	CGameObject* m_pOwner = nullptr;
	Vector3 m_vCenter = Vector3(0, 0, 0);

	bool m_bIsTrigger = false;

	RECT GetWorldRange() const;
	Vector3 GetWorldPosition() const;

	inline float Width() { return abs(right - left); }
	inline float Height() { return abs(bottom - top); }

	inline void RegisterOwner(CGameObject* owner) { m_pOwner = owner; }

	void Create(float width, float height, Vector3 center, std::function<void(CollideBox*)> func);

	CGameObject* GetGameObject() { return m_pOwner; }
};


class CCollider :
	public CComponent
{
private:
	std::vector<CollideBox*> m_pColliderList;
	int m_iEndIndex = 0;
public:
	CCollider();
	virtual ~CCollider();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Destroy() override;

	void AddCollider(float width, float height, Vector3 center, std::function<void(CollideBox*)> func, bool isTrigger = false);
	void AddColliderAsTexture(CTexture* texture, Vector3 center, std::function<void(CollideBox*)> func, bool isTrigger = false);
	void RemoveCollider(int index);

	void Clear();
};

