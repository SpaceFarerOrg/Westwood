#include "GameWorld.h"
#include <json.hpp>
#include <fstream>
#include "Avatar.h"

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
}

void CGameWorld::Render()
{
	m_worldZones[m_currentZone].Render();
}

void CGameWorld::ChangeZone(short a_newZone)
{
	m_currentZone = a_newZone;

	RecalculateAvatarsInZone();
}

void CGameWorld::Update(float a_deltaTime)
{
	UpdateAllAvatars(a_deltaTime);
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

		sf::Vector2f avatarsFuturePosition = m_avatarsInCurrentZone[i]->GetFuturePosition();

		bool shouldAllowMove = m_worldZones[m_currentZone].IsMoveToPositionAllowed(avatarsFuturePosition);

		m_avatarsInCurrentZone[i]->AllowMove(shouldAllowMove);
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
