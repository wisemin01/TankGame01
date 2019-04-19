#include "DXUT.h"
#include "CIntroScene.h"

#include "CButton.h"

#include "CFade.h"
#include "CExplode.h"

CIntroScene::CIntroScene()
{
}


CIntroScene::~CIntroScene()
{
}

void CIntroScene::Init()
{
	ADDTEXTURE("START_BUTTON", "./RS/UI/BUTTON/START/(%d).png", 3);
	ADDTEXTURE("INFO_BUTTON", "./RS/UI/BUTTON/INFO/(%d).png", 3);
	ADDTEXTURE("QUIT_BUTTON", "./RS/UI/BUTTON/QUIT/(%d).png", 3);
	ADDTEXTURE("HOWTO_BUTTON", "./RS/UI/BUTTON/HOWTO/(%d).png", 3);

	ADDTEXTURE("BLACK", "./RS/EFFECT/BLACK.png");
	ADDTEXTURE("TITLE", "./RS/TITLE/(%d).png", 26);
	
	CAMERA.Init();

	auto title = Instantiate(EFFECT, CGameObject);
	title->AC(CTransform);
	title->AC(CRenderer);
	title->GetTransform()->SetPosition(V3CENTER);
	title->GetRenderer()->SetRenderType(SCREEN);
	title->GetRenderer()->SetTexture("TITLE");
	title->GetRenderer()->SetFrame(0, 25, 300);
	title->GetRenderer()->SetFrameLoop(false);

	Instantiate(UI, CButton)->ButtonSetup(Vector3(300, WINSIZEY / 2.f, 0), "START_BUTTON", 204, 97, [&]() {
		auto fade = Instantiate(UI, CFade); fade->Fade(FADE_TO_255, 1, 3); fade->AddFunc(FADE_TO_255, []() { SCENE.ChangeScene("STAGE1"); });});
	Instantiate(UI, CButton)->ButtonSetup(Vector3(500, WINSIZEY / 2.f, 0), "INFO_BUTTON", 204, 97, [&]() {
		});
	Instantiate(UI, CButton)->ButtonSetup(Vector3(700, WINSIZEY / 2.f, 0), "HOWTO_BUTTON", 204, 97, [&]() {
		});
	Instantiate(UI, CButton)->ButtonSetup(Vector3(900, WINSIZEY / 2.f, 0), "QUIT_BUTTON", 204, 97, [&]() {
		auto fade = Instantiate(UI, CFade); fade->Fade(FADE_TO_255, 1, 3); fade->AddFunc(FADE_TO_255, []() { GameExit(0); }); });
	
}

void CIntroScene::Update()
{
	// CONSOLE_LOG("intro update");
}

void CIntroScene::Render()
{
	// CONSOLE_LOG("intro render");
}

void CIntroScene::Destroy()
{
	// CONSOLE_LOG("intro destroy");
}
