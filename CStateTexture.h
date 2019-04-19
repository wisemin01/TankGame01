#pragma once
#include "CObject.h"

enum STATE
{
	ATTACK,
	IDLE,
	MOVE
};

class CStateTexture
{
public:
	union {
		struct {

			CTexture * m_pAttack;
			CTexture * m_pIdle;
			CTexture * m_pMove;

		};
		CTexture* m_pStateTex[3];
	};
public:
	CStateTexture();
	virtual ~CStateTexture();

	void operator ()(ResourceID key, ResourceID path, int frameCount);
	void Get(ResourceID key);

	CTexture* GetAttack() { return m_pAttack; }
	CTexture* GetIdle() { return m_pIdle; }
	CTexture* GetMove() { return m_pMove; }

	CTexture* GetTex(STATE state) { return m_pStateTex[state]; }
};

