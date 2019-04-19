#include "DXUT.h"
#include "CFrame.h"


CFrame::CFrame()
{
}


CFrame::~CFrame()
{
}

bool CFrame::OnFrame()
{
	if (m_dwSkipTime <= GetNowTime())
	{
		m_dwSkipTime = m_dwFrameSkip + GetNowTime();

		if (++m_iCurrent > m_iMaxFrame)
		{
			if (!m_bIsLoop)
				m_iCurrent = m_iMaxFrame;
			else
				m_iCurrent = m_iStartFrame;
		}
		return true;
	}
	return false;
}

void CFrame::SetFrame(int start, int end, DWORD delay)
{
	m_iCurrent = m_iStartFrame = start;
	m_iMaxFrame = end;

	m_dwFrameSkip = delay;
	m_dwSkipTime = GetNowTime() + delay;
}
