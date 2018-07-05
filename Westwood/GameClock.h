#pragma once
#include <SFML\System\String.hpp>

class CClock
{
public:
	struct STimePoint
	{
		STimePoint() = default;
		STimePoint(unsigned short a_hour, unsigned short a_minute)
		{
			m_hour = a_hour;
			m_minute = a_minute;
		}

		bool operator<(const STimePoint& a_otherTimePoint) const
		{
			if (m_hour < a_otherTimePoint.m_hour)
			{
				return true;
			}

			if (m_hour == a_otherTimePoint.m_hour && m_minute < a_otherTimePoint.m_minute)
			{
				return true;
			}

			return false;
		}

		bool operator>(const STimePoint& a_otherTimePoint) const
		{
			return a_otherTimePoint < (*this);
		}

		unsigned short m_hour;
		unsigned short m_minute;

		//This ensures times are written with a prefixed 0 if under 10 (ie 01, 02 etc)
		sf::String GetTimeString(short a_timeValue) const
		{
			sf::String returnString;

			if (a_timeValue < 10)
			{
				returnString += "0";
			}

			returnString += std::to_string(a_timeValue);

			return std::move(returnString);
		}
		
		sf::String ToString() const
		{
			sf::String returnString;

			returnString += GetTimeString(m_hour) + ":" + GetTimeString(m_minute);

			return std::move(returnString);
		}

	};
public:
	CClock();
	CClock(const STimePoint& a_timePoint);
	CClock(const CClock& a_otherClock);

	void operator =(const STimePoint& a_otherClock);

	void SetTime(const STimePoint& a_timePoint);

	void TickMinute();

	const STimePoint& GetCurrentTime() const;
private:
	STimePoint m_currentTimePoint;
};