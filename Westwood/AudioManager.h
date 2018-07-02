#pragma once
#include "SoundBank.h"
#include <array>
#include <SFML/System/Vector2.hpp>

class CAudioManager
{
public:
	CAudioManager();

	static CAudioManager& GetInstance();

	void Load();
	void SetListenerPosition(const sf::Vector2f& a_position);

	void PlaySound(const std::string& a_soundName);
	void PlaySoundAtPosition(const std::string& a_soundName, const sf::Vector2f& a_position);

private:
	~CAudioManager();

	CSoundBank m_soundBank;

	std::array<sf::Sound, 256> m_soundBuffer;
	short m_availableIndex;

	sf::Vector2f m_positionOffset;
};

