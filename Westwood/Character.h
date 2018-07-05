#pragma once
#include <SFML\Graphics\Sprite.hpp>
#include <vector>
#include <array>
#include <SFML\Graphics\RenderTexture.hpp>

class CCharacter
{
public:
	enum EBodyParts
	{
		LeftArm,
		RightLeg,
		Torso,
		LeftLeg,
		RightArm,
		Count,
	};
private:
	struct SFrame
	{
		SFrame()
		{
			for (float& rot : m_targetRotations)
			{
				rot = 0.f;
			}
		}

		float& operator[](size_t a_index)
		{
			return m_targetRotations[a_index];
		}

		std::array<float, EBodyParts::Count> m_targetRotations;
	};
public:
	void LoadCharacter(const char* a_textureFile, const char* a_characterFile);

	void Update(float a_dt);
	void Render(const sf::Vector2f& a_position);

	void OverrideBodyPart(EBodyParts a_partToOverride, float a_rotation);
	void HandBackBodyPart(EBodyParts a_partToHandBack);

	void SetDirection(short a_direction);

	void HoldItem(short a_itemID);
private:
	void UpdatePart(size_t a_part, float a_dt);
	bool IsFrameDoneForPart(size_t a_part);

	std::array < sf::Sprite, static_cast<size_t>(EBodyParts::Count)> m_sprites;
	std::array<float, static_cast<size_t>(EBodyParts::Count)> m_rotations;
	std::array<float, EBodyParts::Count> m_overrideRotations;
	std::array<bool, EBodyParts::Count> m_isOverride;
	std::array<bool, EBodyParts::Count> m_isHandedBack;

	std::vector<SFrame> m_frames;

	sf::Vector2f m_carryPosition;
	sf::Sprite m_sprite;
	sf::RenderTexture m_renderTexture;

	short m_carriedObject;
	
	short m_currentFrame;

	short m_direction;

	float m_rotationSpeed;

	bool m_isCarryingObject;
};