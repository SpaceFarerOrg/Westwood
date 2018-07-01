#pragma once
#include <unordered_map>
#include <string>
#include <SFML/Audio.hpp>

class CSoundBank
{
public:
	CSoundBank();

	void LoadAllSounds(const char*  a_soundDataPath);
	const sf::SoundBuffer& GetSoundBuffer(const std::string& aSoundName);

private:

	std::unordered_map<std::string, sf::SoundBuffer> m_soundBuffers;
};

