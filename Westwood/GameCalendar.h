#pragma once
#include <array>
#include "GameClock.h"

class CGameCalendar
{
public:
	enum class ESeason
	{
		Spring,
		Summer,
		Fall,
		Winter
	};

	enum class EDay
	{
		Mon,
		Tue,
		Wed,
		Thu,
		Fri,
		Sat,
		Sun,
		Count,
	};
public:
	CGameCalendar();

	void EndDay();
	void Update(float a_dt);

	void SetTime(const CClock::STimePoint& a_timePoint, ESeason a_season, unsigned short a_day);

	EDay GetCurrentDay() const;
	ESeason GetCurrentSeason() const;
	short GetCurrentDate() const;
	const CClock::STimePoint& GetCurrentTime() const;
private:
	void EnterNewSeason();
	CClock m_clock;
	ESeason m_currentSeason;
	EDay m_currentDay;
	unsigned short m_currentDate;
	std::array<EDay, 28> m_dateToDayLUT;

	float m_currentMinuteTime;
	float m_lengthOfMinute;

};