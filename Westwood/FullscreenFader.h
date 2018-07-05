#pragma once
#include <SFML\Graphics\Color.hpp>

class CFullscreenFader
{
public:
	CFullscreenFader();
	void Update(float a_dt);

	bool GetIsFading() const;
private:
	void StartFade();

	sf::Color m_currentColor;
	float m_alpha;
	float m_originalMusicVolume;
	bool m_isFadingOut : 1;
	bool m_isFading : 1;
};