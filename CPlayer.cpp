#include "DXUT.h"
#include "CPlayer.h"

#include "CDelayBullet.h"
#include "CGuiededBullet.h"

#include "CExplode.h"
#include "CTopCannon.h"

CPlayer::CPlayer()
{
}


CPlayer::~CPlayer()
{
}

void CPlayer::Init()
{
	AC(CTransform);
	AC(CRenderer);
	AC(CRigidbody);
	AC(CMultiPixelCollider);
	AC(CCollider);

	SetTag("PLAYER");
	CAMERA.SetTarget(this);
	CAMERA.SetPosition(Vector3(200, 500, 0));
	CAMERA.SetCameraOffset(Vector3(300, 0, 0));

	m_pRenderer->SetRenderType(SCROLL);
	m_pRenderer->SetRenderLayer(10);

	m_pTransform->SetPosition(WINSIZEX / 2.f, 500, 0);
	m_pTransform->SetScale(0.5, 0.5, 0.5);
	m_bIsCanUserControl = true;

	m_pItemMap = new map<ITEM_TYPE, float>;

	m_StateTex[PANZER].Get("PANZER");
	m_StateTex[WHIPPET].Get("WHIPPET");
	m_StateTex[HEAVYTANK].Get("HEAVYTANK");

	ChangeTank(PANZER);
	m_pRenderer->SetFrame(0, 5, 150);

	m_pCannon = Instantiate(CANNON, CTopCannon);
	m_pCannon->Setup(this);

	INSERT_DATA("PLAYER_LIFE", new bool(true));
}

void CPlayer::Update()
{
	CalcPlayer();

	if (m_bIsCanUserControl)
		CalcInput();

	CalcState();
}

void CPlayer::Render()
{
}

void CPlayer::Destroy()
{
	if (CAMERA.GetTarget() == this)
		CAMERA.SetTarget(nullptr);

	if (m_pItemMap) {
		m_pItemMap->clear();
		delete m_pItemMap;
		m_pItemMap = nullptr;
	}

	INSERT_DATA("PLAYER_LIFE", new bool(false));
}

void CPlayer::CalcPlayer()
{
	if (m_pTransform->GetPosition().y >= WINSIZEY)
	{
		Kill();
	}

	Vector3 *m_pPosition = m_pTransform->GetPositionPtr();

	m_pPixelCollider->GetLineRotation(*m_pPosition, m_pTransform->GetRotationPtr());

	CAMERA.LockInMap(m_pPosition);

	UpdatingItemList();
}

void CPlayer::CalcInput()
{
	float boostSpeed = m_fFrontSpeed;

	if (INPUT.GetKeyPress(VK_LSHIFT))
		boostSpeed *= 1.25f;

	if (INPUT.GetKeyPress(VK_D) || INPUT.GetKeyPress(VK_RIGHT))
	{
		m_pRigidbody->AddForce(boostSpeed, 0);
	}

	if (INPUT.GetKeyPress(VK_A) || INPUT.GetKeyPress(VK_LEFT))
	{
		m_pRigidbody->AddForce(-m_fBackSpeed, 0);
	}

	if (INPUT.GetKeyDown(VK_SPACE))
	{
		if (m_pPixelCollider->IsOnFloor()) {
			m_pRigidbody->AddForce(0, -m_fJumpPower);

			if (ItemCheck(DOUBLE_JUMP_BOOSTER))
				m_bIsCanDoubleJump = true;
		}
		else if(m_bIsCanDoubleJump)
		{
			m_bIsCanDoubleJump = false;
			m_pRigidbody->AddForce(0, -m_fJumpPower);
		}
	}
	
	if (INPUT.GetKeyDown(VK_LBUTTON))
	{
		float range = 400;

		if (ItemCheck(RANGE_UPGRADE))
			range = 1200;

		if (ItemCheck(THREE_DIR_MISSILE))
		{
			for (int i = -1; i < 2; i++)
				Instantiate(EFFECT, CDelayBullet)->Fire(m_pTransform->GetPosition()
					+ GetBarrelPos(), Vector3(cosf(m_pTransform->GetRotation() + i * 0.3),
						sinf(m_pTransform->GetRotation() + i * 0.3), 0), "BULLET", 50, 1, range);
		}
		else if (ItemCheck(HOMING_MISSILE))
		{
			Instantiate(EFFECT, CGuiededBullet)->Fire(m_pTransform->GetPosition() + GetBarrelPos(), "BULLET", 35, 2);
		}
		else
		{
			Instantiate(EFFECT, CDelayBullet)->Fire(m_pTransform->GetPosition()
				+ GetBarrelPos(), Vector3(cosf(m_pTransform->GetRotation()),
					sinf(m_pTransform->GetRotation()), 0), "BULLET", 50, 1, range);
		}
	}

	if (INPUT.GetKeyDown('1'))
		AddItem(DOUBLE_JUMP_BOOSTER, 7500);
	if (INPUT.GetKeyDown('2'))
		AddItem(RANGE_UPGRADE, 7500);
	if (INPUT.GetKeyDown('3'))
		AddItem(HOMING_MISSILE, 7500);
	if (INPUT.GetKeyDown('4'))
		AddItem(THREE_DIR_MISSILE, 7500);
}

void CPlayer::CalcState()
{
	int prev = m_eState;

	if (m_pRigidbody->GetTotalForce() == 0)
	{
		m_eState = IDLE;
	}
	else
		m_eState = MOVE;

	if (prev != m_eState)
		ChangeTextureAsState();
}

