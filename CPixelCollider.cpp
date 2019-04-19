#include "DXUT.h"
#include "CPixelCollider.h"

#include "CObject.h"
#include "CTexture.h"

#include "CMapPlacer.h"

#define BLOCK_COLOR D3DCOLOR_ARGB(255, 0, 0, 0)
#define RED_COLOR	D3DCOLOR_ARGB(255, 255, 0, 0)

CPixelCollider::CPixelCollider()
{
	m_pHeightArray = nullptr;
	m_fDepth = 5;
}


CPixelCollider::~CPixelCollider()
{
}

void CPixelCollider::Init()
{
	GO->m_pPixelCollider = this;
}

void CPixelCollider::Update()
{
	Vector3* pPos = GO->GetTransform()->GetPositionPtr();
	Vector3* pForce = GO->m_pRigidbody->GetForcePtr();

	CalcOnHeightMap(pPos, pForce);
}

void CPixelCollider::Destroy()
{
	SAFE_DELETE_ARRAY(m_pHeightArray);

	if (GO->m_pPixelCollider == this)
		GO->m_pPixelCollider = nullptr;
}

void CPixelCollider::RegisterMinimap(ResourceID map_id)
{
	RegisterMinimap(RESOURCE.GetTexture(map_id));
}

void CPixelCollider::RegisterMinimap(CTexture * map_texture)
{
	m_lpTexture = map_texture->texture;

	m_fWidth = map_texture->info.Width;
	m_fHeight = map_texture->info.Height;

	m_iArraySize = (INT)m_fWidth;

	ResizeArray(m_pHeightArray, m_iArraySize);
	CreateHeightMap(map_texture, m_pHeightArray, 0);
}

void CPixelCollider::CreatePixelCollider(CTexture * minimapTex, int minimapMaxCnt, int mapLength)
{
	RegisterMinimap(minimapTex);
}

void CPixelCollider::CreateMapsAsPixelMap(CTexture * realMapTex, int renderLayer)
{
	Instantiate(SPAWNER, CMapPlacer)->CreateMaps(realMapTex, nullptr, 0, renderLayer);
}

void CPixelCollider::CreateCheckPoints(CTexture * minimapTex, int renderLayer)
{
	Instantiate(SPAWNER, CMapPlacer)->CreateCheckPoints(minimapTex, nullptr, 0, renderLayer);
}

void CPixelCollider::UnRegisterMinimap()
{
}

bool CPixelCollider::IsCollisionOnFloor(Vector3 position)
{
	int x = (int)position.x;
	int y = (int)position.y;

	if (m_pHeightArray[x].first <= y && m_pHeightArray[x].second == TYPE_FLOOR)
	{
		return true;
	}

	return false;
}

bool CPixelCollider::IsCollision(Vector3 position)
{
	int x = (int)position.x;
	int y = (int)position.y;

	if (m_pHeightArray[x].first <= y && m_pHeightArray[x].second != TYPE_NONE)
	{
		return true;
	}

	return false;
}

Vector3 CPixelCollider::GetNormalVector(Vector3 position)
{
	Vector3 pos(position.x, position.y, 0);

	if (m_pHeightArray[(INT)pos.x].first > pos.y)
		return Vector3(0.0f, 0.0f, 0.0f);

	Vector3 line_vec = GetLineVector(position);

	Vector3 normal_vec = Vector3(line_vec.y, -line_vec.x, 0);

	if (normal_vec.y > 0)
		normal_vec *= -1;

	return normal_vec;
}

Vector3 CPixelCollider::GetLineVector(Vector3 position)
{
	Vector3 pos(position.x, position.y, 0);

	Vector3 left(pos.x - (INT)m_fDepth, m_pHeightArray[(INT)pos.x - (INT)m_fDepth].first, 0);
	Vector3 right(pos.x + (INT)m_fDepth, m_pHeightArray[(INT)pos.x + (INT)m_fDepth].first, 0);

	Vector3 line_vec = right - left;

	D3DXVec3Normalize(&line_vec, &line_vec);

	return line_vec;
}


