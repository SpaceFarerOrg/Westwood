#pragma once
#include <unordered_map>
#include <string>
#include <SFML/Audio.hpp>

class CSoundBank
{
public:
	CSoundBank();

	void LoadAllSounds(const char*  a_soundDataPath);
	const sf::SoundBuffer& GetSoundBuffer(const std::string& a_SoundName);
	bool SoundExists(const std::string& a_soundName);

private:
	struct SSoundBufferGroup
	{
		std::vector<sf::SoundBuffer> m_soundBuffers;
	};

	std::unordered_map<std::string, SSoundBufferGroup> m_soundGroups;
};

