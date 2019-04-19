#pragma once
#include "CSingleton.h"
class CSoundManager :
	public CSingleton<CSoundManager>
{
public:
	CSoundManager();
	virtual ~CSoundManager();
};

#define SOUND (*CSoundManager::Instance())