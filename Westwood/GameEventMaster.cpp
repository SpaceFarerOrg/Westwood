#include "GameEventMaster.h"

CGameEventMaster & CGameEventMaster::GetInstance()
{
	static CGameEventMaster instance;

	return instance;
}

void CGameEventMaster::HandleFrameEvents()
{
	for (size_t i = 0; i < m_eventStatusCurrentFrame.max_size(); ++i)
	{
		if (m_eventStatusCurrentFrame[i] == true)
		{
			for (std::function<void()>& callback : m_eventSubscriberList[i])
			{
				callback();
			}

			m_eventStatusCurrentFrame[i] = false;
		}
	}
}

void CGameEventMaster::SendGameEvent(EGameEvent a_eventToSend)
{
	m_eventStatusCurrentFrame[static_cast<size_t>(a_eventToSend)] = true;
}

void CGameEventMaster::SubscribeToEvent(EGameEvent a_eventToSubscribeTo, std::function<void()> a_callbackOnEventHappen)
{
	m_eventSubscriberList[static_cast<size_t>(a_eventToSubscribeTo)].push_back(a_callbackOnEventHappen);
}
