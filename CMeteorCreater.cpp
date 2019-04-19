#include "DXUT.h"
#include "CMeteorCreater.h"

#include "CMeteor.h"

CMeteorCreator::CMeteorCreator()
{
}


CMeteorCreator::~CMeteorCreator()
{
}

void CMeteorCreator::Init()
{
	m_bIsDisplay = false;
}

void CMeteorCreator::Update()
{
	if (m_fSpawnTime <= GetNowTime())
	{
		// CREATE METEOR
		CreateMeteor(CAMERA.GetPosition());

		m_fSpawnTime = GetNowTime() + m_fDelay;
	}
}

void CMeteorCreator::Render()
{
}

void CMeteorCreator::Setting(float delay, std::pair<float, float> scaleRange)
{
	m_fDelay = delay;
	m_fSpawnTime = GetNowTime() + delay;

	m_fScaleRange = scaleRange;
}

void CMeteorCreator::CreateMeteor(Vector3 pivot)
{
	Vector3 createSpot = pivot + Vector3(RandomNumber(0, WINSIZEX), -WINSIZEY / 2.f, 0);

	CMeteor* meteor = Instantiate(EFFECT, CMeteor);
	meteor->Create(createSpot);

	float sca = FRandomNumber(m_fScaleRange.first, m_fScaleRange.second);

	meteor->GetTransform()->SetScale(sca, sca, 1.0f);
}

