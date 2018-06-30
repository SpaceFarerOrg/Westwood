#pragma once
#include <vector>
#include "Avatar.h"

class CGameWorld;
class CPlayer;

class CAvatarCollection
{
public:
	CAvatar & CreateNewAvatar();
	void AddPlayer(CPlayer& a_player);
	void BindGameWorld(CGameWorld& a_gameWorld);
	void FinalizeAvatarCreation();

	void RenderAvatars();
private:
	std::vector<CAvatar> m_avatarCollection;
	CAvatar* m_player;
	CGameWorld * m_gameWorld;
};