#include "DXUT.h"
#include "CMine.h"

#include "CExplode.h"

CMine::CMine()
{
}


CMine::~CMine()
{
}

void CMine::Init()
{
	AC(CTransform);
	AC(CRenderer);
	AC(CCollider);

	SetTag("MINE");
}

void CMine::Update()
{
	if (m_bIsDroping)
	{
		if (COLLISION.IsOnLoad(m_pTransform->GetPosition()))
		{
			Place(m_pTransform->GetPosition().x);
			m_pRigidbody->SetActive(false);
		}
	}
}

void CMine::Destroy()
{
}

void CMine::Place(float x)
{
	m_pTransform->SetPosition(x, WINSIZEY, 0);
	m_pTransform->SetScale(Vector3(0.5f, 0.5f, 0.5f));
	COLLISION.SetObjectOnPixelMap(this, -45);

	if (m_pTransform->GetPosition().y == 0)
		NoneExplodeKill();

	m_pRenderer->SetTexture("MINE");
	m_pRenderer->SetRenderLayer(11);
	m_pRenderer->SetFrame(0, 5, 200);
	m_pCollider->AddColliderAsTexture(m_pRenderer->m_pTexture, V3ZERO, [&](CollideBox* other) {OnCollision(other); });

	m_bIsDroping = false;
}

void CMine::Drop(Vector3 position)
{
	AC(CRigidbody);

	m_pTransform->SetPosition(position);
	m_pTransform->SetScale(Vector3(0.5f, 0.5f, 0.5f));

	m_pRenderer->SetTexture("MINE");
	m_pRenderer->SetRenderLayer(11);
	m_pRenderer->SetFrame(0, 5, 200);
	m_pCollider->AddColliderAsTexture(m_pRenderer->m_pTexture, V3ZERO, [&](CollideBox* other) {OnCollision(other); });

	m_bIsDroping = true;
}

void CMine::OnCollision(CollideBox * other)
{
	if (other->GO->CompareTag("PLAYER"))
	{
		other->GO->Kill();
		Kill();
	}
	else if (other->GO->CompareTag("BULLET"))
	{
		Kill();
	}
}

void CMine::Kill()
{
	m_bIsLive = false;

	Instantiate(EFFECT, CExplode)->Setup(m_pTransform->GetPosition(), "PLASMA", 100);
	CAMERA.Shake(250, 5);
}

void CMine::CreateMines(int count, int start_x, int depth_min, int depth_max)
{
	int x_step = start_x;

	for (int i = 0; i < count; i++)
	{
		Instantiate(ENEMY, CMine)->Place(x_step);

		x_step += RandomNumber(depth_min, depth_max);
	}
}
