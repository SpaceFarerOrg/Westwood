#include "GameWorld.h"
#include <json.hpp>
#include <fstream>
#include "Avatar.h"
#include "GameEventMaster.h"
#include "Math.h"

CGameWorld::CGameWorld()
{
	m_timeFreezed = false;

	CGameEventMaster::GetInstance().SubscribeToEvent(EGameEvent::PauseTime, [&timeFreezed = m_timeFreezed]() { timeFreezed = true; });
	CGameEventMaster::GetInstance().SubscribeToEvent(EGameEvent::ContinueTime, [&timeFreezed = m_timeFreezed]() {timeFreezed = false; });
	CGameEventMaster::GetInstance().SubscribeToEvent(EGameEvent::PlayerSleep, [&timeFreezed = m_timeFreezed]() { timeFreezed = true; });
	CGameEventMaster::GetInstance().SubscribeToEvent(EGameEvent::PlayerWakeup, [&timeFreezed = m_timeFreezed]() {timeFreezed = false; });
	CGameEventMaster::GetInstance().SubscribeToEvent(EGameEvent::FadeReachBlack, [this] {this->m_calendar.Sleep(); });

	m_allAvatars.push_back(&m_player);

	m_avatarCollection.AddPlayer(m_player);

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

	m_player.Init();
	/*Debug give player items*/
	m_player.GetInventory().AddItemToInventory("Axe");
	m_player.GetInventory().AddItemToInventory("Pickaxe");
	m_player.GetInventory().AddItemToInventory("Shovel");
	m_player.GetInventory().AddItemToInventory("WaterCan");
	/*End debug*/


	m_avatarCollection.BindGameWorld(*this);
	m_avatarCollection.FinalizeAvatarCreation();

	m_farm.Init();
	m_player.BindFarm(m_farm);
}

void CGameWorld::Render()
{
	m_worldZones[m_currentZone].Render();

	m_calendar.RenderCalendar();
	m_farm.Render();
}

void CGameWorld::ChangeZone(short a_newZone)
{
	m_worldZones[m_currentZone].LeaveZone();

	m_currentZone = a_newZone;

	m_worldZones[m_currentZone].EnterZone();

	RecalculateAvatarsInZone();

	m_player.SetCurrentZone(m_worldZones[m_currentZone]);
	m_farm.BindFarmTileMap(m_worldZones[m_currentZone].GetTileMap());
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

	m_player.Update();
	m_calendar.Update(deltaTime);
	UpdateAllAvatars(deltaTime);
	m_avatarCollection.RenderAvatars();
	m_worldZones[m_currentZone].CheckPlayerAgainstItems(m_player);
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
		sf::Vector2f finalAllowedMove;
		
		for (short cp = 0; cp < 4; ++cp)
		{
			sf::Vector2f collisionPointsFuturePosition = m_avatarsInCurrentZone[i]->GetFuturePositionOfCollisionPoint(cp);
			sf::Vector2f collisionPointsCurrentPosition = m_avatarsInCurrentZone[i]->GetPositionOfCollisionPoint(cp);

			sf::Vector2f allowedMove = m_worldZones[m_currentZone].CheckForAllowedMove(collisionPointsFuturePosition, collisionPointsCurrentPosition);

			if (Math::GetLenght2(allowedMove) < Math::GetLenght2(finalAllowedMove) || cp == 0) //If its the first iteration do this to avoid never being allowed to move
			{
				finalAllowedMove = allowedMove;
			}
		}

		m_avatarsInCurrentZone[i]->AllowMove(finalAllowedMove);
		/*End Move*/


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
