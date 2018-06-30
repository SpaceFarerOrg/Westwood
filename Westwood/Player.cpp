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
	m_shouldSleep = false;
}

void CPlayer::Update()
{
	CInputManager& input = CInputManager::GetInstance();
	sf::Vector2f direction;
	if (input.IsKeyDown(EKeyCode::D))
	{
		direction.x += 1.f;
	}
	if (input.IsKeyDown(EKeyCode::A))
	{
		direction.x -= 1.f;
	}
	if (input.IsKeyDown(EKeyCode::W))
	{
		direction.y -= 1.f;
	}
	if (input.IsKeyDown(EKeyCode::S))
	{
		direction.y += 1.f;
	}

	if (input.IsKeyPressed(EKeyCode::E))
	{
		m_inventory.ChangeActiveSlot(1);
	}
	if (input.IsKeyPressed(EKeyCode::Q))
	{
		m_inventory.ChangeActiveSlot(-1);
	}

	if (input.IsKeyPressed(EKeyCode::Space))
	{
		m_toolBank.UseActiveTool(m_avatar);
	}
	
	if (input.IsKeyPressed(EKeyCode::I))
	{
		m_inventory.OpenInventory();
	}

#ifdef _DEBUG
	if (input.IsKeyPressed(EKeyCode::F8))
	{
		m_shouldSleep = true;
	}
#endif

	m_avatar.SetDirection(direction);

	CRenderer::GetInstance().SetCameraTarget(m_avatar.GetPosition());

	m_inventory.RenderInventory();
}

CInventory & CPlayer::GetInventory()
{
	return m_inventory;
}

bool CPlayer::GetShouldSleep()
{
	return m_shouldSleep;
}

void CPlayer::WakeUp()
{
	m_shouldSleep = false;
}

