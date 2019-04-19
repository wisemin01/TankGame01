#include "DXUT.h"
#include "CMultiPixelCollider.h"

#include "CTexture.h"

#include "CObject.h"
#include "CTransform.h"
#include "CRigidbody.h"
#include "CMapPlacer.h"

#define DEPTH (20.0f)

CMultiPixelCollider::CMultiPixelCollider()
{
}


CMultiPixelCollider::~CMultiPixelCollider()
{
}

void CMultiPixelCollider::Init()
{
	GO->m_pPixelCollider = this;
	m_iMapDataArray = nullptr;
}

void CMultiPixelCollider::Update()
{
	CalcOnHeightMap(
		GO->m_pTransform->GetPositionPtr(),
		GO->m_pRigidbody->GetForcePtr());
}

void CMultiPixelCollider::Destroy()
{
	SAFE_DELETE_ARRAY(m_iMapDataArray);
	SAFE_DELETE_ARRAY(m_pHeightArray);

	if (GO->m_pPixelCollider == this)
		GO->m_pPixelCollider = nullptr;
}

void CMultiPixelCollider::CreatePixelCollider(CTexture * minimapTex, int minimapMaxCnt, int mapCount)
{
	// ���� ������ ����� ���´�.
	// m_iMapKindCount = minimapTex->GetSize() �̰ɷ� ���͵� �����ϴ�.
	m_iMapKindCount = minimapMaxCnt;

	// �� ���� ����
	m_iMapCount = mapCount;

	// �迭�� �̹� �����Ѵٸ� �����ϰ� ���� ������ŭ ���Ҵ��Ѵ�.
	ResizeArray(m_iMapDataArray, m_iMapCount);

	// ������ ���� �迭�� ��ġ��Ų��.
	for (int i = 0; i < m_iMapCount; i++)
	{
		m_iMapDataArray[i] = RandomNumber(0, m_iMapKindCount - 1);
	}
	
	// ���̿� �ʺ� ���ؿ��� �ؽ��Ĵ� 0�� ����.
	float m_fWidth = minimapTex->GetImage(0)->info.Width;
	float m_fHeight = minimapTex->GetImage(0)->info.Height;

	// �迭�� ũ�⸦ ( ���� ���� * ���� �ʺ� ) ������ ����
	m_iArraySize = m_iMapCount * m_fWidth;

	// ���� ���� ���Ҵ��Ѵ�.
	ResizeArray(m_pHeightArray, m_iArraySize);

	for (int i = 0; i < m_iMapCount; i++)
	{
		// �̹����� m_iMapDataArray �� �̸� ��ġ�� �״� ������ ��ȣ.
		CreateHeightMap(minimapTex->GetImage(m_iMapDataArray[i]), m_pHeightArray, i * m_fWidth);
	}
}

void CMultiPixelCollider::CreateMapsAsPixelMap(CTexture * realMapTex, int renderLayer)
{
	Instantiate(SPAWNER, CMapPlacer)->CreateMaps(realMapTex, m_iMapDataArray, m_iMapCount, renderLayer);
}

void CMultiPixelCollider::CreateCheckPoints(CTexture * minimapTex, int renderLayer)
{
	Instantiate(SPAWNER, CMapPlacer)->CreateCheckPoints(minimapTex, m_iMapDataArray, m_iMapCount, renderLayer);
}

bool CMultiPixelCollider::IsCollisionOnFloor(Vector3 position)
{
	int x = (int)position.x;
	int y = (int)position.y;

	// ����ó��
	if (IsOutOfRange(x))
		return false;

	if (m_pHeightArray[x].first <= y && m_pHeightArray[x].second == TYPE_FLOOR)
	{
		return true;
	}

	return false;
}

bool CMultiPixelCollider::IsCollision(Vector3 position)
{
	int x = (int)position.x;
	int y = (int)position.y;

	// ����ó��
	if (IsOutOfRange(x))
		return false;

	if (m_pHeightArray[x].first <= y && m_pHeightArray[x].second != TYPE_NONE)
	{
		return true;
	}

	return false;
}

Vector3 CMultiPixelCollider::GetNormalVector(Vector3 position)
{
	if (IsCollisionOnFloor(position))
	{
		Vector3 vLine = GetLineVector(position);

		Vector3 vNormal = Vector3(vLine.y, -vLine.x, 0);

		if (vNormal.y > 0)
			vNormal *= -1;

		return vNormal;
	}

	return Vector3(0.0f, 0.0f, 0.0f);
}

Vector3 CMultiPixelCollider::GetLineVector(Vector3 position)
{
	float leftX = position.x - m_fDepth;
	float rightX = position.x + m_fDepth;

	// ����ó��
	if (IsOutOfRange(leftX) || IsOutOfRange(rightX))
		return Vector3(0.0f, 0.0f, 0.0f);

	Vector3 left(leftX, m_pHeightArray[(int)leftX].first, 0);
	Vector3 right(rightX, m_pHeightArray[(int)rightX].first, 0);
	Vector3 line_vec = right - left;

	D3DXVec3Normalize(&line_vec, &line_vec);

	return line_vec;
}

Vector3 CMultiPixelCollider::GetSlipVector(Vector3 position, Vector3 force)
{
	// ������� ����.
	return Vector3(0.0f, 0.0f, 0.0f);
}

void CMultiPixelCollider::CalcOnHeightMap(Vector3 * position, Vector3 * force)
{
	// �浹�ߴٸ�
	if (IsCollisionOnFloor(*position))
	{
		if (IsOutOfRange(position->x))
			return;

		float y = m_pHeightArray[(INT)position->x].first;

		*force += GetNormalVector(*position) * 75;

		// ���� �Ʒ��� ���Ѵٸ� �ʱ�ȭ.
		if (force->y > y)
			force->y = 0;

		// y ��ǥ�� �ʺ��� �Ʒ���� ���� y��ǥ�� �缳��.
		if (position->y >= y)
			Lerp(position->y, y, DELTIME * 20.0f);

		m_bIsOnFloor = true;
	}
	else if (IsCollisionOnFloor(*position + Vector3(0, 10, 0)))
	{
		m_bIsOnFloor = true;
	}
	else
		m_bIsOnFloor = false;
}

void CMultiPixelCollider::GetLineRotation(const Vector3 & position, float * rot)
{
	if (!IsCollisionOnFloor(position)) {
		Lerp(*rot, 0.0f, DELTIME * 1.0f);
		return;
	}

	Vector3 v = GetLineVector(position);

	if (v == Vector3(0, 0, 0))
		return;

	Lerp(*rot, atan2f(v.y, v.x), DELTIME * 8.0f);
}
