#pragma once
#include <vector>
#include "Avatar.h"

class CGameWorld;

class CAvatarCollection
{
public:
	CAvatar & CreateNewAvatar();
	void BindGameWorld(CGameWorld& a_gameWorld);
	void FinalizeAvatarCreation();

	void RenderAvatars();
private:
	std::vector<CAvatar> m_avatarCollection;
	CGameWorld * m_gameWorld;
};