#include "GameCalendar.h"

CGameCalendar::CGameCalendar()
{
	for (size_t i = 0; i < 28; ++i)
	{
		m_dateToDayLUT[i] = static_cast<EDay>(i % 7);
	}
}

void CGameCalendar::EndDay()
{
	m_currentDate++;

	if (m_currentDate / 28 == 1)
	{
		EnterNewSeason();
	}
}

void CGameCalendar::Update(float a_dt)
{
	m_currentMinuteTime += a_dt;

	if (m_currentMinuteTime >= m_lengthOfMinute)
	{
		m_currentMinuteTime -= m_lengthOfMinute;

		m_clock.TickMinute();
	}
}

void CGameCalendar::SetTime(const CClock::STimePoint & a_timePoint, ESeason a_season, unsigned short a_day)
{
	m_clock = a_timePoint;
	m_currentSeason = a_season;
	m_currentDate = a_day;
}

CGameCalendar::EDay CGameCalendar::GetCurrentDay() const
{
	return m_currentDay;
}

CGameCalendar::ESeason CGameCalendar::GetCurrentSeason() const
{
	return m_currentSeason;
}

short CGameCalendar::GetCurrentDate() const
{
	return m_currentDate;
}

const CClock::STimePoint & CGameCalendar::GetCurrentTime() const
{
	return m_clock.GetCurrentTime();
}

void CGameCalendar::EnterNewSeason()
{
	m_currentDate = 1;

	if (m_currentSeason == ESeason::Winter)
	{
		m_currentSeason = ESeason::Spring;
	}
	else
	{
		m_currentSeason = static_cast<ESeason>(static_cast<short>(m_currentSeason) + 1);
	}
}
