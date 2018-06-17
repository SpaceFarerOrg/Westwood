#pragma once
#include <vector>
#include "WorldZone.h"
#include "GameCalendar.h"

class CAvatar;

class CGameWorld
{
public:
	void Load(const char* a_worldPath);
	void Render();

	void ChangeZone(short a_newZone);
	void Update(float a_deltaTime);
	CWorldZone& GetCurrentZone();

	void AddAvatarToWorld(CAvatar& a_avatar);
private:
	CGameCalendar m_calendar;

	void UpdateAllAvatars(float a_deltaTime);

	void RecalculateAvatarsInZone();

	short m_currentZone;
	std::vector<CWorldZone> m_worldZones;
	std::vector<CAvatar*> m_allAvatars;
	std::vector<CAvatar*> m_avatarsInCurrentZone;
	std::vector<CAvatar*> m_avatarsInOtherZones;
};