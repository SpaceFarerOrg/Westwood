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
	m_soundGroups.reserve(amountOfSounds);

	for (short i = 0; i < amountOfSounds; ++i)
	{
		std::string name = soundsJson["sounds"][i]["name"];
		m_soundGroups.insert(std::make_pair(name, SSoundBufferGroup()));

		for (int j = 0; j < soundsJson["sounds"][i]["paths"].size(); ++j)
		{
			m_soundGroups[name].m_soundBuffers.push_back(sf::SoundBuffer());
			m_soundGroups[name].m_soundBuffers.back().loadFromFile(soundsJson["sounds"][i]["paths"][j]);
		}
	}
}

const sf::SoundBuffer & CSoundBank::GetSoundBuffer(const std::string & aSoundName)
{
	const std::vector<sf::SoundBuffer>& group = m_soundGroups[aSoundName].m_soundBuffers;
	return group[rand() % group.size()];
}
