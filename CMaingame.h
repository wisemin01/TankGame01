#pragma once
class CMaingame
{
public:
	CMaingame();
	virtual ~CMaingame();

public:

	void Init();
	void Update();
	void Render();
	void Destroy();

	void Reset();
	void Lost();

	void CheetInput();
};

