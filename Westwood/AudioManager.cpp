#include "AudioManager.h"

CAudioManager::CAudioManager()
{
}

CAudioManager & CAudioManager::GetInstance()
{
	static CAudioManager instance;
	return instance;
}

void CAudioManager::Load()
{
	m_soundBank.LoadAllSounds("data/sounds.json");
	m_availableIndex = 0;
}

void CAudioManager::SetListenerPosition(const sf::Vector2f & a_position)
{
	m_positionOffset = a_position;
}

void CAudioManager::PlaySound(const char * a_soundName)
{
	PlaySoundAtPosition(a_soundName, m_positionOffset);
}

void CAudioManager::PlaySoundAtPosition(const char * a_soundName, const sf::Vector2f & a_position)
{
	sf::Vector3f position = { a_position.x - m_positionOffset.x, a_position.y - m_positionOffset.y, 0 };

	m_soundBuffer[m_availableIndex].setBuffer(m_soundBank.GetSoundBuffer(a_soundName));
	m_soundBuffer[m_availableIndex].setPosition(position);
	m_soundBuffer[m_availableIndex].play();

	m_availableIndex++;
	if (m_availableIndex == m_soundBuffer.size())
	{
		m_availableIndex = 0;
	}
}


CAudioManager::~CAudioManager()
{
}
