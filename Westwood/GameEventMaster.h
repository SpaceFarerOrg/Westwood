#pragma once
#include <array>
#include <vector>
#include <functional>

enum class EGameEvent
{
	PauseTime,
	ContinueTime,
	Count,
};

class CGameEventMaster
{
public:
	static CGameEventMaster& GetInstance();
	void HandleFrameEvents();

	void SendGameEvent(EGameEvent a_eventToSend);
	void SubscribeToEvent(EGameEvent a_eventToSubscribeTo, std::function<void()> a_callbackOnEventHappen);
private:
	CGameEventMaster() = default;
	std::array<bool, static_cast<size_t>(EGameEvent::Count)> m_eventStatusCurrentFrame;
	std::array<std::vector<std::function<void()>>, static_cast<size_t>(EGameEvent::Count)> m_eventSubscriberList;
};