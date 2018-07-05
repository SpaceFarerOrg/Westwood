#include "Player.h"
#include "Renderer.h"
#include "InputManager.h"
#include "GameEventMaster.h"
#include "SoundBank.h"
#include "AudioManager.h"
#include "ItemBank.h"

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

	m_inventory.TrySetActiveSlot(0);

	m_energyStatus.Init(100.f, 32.f, 128.f, CStatusBar::EType::vertical);
	m_energyStatus.BindCallbackToOnEmpty([this] { this->Faint(); });

	CGameEventMaster::GetInstance().SubscribeToEvent(EGameEvent::FadeFinished, [this] {this->WakeUp(); });

	m_isGod = false;
}

void CPlayer::Update()
{
	CInputManager& input = CInputManager::GetInstance();
	sf::Vector2f direction;

	if (m_isInputLocked == false)
	{
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
		
		if (input.IsKeyPressed(EKeyCode::Space))
		{
			DoInteraction();
		}

		if (input.IsKeyPressed(EKeyCode::I))
		{
			m_inventory.ToggleInventory();
		}
	}

	// DEBUG CODE
	if (input.IsKeyPressed(EKeyCode::F5))
	{
		m_isGod = !m_isGod;
	}
	// END

	SelectInventorySlot();


#ifdef _DEBUG
	if (input.IsKeyPressed(EKeyCode::F8))
	{
		SetShouldSleep();
	}
#endif

	SetDirection(direction);

	sf::RectangleShape interactTile;
	interactTile.setFillColor(sf::Color(255,0,0,50));
	interactTile.setOutlineColor(sf::Color(150, 0, 0, 255));
	interactTile.setOutlineThickness(2);
	sf::Vector2f where = GetInteractPosition();
	where /= 64.f;
	where.x = (int)where.x;
	where.y = (int)where.y;
	where *= 64.f;
	interactTile.setPosition(where.x , where.y);
	interactTile.setSize({ 64, 64 });
	CRenderer::GetInstance().PushRenderCommand(interactTile, LAYER_UI);

	// DEBUG CODE
	sf::RectangleShape debugDot;
	debugDot.setSize({ 2,2 });
	debugDot.setPosition(GetInteractPosition());
	CRenderer::GetInstance().PushRenderCommand(debugDot, LAYER_UI);
	// END

	CRenderer::GetInstance().SetCameraTarget(GetPosition());

	m_inventory.RenderInventory();

	sf::Vector2f positionToRenderInventory;
	positionToRenderInventory.x = CRenderer::GetInstance().GetWindowDimensions().x - m_energyStatus.GetSize().x * 1.5f;
	positionToRenderInventory.y = CRenderer::GetInstance().GetWindowDimensions().y - m_energyStatus.GetSize().y * 1.5f;

	m_energyStatus.Render(positionToRenderInventory);

	if (input.IsKeyPressed(EKeyCode::MouseLeft))
	{
		CAudioManager::GetInstance().PlaySoundAtPosition("Shovel", -CRenderer::GetInstance().GetCamera().getSize() / 2.f + input.GetMousePosFloat() + CRenderer::GetInstance().GetCamera().getCenter());
		GetInventory().AddItemToInventory("PotatoSeeds", 5);
		GetInventory().AddItemToInventory("FlowerSeeds", 5);
	}
}

void CPlayer::BindFarm(CFarm & a_farm)
{
	m_farm = &a_farm;
}

void CPlayer::SetCurrentZone(CWorldZone & a_zone)
{
	m_currentZone = &a_zone;
}

void CPlayer::Faint()
{
	//Todo: Add meaningful faint logic here
	SetShouldSleep();
}

void CPlayer::DoInteraction()
{
	short heldItem = m_inventory.GetActiveSlotItemID();
	short targetedTile = m_currentZone->GetTileMap().ConvertPositionToTileIndex(GetInteractPosition());
	CInteractableItem* interactableObject = m_currentZone->GetTargetedObject(GetInteractPosition());

	if (interactableObject != nullptr)
	{
		interactableObject->Interact(*this);
	}
	else if (m_toolBank.UseActiveTool(*this, *m_currentZone))
	{
		CAudioManager::GetInstance().PlaySound(m_toolBank.GetActiveToolName());
	}
	else if (m_farm->TryHarvest(targetedTile, m_currentZone))
	{

	}
	else if (CItemBank::GetInstance().GetItem(heldItem).IsSeed())
	{
		short seedID = CItemBank::GetInstance().GetItem(heldItem).GetSeedID();

		if (m_currentZone->GetTileMap().TileIsPlowed(targetedTile) && m_farm->TileContainsSeed(targetedTile) == false)
		{
			m_farm->PlantSeed(seedID, targetedTile);
			m_inventory.AddItemToInventory(heldItem, -1);
		}
	}
}

void CPlayer::SelectInventorySlot()
{
	CInputManager& input = CInputManager::GetInstance();

	if (input.IsKeyPressed(EKeyCode::E))
	{
		m_inventory.ChangeActiveSlot(1);
	}
	if (input.IsKeyPressed(EKeyCode::Q))
	{
		m_inventory.ChangeActiveSlot(-1);
	}

	if (input.IsKeyPressed(EKeyCode::One)) { m_inventory.TrySetActiveSlot(0); }
	if (input.IsKeyPressed(EKeyCode::Two)) { m_inventory.TrySetActiveSlot(1); }
	if (input.IsKeyPressed(EKeyCode::Three)) { m_inventory.TrySetActiveSlot(2); }
	if (input.IsKeyPressed(EKeyCode::Four)) { m_inventory.TrySetActiveSlot(3); }
	if (input.IsKeyPressed(EKeyCode::Five)) { m_inventory.TrySetActiveSlot(4); }
	if (input.IsKeyPressed(EKeyCode::Six)) { m_inventory.TrySetActiveSlot(5); }
	if (input.IsKeyPressed(EKeyCode::Seven)) { m_inventory.TrySetActiveSlot(6); }
	if (input.IsKeyPressed(EKeyCode::Eight)) { m_inventory.TrySetActiveSlot(7); }
	if (input.IsKeyPressed(EKeyCode::Nine)) { m_inventory.TrySetActiveSlot(8); }
	if (input.IsKeyPressed(EKeyCode::Zero)) { m_inventory.TrySetActiveSlot(9); }
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
	m_isInputLocked = false;
	CGameEventMaster::GetInstance().SendGameEvent(EGameEvent::PlayerWakeup);
}

#include "GameEventMaster.h"
void CPlayer::SetShouldSleep()
{
	m_shouldSleep = true;
	CGameEventMaster::GetInstance().SendGameEvent(EGameEvent::PlayerSleep);
	m_isInputLocked = true;
}

sf::Vector2f CPlayer::GetInteractPosition() const
{
	sf::Vector2f interactPosition;
	interactPosition = GetPosition() + sf::Vector2f(16.f,32.f) + GetFacingDirection() * 64.f;

	return std::move(interactPosition);
}

void CPlayer::DrainEnergy(float a_drainage)
{
	if (!m_isGod)
	{
		m_energyStatus.AddToValue(a_drainage * -1.f);
	}
}


