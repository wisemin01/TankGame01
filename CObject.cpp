#include "DXUT.h"
#include "CObject.h"

#include "CComponent.h"
#include "CRenderer.h"
#include "CTransform.h"


void CGameObject::Init()
{
}

void CGameObject::Update()
{
}

void CGameObject::Render()
{
}

void CGameObject::Destroy()
{
}

void CGameObject::ComponentUpdate()
{
	for (auto iter : m_ComponentMap)
	{
		if (iter.second->GetActive())
			iter.second->Update();
	}
}

void CGameObject::ComponentRender()
{
	for (auto iter : m_ComponentMap)
	{
		if (iter.second->GetActive())
			iter.second->Render();
	}
}

void CGameObject::ComponentDestroy()
{
	for (auto iter : m_ComponentMap)
	{
		iter.second->Destroy();
		SAFE_DELETE(iter.second);
	}
	m_ComponentMap.clear();
}

bool CGameObject::CompareLayer(CGameObject * _1, CGameObject * _2)
{
	if (_1->GetRenderer()->GetRenderLayer() < _2->GetRenderer()->GetRenderLayer())
	{
		return true;
	}
	else
		return false;
}

bool CGameObject::CompareY(CGameObject * _1, CGameObject * _2)
{
	if (_1->GetRenderer()->GetRenderLayer() == _2->GetRenderer()->GetRenderLayer()) {
		return _1->GetTransform()->GetPosition().y < _2->GetTransform()->GetPosition().y;
	}
	else
		return false;
}