void CPlayer::Kill()
{
	if (m_bIsInvinc)
		return;

	CAMERA.Shake(1000, 20);

	for (int i = 0; i < 5; i++) {

		float s;
		float tx, ty;

		s = FRandomNumber(0.8, 1.6);
		tx = RandomNumber(-150, 150);
		ty = RandomNumber(-150, 150);

		auto explode = Instantiate(EFFECT, CExplode);
		explode->Setup(m_pTransform->GetPosition()
			+ Vector3(tx, ty, 0), "EXPLODE", RandomNumber(50, 100));
		explode->GetTransform()->SetScale(s, s, 0);
	}
	m_bIsLive = false;
	m_pCannon->Kill();
}

void CPlayer::MapSettingOnStage(int stage_number)
{
	m_pPixelCollider->CreatePixelCollider(GETTEXTURE("MINIMAP"), 3, 10);

	switch (stage_number) {
	case 1:
		m_pPixelCollider->CreateMapsAsPixelMap(GETTEXTURE("MAP"), 4);
		m_pPixelCollider->CreateMapsAsPixelMap(GETTEXTURE("MAP_OBJ"), 3);
		break;
		
	case 2:
		m_pPixelCollider->CreateMapsAsPixelMap(GETTEXTURE("MAP"), 3);
		m_pPixelCollider->CreateMapsAsPixelMap(GETTEXTURE("MAP_OBJ"), 2);
		break;
	}

	m_pPixelCollider->UploadMinimapData();
	m_pPixelCollider->CreateCheckPoints(GETTEXTURE("MINIMAP"), 10);

	m_pPixelCollider->SetCameraInMap();
	m_pPixelCollider->SetObjectOnPixelMap(m_szTag);
}

void CPlayer::SettingMinimap(int stage_number)
{
	m_pPixelCollider->DownloadMinimapData();
	m_pPixelCollider->SetObjectOnPixelMap(m_szTag);
}

Vector3 CPlayer::GetBarrelPos()
{
	D3DXMATRIX matS, matR;
	Vector3 s = m_pTransform->GetScale();

	D3DXMatrixScaling(&matS, s.x, s.y, s.z);
	D3DXMatrixRotationZ(&matR, m_pTransform->GetRotation());

	D3DXMATRIX matOut = matS * matR;

	Vector3 vOut;
	D3DXVec3TransformCoord(&vOut, &m_vBarrel, &matOut);

	return vOut;
}

bool CPlayer::UpgradeTank()
{
	if (m_eTankMode + 1 < TANK_END)
	{
		m_eTankMode = (TANK_MODE)((int)m_eTankMode + 1);
		ChangeTank(m_eTankMode);

		return true;
	}
	return false;
}

bool CPlayer::DegradeTank()
{
	if (m_eTankMode - 1 > -1)
	{
		m_eTankMode = (TANK_MODE)((int)m_eTankMode - 1);
		ChangeTank(m_eTankMode);
		return true;
	}

	return false;
}

bool CPlayer::ItemCheck(ITEM_TYPE item)
{
	if (m_pItemMap->find(item) != m_pItemMap->end())
		return true;
	else return false;
}

void CPlayer::ChangeTank(TANK_MODE tank)
{
	switch (tank)
	{
	case TANK_MODE::PANZER:
		m_pRenderer->SetTexture(m_StateTex[PANZER].GetTex(m_eState));
		m_pRenderer->SetOffset(Vector3(0, -45, 0));
		m_pCollider->Clear();
		m_pCollider->AddColliderAsTexture(m_pRenderer->m_pTexture,
			Vector3(0, -45, 0), [&](CollideBox* other) {});

		m_vBarrel = Vector3(80, -170, 0);
		m_fFrontSpeed = 36;
		m_fBackSpeed = 25;
		m_pRigidbody->SetMass(2.0f);
		m_pRigidbody->SetAttenuation(0.95f, 0.98f);
		m_fJumpPower = 700;
		m_pPixelCollider->SetLineDepth(65);
		break;
	case TANK_MODE::WHIPPET:
		m_pRenderer->SetTexture(m_StateTex[WHIPPET].GetTex(m_eState));
		m_pRenderer->SetOffset(Vector3(0, -45, 0));
		m_pCollider->Clear();
		m_pCollider->AddColliderAsTexture(m_pRenderer->m_pTexture,
			Vector3(0, -45, 0), [&](CollideBox* other) {});

		m_vBarrel = Vector3(80, -170, 0);
		m_fFrontSpeed = 40;
		m_fBackSpeed = 30;
		m_pRigidbody->SetMass(2.3f);
		m_pRigidbody->SetAttenuation(0.94f, 0.98f);
		m_fJumpPower = 800;		
		m_pPixelCollider->SetLineDepth(75);
		break;
	case TANK_MODE::HEAVYTANK:
		m_pRenderer->SetTexture(m_StateTex[HEAVYTANK].GetTex(m_eState));
		m_pRenderer->SetOffset(Vector3(0, -70, 0));
		m_pCollider->Clear();
		m_pCollider->AddColliderAsTexture(m_pRenderer->m_pTexture,
			Vector3(0, -45, 0), [&](CollideBox* other) {});

		m_vBarrel = Vector3(80, -170, 0);
		m_fFrontSpeed = 36;
		m_fBackSpeed = 25;
		m_pRigidbody->SetMass(3.0f);
		m_pRigidbody->SetAttenuation(0.93f, 0.98f);
		m_fJumpPower = 1000;
		m_pPixelCollider->SetLineDepth(100);
		break;
	}
}

void CPlayer::ChangeTextureAsState()
{
	m_pRenderer->SetTexture(m_StateTex[m_eTankMode].GetTex(m_eState));
}

void CPlayer::UpdatingItemList()
{
	float nt = GetNowTime();

	for (auto iter = m_pItemMap->begin(); iter != m_pItemMap->end();)
	{
		if ((*iter).second <= nt)
			iter = m_pItemMap->erase(iter);
		else
			iter++;
	}
}