Vector3 CPixelCollider::GetSlipVector(Vector3 position, Vector3 force)
{
	Vector3 line = GetLineVector(position);

	if (force.x > 0)
		line.x = abs(line.x);
	else
		line.x = -abs(line.x);

	force.x = line.x;

	return position + force;
}

void CPixelCollider::CalcOnHeightMap(Vector3 *position, Vector3 * force)
{
	if (IsCollisionOnFloor(*position))
	{
		if (position->x >= m_iArraySize)
			return;

		float y = m_pHeightArray[(INT)position->x].first;

		*force += GetNormalVector(*position);

		if (force->y > y)
			force->y = 0;

		if (position->y >= y)
			position->y = y;

		Lerp(position->y, y, DELTIME);
	}
}

void CPixelCollider::GetLineRotation(const Vector3 & position, float* rot)
{
	if (!IsCollisionOnFloor(position)) {
		Lerp(*rot, 0.0f, DELTIME * 1.0f);
		return;
	}

	Vector3 v = GetLineVector(position);

	if (v == Vector3(0, 0, 0))
		return;

	Lerp(*rot, atan2f(v.y, v.x), DELTIME * 2.0f);
}

  
PIXEL_TYPE CPixelCollider::GetPixelType(Vector3 position)
{
	if (IsCollision(position))
		return m_pHeightArray[(INT)position.x].second;

	return TYPE_NONE;
}

void CPixelCollider::CreateHeightMap(CTexture * targetTex, PIXEL_INFO* array, int indexX)
{
	D3DLOCKED_RECT lockRect;

	if(FAILED(targetTex->texture->LockRect(0, &lockRect, nullptr, D3DLOCK_DISCARD)))
	{
		targetTex->texture->UnlockRect(0);
		return;
	}

	m_fWidth = targetTex->info.Width;
	m_fHeight = targetTex->info.Height;

	DWORD * color = (DWORD*)lockRect.pBits;

	for (int i = indexX; i < m_fWidth + indexX; i++)
	{
		m_pHeightArray[i].first = WINSIZEY;
	}

	for (int x = indexX; x < m_fWidth + indexX; x++)
	{
		for (int y = 0; y < m_fHeight; y++)
		{
			DWORD pixel = color[(INT)m_fWidth * y + x];

			switch(pixel) {

			case BLOCK_COLOR:
				m_pHeightArray[x].first = min(m_pHeightArray[x].first, y);
				m_pHeightArray[x].second = TYPE_FLOOR;
				break;

			case RED_COLOR:
				m_pHeightArray[x].first = min(m_pHeightArray[x].first, y);
				m_pHeightArray[x].second = TYPE_TRAP;
				break;
			}
		}
	}

	targetTex->texture->UnlockRect(0);
	return;
}

void CPixelCollider::SetCameraInMap()
{
	CAMERA.UseRange(-m_fWidth / 2.f, -m_fHeight / 2.f - 15, m_iArraySize + m_fWidth / 2.f, m_fHeight / 2.f);
}

void CPixelCollider::SetObjectOnPixelMap(const string & objectTag, float minusIndexY)
{
	CGameObject* object = OBJECT.FindGameObject<CGameObject>(objectTag);

	if (object) {

		Vector3* position = object->GetTransform()->GetPositionPtr();

		if (IsOutOfRange(position->x))
			return;

		position->y = m_pHeightArray[(int)position->x].first + minusIndexY;
	}
}

void CPixelCollider::UploadMinimapData()
{
	COLLISION.LoadHeightArray(m_pHeightArray, m_iArraySize);
}

void CPixelCollider::DownloadMinimapData()
{
	PIXEL_INFO* pDown = COLLISION.GetHeightArray(&m_iArraySize);

	ResizeArray(m_pHeightArray, m_iArraySize);
	memcpy(m_pHeightArray, pDown, m_iArraySize * sizeof(PIXEL_INFO));
}

bool CPixelCollider::IsOutOfRange(int x)
{
	// 0 보다 작거나 배열 사이즈보다 크면 true.
	if (x < 0 || x > m_iArraySize)
		return true;
	else
		return false;
}

void CPixelCollider::SetLineDepth(float depth)
{
	m_fDepth = depth;
}
