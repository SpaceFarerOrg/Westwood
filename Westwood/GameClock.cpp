#include "GameClock.h"

CClock::CClock()
{
	m_currentTimePoint = { 0,0 };
}

CClock::CClock(const STimePoint& a_timePoint)
{
	m_currentTimePoint = a_timePoint;
}

CClock::CClock(const CClock& a_otherClock)
{
	*this = a_otherClock;
}

void CClock::operator =(const STimePoint& a_otherTimePoint)
{
	m_currentTimePoint = a_otherTimePoint;
}

void CClock::SetTime(const STimePoint& a_timePoint)
{
	m_currentTimePoint = a_timePoint;
}

void CClock::TickMinute()
{
	m_currentTimePoint.m_minute += 10;
	
	if (m_currentTimePoint.m_minute == 60)
	{
		m_currentTimePoint.m_minute = 0;
		m_currentTimePoint.m_hour++;
	}
}

const CClock::STimePoint & CClock::GetCurrentTime() const
{
	return m_currentTimePoint;
}
