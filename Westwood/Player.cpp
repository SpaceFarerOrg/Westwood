#include "Player.h"
#include "Renderer.h"
#include "InputManager.h"

CPlayer::CPlayer()
{
	SetMovementSpeed(100.f);
}

void CPlayer::Init()
{
	m_toolBank.InitTools();
	m_inventory.BindToolBank(m_toolBank);
	m_inventory.SetIsOwnedByPlayer();
	m_shouldSleep = false;

	m_energyStatus.Init(100.f, 32.f, 128.f, CStatusBar::EType::vertical);
	m_energyStatus.BindCallbackToOnEmpty([this] { this->Faint(); });
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
		DoInteraction();
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

	SetDirection(direction);

	CRenderer::GetInstance().SetCameraTarget(GetPosition());

	m_inventory.RenderInventory();
	
	sf::Vector2f positionToRenderInventory;
	positionToRenderInventory.x = CRenderer::GetInstance().GetWindowDimensions().x - m_energyStatus.GetSize().x * 1.5f;
	positionToRenderInventory.y = CRenderer::GetInstance().GetWindowDimensions().y - m_energyStatus.GetSize().y * 1.5f;

	m_energyStatus.Render(positionToRenderInventory);
}

void CPlayer::Faint()
{
	//Todo: Add meaningful faint logic here
	SetShouldSleep();
}

void CPlayer::DoInteraction()
{
	PerformWorldInteraction(ETileInteraction::Use, GetInteractPosition());
	m_toolBank.UseActiveTool(*this);
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
	m_energyStatus.SetToMax();
	SetPosition({ 0.f, 0.f });
}

void CPlayer::SetShouldSleep()
{
	m_shouldSleep = true;
}

sf::Vector2f CPlayer::GetInteractPosition() const
{
	sf::Vector2f interactPosition;
	interactPosition = GetPosition() + GetFacingDirection() * 64.f;

	return std::move(interactPosition);
}

void CPlayer::DrainEnergy(float a_drainage)
{
	m_energyStatus.AddToValue(a_drainage * -1.f);
}

