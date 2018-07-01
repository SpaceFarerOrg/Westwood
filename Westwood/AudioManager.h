#pragma once
#include "SoundBank.h"
#include <array>

class CAudioManager
{
public:
	CAudioManager();

	static CAudioManager& GetInstance();

	void Load();

	void PlaySound(const char* a_soundName);

private:
	~CAudioManager();

	CSoundBank m_soundBank;

	std::array<sf::Sound, 256> m_soundBuffer;
	short m_availableIndex;
};

