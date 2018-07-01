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

void CAudioManager::PlaySound(const char * a_soundName)
{
	m_soundBuffer[m_availableIndex].setBuffer(m_soundBank.GetSoundBuffer(a_soundName));
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
