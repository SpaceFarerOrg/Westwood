#include "SoundBank.h"
#include "json.hpp"
#include <fstream>

CSoundBank::CSoundBank()
{
}

void CSoundBank::LoadAllSounds(const char * a_soundDataPath)
{
	nlohmann::json soundsJson;
	std::fstream soundsFile(a_soundDataPath);
	soundsFile >> soundsJson;
	soundsFile.close();

	short amountOfSounds = static_cast<short>(soundsJson["sounds"].size());
	m_soundBuffers.reserve(amountOfSounds);

	for (short i = 0; i < amountOfSounds; ++i)
	{
		std::string name = soundsJson["sounds"][i]["name"];
		m_soundBuffers.insert(std::make_pair(name, sf::SoundBuffer()));

		m_soundBuffers[name].loadFromFile(soundsJson["sounds"][i]["path"]);
	}
}

const sf::SoundBuffer & CSoundBank::GetSoundBuffer(const std::string & aSoundName)
{
	return m_soundBuffers[aSoundName];
}
