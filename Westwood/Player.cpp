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

	m_energyStatus.Init(100.f, 32.f, 128.f, CStatusBar::EType::vertical);
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
		m_energyStatus.AddToValue(-1.f); //TEMP FOR TESTING!!
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
	
	sf::Vector2f positionToRenderInventory;
	positionToRenderInventory.x = CRenderer::GetInstance().GetWindowDimensions().x - m_energyStatus.GetSize().x * 1.5f;
	positionToRenderInventory.y = CRenderer::GetInstance().GetWindowDimensions().y - m_energyStatus.GetSize().y * 1.5f;

	m_energyStatus.Render(positionToRenderInventory);
}

const sf::Vector2f& CPlayer::GetPosition() const
{
	return m_avatar.GetPosition();
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

