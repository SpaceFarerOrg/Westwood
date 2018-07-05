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

	void PlayMusic(const std::string& a_musicName);

	void SetMusicVolume(float a_MusicVolume);
	float GetMusicVolume();

private:
	~CAudioManager();

	CSoundBank m_soundBank;

	std::array<sf::Sound, 255> m_soundBuffer;
	short m_availableIndex;

	sf::Vector2f m_positionOffset;

	sf::Music m_music;
};

