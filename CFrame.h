#pragma once
class CFrame
{
public:
	int m_iCurrent = 0, m_iMaxFrame = 0, m_iStartFrame = 0;
	DWORD m_dwFrameSkip = 0, m_dwSkipTime = 0;
	bool m_bIsLoop = false;
public:
	CFrame();
	virtual ~CFrame();

	bool OnFrame();
	void SetFrame(int start, int end, DWORD delay);

	inline bool operator()() { return OnFrame(); }
};

