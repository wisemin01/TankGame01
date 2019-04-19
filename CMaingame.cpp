#include "DXUT.h"
#include "CMaingame.h"

#include "CIntroScene.h"
#include "CStage1Scene.h"
#include "CStage2Scene.h"

#include "CPlayer.h"

CMaingame::CMaingame()
{
}


CMaingame::~CMaingame()
{
}

void CMaingame::Init()
{
	SCENE.AddScene("INTRO"	, new CIntroScene);
	SCENE.AddScene("STAGE1"	, new CStage1Scene);
	SCENE.AddScene("STAGE2"	, new CStage2Scene);

	SCENE.ChangeScene("INTRO");
}

void CMaingame::Update()
{
	INPUT.Update();
	SCENE.Update();
	CAMERA.Update();

#if TRUE
	CheetInput();
#endif
}

void CMaingame::Render()
{
	RESOURCE.Begin(SCREEN);

	SCENE.Render();

	RESOURCE.End();
}

void CMaingame::Destroy()
{
	CObjectManager	::DestroyInst();
	CCollisionManager::DestroyInst();
	CDataManager	::DestroyInst();
	CSceneManager	::DestroyInst();
	CResourceManager::DestroyInst();
	CInputManager	::DestroyInst();
	CCameraManager	::DestroyInst();
	CSoundManager	::DestroyInst();
}

void CMaingame::Reset()
{
	RESOURCE.Reset();
}

void CMaingame::Lost()
{
	RESOURCE.Lost();
}

void CMaingame::CheetInput()
{
	if (INPUT.GetKeyDown(VK_F1))
	{
		auto player = OBJECT.FindGameObject<CPlayer>("PLAYER");
		player->SetInvinc(!player->GetInvinc());
	}
	if (INPUT.GetKeyDown(VK_F2))
		OBJECT.FindGameObject<CPlayer>("PLAYER")->UpgradeTank();
	if (INPUT.GetKeyDown(VK_F3))
		OBJECT.FindGameObject<CPlayer>("PLAYER")->DegradeTank();
	if (INPUT.GetKeyDown(VK_F4))
		SCENE.ChangeScene("INTRO");
	if (INPUT.GetKeyDown(VK_F5))
		SCENE.ChangeScene("STAGE1");
	if (INPUT.GetKeyDown(VK_F6))
		SCENE.ChangeScene("STAGE2");
}
