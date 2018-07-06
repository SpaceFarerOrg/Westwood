#include "Character.h"
#include "TextureBank.h"
#include "Renderer.h"
#include "Math.h"
#include "CommonUtilities.h"
#include "ItemBank.h"
#include <SFML\Graphics\RenderTexture.hpp>

void CCharacter::LoadCharacter(const char * a_textureFile, const char * a_characterFile)
{
	m_carriedObject = 0;
	m_rotationSpeed = 150.f;
	m_direction = 1;

	short textureIndex = CTextureBank::LoadUnorderedTexture(a_textureFile);
	const sf::Texture& texture = CTextureBank::GetUnorderedTexture(textureIndex);

	for (size_t i = 0; i < EBodyParts::Count; ++i)
	{
		m_sprites[i].setTexture(texture);
		m_rotations[i] = 0.f;
		m_isOverride[i] = false;
		m_isHandedBack[i] = false;
	}

	m_sprites[EBodyParts::Torso].setTextureRect(sf::IntRect(0, 0, 64, 64));

	m_sprites[EBodyParts::LeftArm].setTextureRect(sf::IntRect(64, 0, 64, 64));
	m_sprites[EBodyParts::LeftArm].setOrigin(m_sprites[EBodyParts::LeftArm].getGlobalBounds().width / 2.f, 0.f);
	m_sprites[EBodyParts::RightArm].setTextureRect(sf::IntRect(64, 0, 64, 64));
	m_sprites[EBodyParts::RightArm].setOrigin(m_sprites[EBodyParts::RightArm].getGlobalBounds().width / 2.f, 0.f);

	m_sprites[EBodyParts::LeftLeg].setTextureRect(sf::IntRect(0, 64, 64, 64));
	m_sprites[EBodyParts::LeftLeg].setOrigin(m_sprites[EBodyParts::LeftLeg].getGlobalBounds().width / 2.f, 0.f);
	m_sprites[EBodyParts::RightLeg].setTextureRect(sf::IntRect(0, 64, 64, 64));
	m_sprites[EBodyParts::RightLeg].setOrigin(m_sprites[EBodyParts::RightLeg].getGlobalBounds().width / 2.f, 0.f);

	m_currentFrame = 0;

	nlohmann::json characterJson = OpenJson(a_characterFile);

	for (size_t i = 0; i < characterJson["frames"].size(); ++i)
	{
		m_frames.push_back(SFrame());
		SFrame& frameToLoad = m_frames.back();

		frameToLoad[EBodyParts::LeftArm] = characterJson["frames"][i]["lArmTargetRot"].get<float>();
		frameToLoad[EBodyParts::RightArm] = characterJson["frames"][i]["rArmTargetRot"].get<float>();
		frameToLoad[EBodyParts::LeftLeg] = characterJson["frames"][i]["lLegTargetRot"].get<float>();
		frameToLoad[EBodyParts::RightLeg] = characterJson["frames"][i]["rLegTargetRot"].get<float>();
	}

	m_sprite.setOrigin(64, 0);
	m_renderTexture.create(128, 128);
	m_renderTexture.clear(sf::Color::Transparent);
	m_sprite.setTexture(m_renderTexture.getTexture());
}

void CCharacter::Update(float a_dt)
{
	bool allPartsDone = true;
	for (size_t i = 0; i < EBodyParts::Count; ++i)
	{
		UpdatePart(i, a_dt);

		if (IsFrameDoneForPart(i) == false)
		{
			allPartsDone = false;
		}
	}

	if(allPartsDone == true)
	{
		m_currentFrame++;

		m_currentFrame %= static_cast<short>(m_frames.size());
	}
}

void CCharacter::Render(const sf::Vector2f & a_position)
{
	m_sprites[EBodyParts::Torso].setPosition(m_sprite.getOrigin().x - m_sprites[EBodyParts::Torso].getGlobalBounds().width / 2, 0);

	sf::Vector2f armPosition;
	armPosition.x = (m_sprite.getGlobalBounds().width / 2.f);
	armPosition.y = (m_sprites[EBodyParts::Torso].getGlobalBounds().height / 2.f);

	m_sprites[EBodyParts::LeftArm].setPosition(armPosition);
	m_sprites[EBodyParts::RightArm].setPosition(armPosition);

	sf::Vector2f legPosition;
	legPosition.x = m_sprite.getGlobalBounds().width / 2.f;
	legPosition.y = m_sprites[EBodyParts::Torso].getGlobalBounds().height - 8.f;
	m_sprites[EBodyParts::LeftLeg].setPosition(legPosition);
	m_sprites[EBodyParts::RightLeg].setPosition(legPosition);

	m_renderTexture.clear(sf::Color::Transparent);
	for (size_t i = 0; i < EBodyParts::Count; ++i)
	{
		m_sprites[i].setRotation(m_rotations[i]);
		m_renderTexture.draw(m_sprites[i]);

		//CRenderer::GetInstance().PushRenderCommand(m_sprites[i]);
	}
	m_renderTexture.display();
	m_sprite.setPosition(a_position);
	//m_sprite.setRotation(180.f * (m_direction == 1));
	m_sprite.setScale(m_direction, 1);
	CRenderer::GetInstance().PushRenderCommand(m_sprite, LAYER_OBJECT);

	m_carryPosition = a_position - m_sprite.getOrigin() + m_sprites[EBodyParts::RightArm].getTransform().transformPoint(32.f, 64.f - 16.f);

	CItemBank::GetInstance().RenderItemAsHeld(m_carriedObject, m_carryPosition, m_rotations[EBodyParts::RightArm], m_direction);
}

void CCharacter::OverrideBodyPart(EBodyParts a_partToOverride, float a_rotation)
{ 
	m_isOverride[a_partToOverride] = true;
	m_overrideRotations[a_partToOverride] = a_rotation;
}

void CCharacter::HandBackBodyPart(EBodyParts a_partToHandBack)
{
	m_isOverride[a_partToHandBack] = false;
	m_isHandedBack[a_partToHandBack] = true;
}

void CCharacter::SetDirection(short a_direction)
{
	m_direction = a_direction;
}

void CCharacter::HoldItem(short a_itemID)
{
	m_carriedObject = a_itemID;
}

void CCharacter::UpdatePart(size_t a_part, float a_dt)
{
	if (m_isOverride[a_part])
	{
		m_rotations[a_part] = Math::MoveTowards(m_rotations[a_part], m_overrideRotations[a_part], a_dt * m_rotationSpeed);
	}
	else
	{
		m_rotations[a_part] = Math::MoveTowards(m_rotations[a_part], m_frames[m_currentFrame][a_part], a_dt * m_rotationSpeed);

		if (m_rotations[a_part] == m_frames[m_currentFrame][a_part])
		{
			m_isHandedBack[a_part] = false;
		}
	}
}

bool CCharacter::IsFrameDoneForPart(size_t a_part)
{
	bool returnValue = false;

	if (m_isOverride[a_part] || m_isHandedBack[a_part])
	{
		returnValue = true;
	}
	else
	{
		if (m_rotations[a_part] == m_frames[m_currentFrame][a_part])
		{
			returnValue = true;
		}
	}

	return returnValue;
}
