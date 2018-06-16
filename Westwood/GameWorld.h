#pragma once
#include <vector>
#include "WorldZone.h"

class CAvatar;

class CGameWorld
{
public:
	void Load(const char* a_worldPath);
	void Render();

	void ChangeZone(short a_newZone);
	void Update(float a_deltaTime);

	void AddAvatarToWorld(CAvatar& a_avatar);
private:
	void UpdateAllAvatars(float a_deltaTime);

	void RecalculateAvatarsInZone();

	short m_currentZone;
	std::vector<CWorldZone> m_worldZones;
	std::vector<CAvatar&> m_allAvatars;
	std::vector<CAvatar&> m_avatarsInCurrentZone;
	std::vector<CAvatar&> m_avatarsInOtherZones;
};