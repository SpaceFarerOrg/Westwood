#include "Player.h"
#include "InputManager.h"

CPlayer::CPlayer(CAvatar & a_avatar)
	:m_avatar(a_avatar)
{
	m_avatar.SetMovementSpeed(100.f);
}

void CPlayer::Update()
{
	sf::Vector2f direction;
	if (CInputManager::GetInstance().IsKeyDown(EKeyCode::D))
	{
		direction.x += 1.f;
	}
	if (CInputManager::GetInstance().IsKeyDown(EKeyCode::A))
	{
		direction.x -= 1.f;
	}
	if (CInputManager::GetInstance().IsKeyDown(EKeyCode::W))
	{
		direction.y -= 1.f;
	}
	if (CInputManager::GetInstance().IsKeyDown(EKeyCode::S))
	{
		direction.y += 1.f;
	}

	m_avatar.SetDirection(direction);
}
