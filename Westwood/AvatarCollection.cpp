#include "AvatarCollection.h"
#include "GameWorld.h"
#include "Player.h"

CAvatar & CAvatarCollection::CreateNewAvatar()
{
	m_avatarCollection.push_back(CAvatar());

	return m_avatarCollection.back();
}

void CAvatarCollection::AddPlayer(CPlayer & a_player)
{
	m_player = &a_player;
}

void CAvatarCollection::BindGameWorld(CGameWorld & a_gameWorld)
{
	m_gameWorld = &a_gameWorld;
}

void CAvatarCollection::FinalizeAvatarCreation()
{
	for (CAvatar& avatar : m_avatarCollection)
	{
		m_gameWorld->AddAvatarToWorld(avatar);
	}
}

void CAvatarCollection::RenderAvatars()
{
	for (CAvatar& avatar : m_avatarCollection)
	{
		avatar.Draw();
	}

	m_player->Draw();
}
