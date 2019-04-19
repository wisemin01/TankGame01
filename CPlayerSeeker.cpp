#include "DXUT.h"
#include "CPlayerSeeker.h"

#include "CPlayer.h"
#include "CPixelCollider.h"
#include "CFade.h"
#include "CTexture.h"

#include "CGagebar.h"
#include "CScene.h"

#define ITEM_DEPTH (60.0f)

CPlayerController::CPlayerController()
{
	m_pNowPlayer = nullptr;
	//m_bIsDisplay = false;
	m_fPlayTime = 0;
	m_fProgress = 0;
}


CPlayerController::~CPlayerController()
{
}

void CPlayerController::Init()
{
	AC(CTransform);
	AC(CRenderer);

	m_pTransform->SetPosition(V3CENTER);
	m_pRenderer->SetRenderType(SCREEN);
	m_pRenderer->SetRenderLayer(20);

	m_szString = new string;

	m_pItemTexture = GETTEXTURE("ITEM");
	m_pHeart = GETTEXTURE("HEART");
	m_bIsGameEnd = false;
	m_bIsStageClear = false;
}

void CPlayerController::Update()
{
	if (m_pNowPlayer)
	{
		if (auto find = FIND_DATA(bool, "PLAYER_LIFE"))
		{
			if (!(*find)) {
				m_pNowPlayer = nullptr;

				CFade* pFade = Instantiate(EFFECT, CFade);

				pFade->Fade(FADE_TO_255, 2, 4);
				pFade->AddFunc(FADE_TO_255, [&]() {
					RespawnPlayer();

					if (m_pNowPlayer)
						m_pNowPlayer->SetIsCanUserControl(false);
					});

				pFade->AddFunc(FADE_TO_0, [&]() {
					if (m_pNowPlayer)
						m_pNowPlayer->SetIsCanUserControl(true);

					});
				return;
			}
		}

		m_fPlayTime += DELTIME; 
		m_fProgress = m_pNowPlayer->GetTransform()->GetPosition().x / (float)COLLISION.GetMapWidth();

		*m_szString = "TIME : "; 
		m_szString->append(std::to_string((int)m_fPlayTime));

		if (m_fProgress > 0.99)
		{
			if (!m_bIsStageClear)
			{
				m_bIsStageClear = true;
				m_pNowPlayer->SetInvinc(true);

				CFade* pFade = Instantiate(EFFECT, CFade);

				pFade->Fade(FADE_TO_255, 1, 4);
				pFade->AddFunc(FADE_TO_255, [&]() {

					if (SCENE.GetNowScene()->GetSceneKey() == "STAGE1")
						SCENE.ChangeScene("STAGE2");
					else if (SCENE.GetNowScene()->GetSceneKey() == "STAGE2")
						SCENE.ChangeScene("INTRO");

					});
			}
		}
		
	}
}

void CPlayerController::Render()
{
	RESOURCE.SetRenderType(SCREEN);

	RESOURCE.DrawFont(*m_szString , "메이플스토리 Bold", Vector3(550, 30, 0), 40,
		D3DXCOLOR(1, 1, 1, 1));

	if (m_pNowPlayer) {
		DrawItemMap();
		DrawHeart();
	}

	if (m_bIsGameEnd)
	{
		RESOURCE.DrawFont("GAME OVER", "메이플스토리 Bold", V3CENTER - Vector3(300, 100, 0), 120,
			D3DXCOLOR(1, 1, 1, 1));
	}
}

void CPlayerController::Destroy()
{
	SAFE_DELETE(m_szString);
}

void CPlayerController::Setting(int stage)
{
	m_iHealth = 3;
	m_iStage = stage;

	m_pNowPlayer = Instantiate(PLAYER, CPlayer);
	m_pNowPlayer->MapSettingOnStage(stage);

	Instantiate(UI, CGagebar)->Setup(&m_fProgress);
}

void CPlayerController::RespawnPlayer()
{
	if (m_iHealth <= 1) {
		m_bIsGameEnd = true;
		return;
	}

	if (!m_pNowPlayer)
		m_pNowPlayer = Instantiate(PLAYER, CPlayer);

	m_pNowPlayer->SettingMinimap(m_iStage);

	Vector3 *position = FIND_DATA(Vector3, "PLAYER_RESPAWN");

	if (position)
		m_pNowPlayer->GetTransform()->SetPosition(*position);

	CAMERA.SetPosition(m_pNowPlayer->GetTransform()->GetPosition());

	m_iHealth--;
	m_fPlayTime = 0;
}

void CPlayerController::DrawItemMap()
{
	float startX = WINSIZEX - m_pNowPlayer->GetItemMap().size() * ITEM_DEPTH * 2;
	int count = 0;

	for (auto iter : m_pNowPlayer->GetItemMap())
	{
		Vector3 position = Vector3(startX + count * ITEM_DEPTH * 2 + ITEM_DEPTH, ITEM_DEPTH, 0);
		Vector3 scale = m_pTransform->GetScale();
		float rotation = m_pTransform->GetRotation();

		RESOURCE.ApplyWorldTransform(position, scale, rotation);

		RESOURCE.Draw(m_pItemTexture->GetImage(iter.first), D3DXCOLOR(255, 255, 255, 255));

		RESOURCE.DrawFont(to_string((int)(iter.second - GetNowTime()) / 1000),
			"메이플스토리 Light", position + Vector3(30, 20, 0), 27.5, D3DXCOLOR(1, 1, 1, 1));

		count++;
	}
}

void CPlayerController::DrawHeart()
{
	float heartW = m_pHeart->info.Width;
	float heartH = m_pHeart->info.Height;
	float startX = heartW / 2.f;

	for (int i = 0; i < m_iHealth; i++)
	{
		Vector3 position = Vector3(startX + heartW * i + 20, heartH / 2.f + 20, 0);
		Vector3 scale = m_pTransform->GetScale();
		float rotation = m_pTransform->GetRotation();

		RESOURCE.ApplyWorldTransform(position, scale, rotation);

		RESOURCE.Draw(m_pHeart, D3DXCOLOR(255, 255, 255, 255));
	}
}
