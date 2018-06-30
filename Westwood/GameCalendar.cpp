#include "GameCalendar.h"

CGameCalendar::CGameCalendar()
	: m_timePassageMultiplier(1.0f)
	, m_lengthOfMinute(3.f)
{
	m_hasChangedDateWithoutSleep = false;

	for (size_t i = 0; i < 28; ++i)
	{
		m_dateToDayLUT[i] = static_cast<EDay>(i % 7);
	}

	SetDayName(EDay::Mon, "Mon");
	SetDayName(EDay::Tue, "Tue");
	SetDayName(EDay::Wed, "Wed");
	SetDayName(EDay::Thu, "Thu");
	SetDayName(EDay::Fri, "Fri");
	SetDayName(EDay::Sat, "Sat");
	SetDayName(EDay::Sun, "Sun");

	SetSeasonName(ESeason::Spring, "Spring");
	SetSeasonName(ESeason::Summer, "Summer");
	SetSeasonName(ESeason::Fall, "Fall");
	SetSeasonName(ESeason::Winter, "Winter");
}

void CGameCalendar::EndDay()
{
	m_currentDate++;
	m_currentMinuteTime = 0.f;
	m_clock = { 0,0 };

	if (m_currentDate == 29)
	{
		EnterNewSeason();
	}

	m_currentDay = m_dateToDayLUT[m_currentDate - 1];
}

void CGameCalendar::Sleep()
{
	if (!m_hasChangedDateWithoutSleep)
	{
		EndDay();
	}

	m_clock = { 6,0 };

	m_hasChangedDateWithoutSleep = false;
}

void CGameCalendar::Update(float a_dt)
{
	m_currentMinuteTime += a_dt * m_timePassageMultiplier;

	if (m_currentMinuteTime >= m_lengthOfMinute)
	{
		m_currentMinuteTime -= m_lengthOfMinute;

		m_clock.TickMinute();

		if (m_clock.GetCurrentTime() > CClock::STimePoint(24,0))
		{
			m_hasChangedDateWithoutSleep = true;
			EndDay();
		}
	}
}

#include <SFML\Graphics\Text.hpp>
#include "Renderer.h"
#include "TextureBank.h"
void CGameCalendar::RenderCalendar()
{
	sf::Text currentTextToRender;
	currentTextToRender.setFont(CTextureBank::GetFont(EFonts::Debug));
	currentTextToRender.setFillColor(sf::Color::White);
	currentTextToRender.setOutlineColor(sf::Color::Black);
	currentTextToRender.setOutlineThickness(2.f);

	sf::String stringToRender;

	stringToRender = m_seasonStringLUT[static_cast<size_t>(GetCurrentSeason())] + "\n"; //Season
	stringToRender += m_dayStringLUT[static_cast<size_t>(GetCurrentDay())] + " : " + std::to_string(GetCurrentDate()) + "\n"; //Date and day
	stringToRender += GetCurrentTime().ToString() + "\n"; //Clock

	currentTextToRender.setString(stringToRender);

	currentTextToRender.setOrigin(currentTextToRender.getGlobalBounds().width, 0.f);
	currentTextToRender.setPosition(CRenderer::GetInstance().GetWindowDimensions().x - 100, 0);

	CRenderer::GetInstance().PushUIRenderCommand(currentTextToRender);
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

void CGameCalendar::SetTimePassageMultiplier(float a_multiplier)
{
	m_timePassageMultiplier = a_multiplier;
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

void CGameCalendar::SetDayName(EDay a_day, const char * a_name)
{
	m_dayStringLUT[static_cast<size_t>(a_day)] = a_name;
}

void CGameCalendar::SetSeasonName(ESeason a_season, const char * a_name)
{
	m_seasonStringLUT[static_cast<size_t>(a_season)] = a_name;
}
