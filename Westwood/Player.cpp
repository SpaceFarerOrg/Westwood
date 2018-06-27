#include "Player.h"
#include "Renderer.h"
#include "InputManager.h"

CPlayer::CPlayer(CAvatar & a_avatar)
	:m_avatar(a_avatar)
{
	m_avatar.SetMovementSpeed(100.f);
}

void CPlayer::Init()
{
	m_toolBank.InitTools();
	m_inventory.BindToolBank(m_toolBank);
	m_inventory.SetIsOwnedByPlayer();
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

	if (CInputManager::GetInstance().IsKeyPressed(EKeyCode::E))
	{
		m_inventory.ChangeActiveSlot(1);
	}
	if (CInputManager::GetInstance().IsKeyPressed(EKeyCode::Q))
	{
		m_inventory.ChangeActiveSlot(-1);
	}

	if (CInputManager::GetInstance().IsKeyPressed(EKeyCode::Space))
	{
		m_toolBank.UseActiveTool(m_avatar);
	}
	
	if (CInputManager::GetInstance().IsKeyPressed(EKeyCode::I))
	{
		m_inventory.OpenInventory();
	}


	m_avatar.SetDirection(direction);

	CRenderer::GetInstance().SetCameraTarget(m_avatar.GetPosition());

	m_inventory.RenderInventory();
}

CInventory & CPlayer::GetInventory()
{
	return m_inventory;
}

