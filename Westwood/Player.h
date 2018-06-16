#pragma once
#include "Avatar.h"

class CPlayer
{
public:
	CPlayer(CAvatar& a_avatar);
	void Update();
private:
	CAvatar & m_avatar;
};