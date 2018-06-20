#include "GameWorld.h"
#include <json.hpp>
#include <fstream>
#include "Avatar.h"
#include "GameEventMaster.h"

CGameWorld::CGameWorld()
{
	m_timeFreezed = false;

	CGameEventMaster::GetInstance().SubscribeToEvent(EGameEvent::PauseTime, [&timeFreezed = m_timeFreezed]() { timeFreezed = true; });
	CGameEventMaster::GetInstance().SubscribeToEvent(EGameEvent::ContinueTime, [&timeFreezed = m_timeFreezed]() {timeFreezed = false; });
}

void CGameWorld::Load(const char * a_worldPath)
{
	nlohmann::json worldJson;
	std::ifstream worldFile(a_worldPath);

	worldFile >> worldJson;

	worldFile.close();

	for (size_t i = 0; i < worldJson["zones"].size(); ++i)
	{
		m_worldZones.push_back(CWorldZone());
		m_worldZones.back().LoadZone(worldJson["zones"][i]);
	}

	m_calendar.SetTime({ 6,0 }, CGameCalendar::ESeason::Spring, 1);
}

void CGameWorld::Render()
{
	m_worldZones[m_currentZone].Render();

	m_calendar.RenderCalendar();
}

void CGameWorld::ChangeZone(short a_newZone)
{
	m_currentZone = a_newZone;

	RecalculateAvatarsInZone();
}

#include "InputManager.h"
void CGameWorld::Update(float a_deltaTime)
{
	if (CInputManager::GetInstance().IsKeyDown(EKeyCode::F1))
	{
		float multiplier = 100.f;

		if (CInputManager::GetInstance().IsKeyDown(EKeyCode::LeftShift))
		{
			multiplier *= 50.f;
		}

		m_calendar.SetTimePassageMultiplier(multiplier);
	}
	else
	{
		m_calendar.SetTimePassageMultiplier(1.f);
	}

	float deltaTime = a_deltaTime;

	if (m_timeFreezed == true)
	{
		deltaTime = 0.f;
	}

	m_calendar.Update(deltaTime);
	UpdateAllAvatars(deltaTime);
}

CWorldZone & CGameWorld::GetCurrentZone()
{
	return m_worldZones[m_currentZone];
}

void CGameWorld::AddAvatarToWorld(CAvatar & a_avatar)
{
	m_allAvatars.push_back(&a_avatar);
}

void CGameWorld::UpdateAllAvatars(float a_deltaTime)
{
	for (size_t i = 0; i < m_avatarsInCurrentZone.size(); ++i)
	{
		m_avatarsInCurrentZone[i]->SetDeltaTime(a_deltaTime);

		/*Move logic*/
		sf::Vector2f avatarsFuturePosition = m_avatarsInCurrentZone[i]->GetFuturePosition();
		sf::Vector2f avatarsCurrentPosition = m_avatarsInCurrentZone[i]->GetPosition();

		sf::Vector2f allowedMove = m_worldZones[m_currentZone].CheckForAllowedMove(avatarsFuturePosition, avatarsCurrentPosition);

		m_avatarsInCurrentZone[i]->AllowMoveTo(allowedMove);
		/*End Move*/

		/*Interaction Logic*/
		sf::Vector2f interactionPosition;
		ETileInteraction interaction;

		if (m_avatarsInCurrentZone[i]->HasPerformedWorldInteraction(interaction, interactionPosition))
		{
			m_worldZones[m_currentZone].PerformWorldInteraction(interaction, interactionPosition);
		}
		/*End interaction*/
	}

	//Todo: Update all Avatars in a different zone than the current one (will make NPCs seem more lively)

}

void CGameWorld::RecalculateAvatarsInZone()
{
	m_avatarsInCurrentZone.clear();
	m_avatarsInOtherZones.clear();

	for (size_t i = 0; i < m_allAvatars.size(); ++i)
	{
		if (m_allAvatars[i]->GetCurrentZone() == m_currentZone)
		{
			m_avatarsInCurrentZone.push_back(m_allAvatars[i]);
		}
		else
		{
			m_avatarsInOtherZones.push_back(m_allAvatars[i]);
		}
	}
}
