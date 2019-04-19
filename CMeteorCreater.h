#pragma once
#include "CObject.h"


class CMeteorCreator :
	public CGameObject
{
private:
	float m_fDelay;
	float m_fSpawnTime;

	std::pair<float, float> m_fScaleRange;
public:
	CMeteorCreator();
	virtual ~CMeteorCreator();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	void Setting(float delay, std::pair<float, float> scaleRange);

private:
	void CreateMeteor(Vector3 pivot);
};
