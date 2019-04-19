#include "DXUT.h"
#include "CCollider.h"

#include "CObject.h"
#include "CTexture.h"

CCollider::CCollider()
{
}


CCollider::~CCollider()
{
}

void CCollider::Init()
{
	GO->m_pCollider = this;
}

void CCollider::Update()
{
}

void CCollider::Destroy()
{
	Clear();

	if (GO->m_pCollider == this)
		GO->m_pCollider = nullptr;
}

void CCollider::AddCollider(float width, float height, Vector3 center, std::function<void(CollideBox*)> func, bool isTrigger)
{
	CollideBox* new_collider = new CollideBox;

	new_collider->Create(width, height, center, func);
	new_collider->RegisterOwner(GO);
	new_collider->m_bIsTrigger = isTrigger;

	m_pColliderList.push_back(new_collider);
	COLLISION.Register(new_collider);
}

void CCollider::AddColliderAsTexture(CTexture * texture, Vector3 center, std::function<void(CollideBox*)> func, bool isTrigger)
{
	CollideBox* new_collider = new CollideBox;

	Vector3 scale = GO->GetTransform()->GetScale();

	float w, h;
	w = texture->GetImage(0)->info.Width * scale.x;
	h = texture->GetImage(0)->info.Height * scale.y;

	new_collider->Create(w, h, center, func);
	new_collider->RegisterOwner(GO);
	new_collider->m_bIsTrigger = isTrigger;

	m_pColliderList.push_back(new_collider);
	COLLISION.Register(new_collider);
}

void CCollider::RemoveCollider(int index)
{
	if (m_iEndIndex <= index)
		return;

	auto iter = m_pColliderList.begin();

	for (int i = 0; i < index; i++)
	{
		iter++;
	}

	COLLISION.UnRegister(*iter);
	SAFE_DELETE(*iter);

	m_pColliderList.erase(iter);
}

void CCollider::Clear()
{
	for (auto iter : m_pColliderList)
	{
		COLLISION.UnRegister(iter);
		SAFE_DELETE(iter);
	}
	m_pColliderList.clear();
}

RECT CollideBox::GetWorldRange() const
{
	RECT rcWorld;
	Vector3 prTrans = GetWorldPosition();

	SetRect(&rcWorld, left + prTrans.x, top + prTrans.y,
		right + prTrans.x, bottom + prTrans.y);

	return rcWorld;
}

Vector3 CollideBox::GetWorldPosition() const
{
	return m_pOwner->GetTransform()->GetPosition() + m_vCenter;
}

void CollideBox::Create(float width, float height, Vector3 center, std::function<void(CollideBox*)> func)
{
	left = -width / 2.f;
	right = width / 2.f;
	top = -width / 2.f;
	bottom = width / 2.f;

	m_vCenter = center;
	m_pLinkFunc = func;
}
