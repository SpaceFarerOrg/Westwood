#pragma once

class CClock
{
public:
	struct STimePoint
	{
		unsigned short m_hour;
		unsigned short m_minute;
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