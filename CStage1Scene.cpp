#include "DXUT.h"
#include "CStage1Scene.h"

#include "CPlayer.h"
#include "CBackground.h"
#include "CScrollBackground.h"
#include "CMapPlacer.h"
#include "CMeteorCreater.h"
#include "CPlayerSeeker.h"
#include "CCheckPoint.h"

#include "CStateTexture.h"
#include "CMine.h"
#include "CEnemyAdmin.h"

CStage1Scene::CStage1Scene()
{
}


CStage1Scene::~CStage1Scene()
{
}

void CStage1Scene::Init()
{
	// PLAYER LOAD
	CStateTexture stateLoader;

	stateLoader("PANZER", "./RS/OBJECT/PLAYER/PANZER", 6);
	stateLoader("HEAVYTANK", "./RS/OBJECT/PLAYER/HEAVYTANK", 6);
	stateLoader("WHIPPET", "./RS/OBJECT/PLAYER/WHIPPET", 6);

	// ENEMY LOAD
	stateLoader("ENEMY", "./RS/OBJECT/ENEMY/ENEMY", 6);
	stateLoader("MINE_ENEMY", "./RS/OBJECT/ENEMY/MINE_ENEMY", 6);

	ADDTEXTURE("MINE", "./RS/OBJECT/ENEMY/MINE/(%d).png", 6);
	ADDTEXTURE("BULLET", "./RS/EFFECT/BULLET.png");
	ADDTEXTURE("METEOR", "./RS/EFFECT/meteor.png");
	ADDTEXTURE("EXPLODE", "./RS/EFFECT/EXPLODE/(%d).png", 6);
	ADDTEXTURE("PLASMA", "./RS/EFFECT/PLASMA/(%d).png", 4);
	ADDTEXTURE("CANNON", "./RS/OBJECT/PLAYER/CANNON%d.png", 3);
	ADDTEXTURE("DASH", "./RS/EFFECT/DASH_EFFECT.png");

	ADDTEXTURE("CHECKPOINT", "./RS/OBSTACLE/CheckPoint%d.png", 2);
	ADDTEXTURE("BLACK", "./RS/EFFECT/BLACK.png");
	ADDTEXTURE("ITEM", "./RS/UI/ITEM/ITEM(%d).png", 4);

	ADDTEXTURE("MINITANK", "./RS/UI/GAGEBAR/MINITANK.png");
	ADDTEXTURE("HEART", "./RS/UI/GAGEBAR/HEART.png");
	ADDTEXTURE("GAGEBAR", "./RS/UI/GAGEBAR/BAR%d.png", 2);

	// BACKGROUND
	ADDTEXTURE("BACKGROUND", "./RS/BACKGROUND/STAGE1/%d.png", 4);
	ADDTEXTURE("MINIMAP", "./RS/BACKGROUND/STAGE1/MINIMAP/minimap%d.png", 3);
	ADDTEXTURE("MAP", "./RS/BACKGROUND/STAGE1/GROUND/pair%d.png", 3);
	ADDTEXTURE("MAP_OBJ", "./RS/BACKGROUND/STAGE1/GROUND/obj%d.png", 3);

	Instantiate(SPAWNER, CPlayerController)->Setting(1);

	Instantiate(BACKGROUND, CScrollBackground)->Setting(GETTEXTURE("BACKGROUND", 0), Vector3(0, WINSIZEY / 2.f, 0), 200);
	Instantiate(BACKGROUND, CScrollBackground)->Setting(GETTEXTURE("BACKGROUND", 1), Vector3(0, WINSIZEY / 2.f, 0), 400);
	Instantiate(BACKGROUND, CScrollBackground)->Setting(GETTEXTURE("BACKGROUND", 2), Vector3(0, WINSIZEY / 2.f, 0), 600);
	Instantiate(BACKGROUND, CScrollBackground)->Setting(GETTEXTURE("BACKGROUND", 3), Vector3(0, WINSIZEY / 2.f, 0), 800);

	Instantiate(SPAWNER, CMeteorCreator)->Setting(1000, make_pair(0.5, 1.0));

	Instantiate(SPAWNER, CEnemyAdmin)->Setup(3500);

	CMine::CreateMines(60, 1500, 700, 850);
}

void CStage1Scene::Update()
{

}

void CStage1Scene::Render()
{

}

void CStage1Scene::Destroy()
{

}
