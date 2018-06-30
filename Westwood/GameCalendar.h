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
		Winter,
		Count
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
	void Sleep();
	void Update(float a_dt);
	void RenderCalendar();


	void SetTime(const CClock::STimePoint& a_timePoint, ESeason a_season, unsigned short a_day);

	EDay GetCurrentDay() const;
	ESeason GetCurrentSeason() const;
	short GetCurrentDate() const;
	const CClock::STimePoint& GetCurrentTime() const;

	void SetTimePassageMultiplier(float a_multiplier);

private:
	void EnterNewSeason();
	CClock m_clock;
	ESeason m_currentSeason;
	EDay m_currentDay;
	unsigned short m_currentDate;
	std::array<EDay, 28> m_dateToDayLUT;

	std::array<sf::String, static_cast<size_t>(EDay::Count)> m_dayStringLUT;
	std::array<sf::String, static_cast<size_t>(ESeason::Count)> m_seasonStringLUT;
	void SetDayName(EDay a_day, const char* a_name);
	void SetSeasonName(ESeason, const char* a_name);

	float m_timePassageMultiplier;
	float m_currentMinuteTime;
	float m_lengthOfMinute;

	bool m_hasChangedDateWithoutSleep : 1;
};