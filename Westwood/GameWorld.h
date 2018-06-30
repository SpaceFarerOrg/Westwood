#pragma once
#include <vector>
#include "WorldZone.h"
#include "GameCalendar.h"
#include "AvatarCollection.h"
#include "Player.h"

class CAvatar;

class CGameWorld
{
public:
	CGameWorld();

	void Load(const char* a_worldPath);
	void Render();

	void ChangeZone(short a_newZone);
	void Update(float a_deltaTime);
	CWorldZone& GetCurrentZone();

	void AddAvatarToWorld(CAvatar& a_avatar);
private:
	CGameCalendar m_calendar;
	CAvatarCollection m_avatarCollection;
	CPlayer m_player;

	void UpdateAllAvatars(float a_deltaTime);
	
	void RecalculateAvatarsInZone();

	short m_currentZone;
	std::vector<CWorldZone> m_worldZones;
	std::vector<CAvatar*> m_allAvatars;
	std::vector<CAvatar*> m_avatarsInCurrentZone;
	std::vector<CAvatar*> m_avatarsInOtherZones;

	bool m_timeFreezed;
};