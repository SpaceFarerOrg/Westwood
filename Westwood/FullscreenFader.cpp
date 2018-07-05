#include "FullscreenFader.h"
#include "GameEventMaster.h"
#include "Math.h"
#include <SFML\Graphics\Rect.hpp>
#include "Renderer.h"
#include "AudioManager.h"

CFullscreenFader::CFullscreenFader()
{
	CGameEventMaster::GetInstance().SubscribeToEvent(EGameEvent::PlayerSleep, [this] {this->StartFade(); });

	m_currentColor = sf::Color::Black;
}

void CFullscreenFader::Update(float a_dt)
{

	if (GetIsFading())
	{
		if (!m_isFadingOut)
		{
			m_alpha += a_dt * 255.f;
		}
		else
		{
			m_alpha -= a_dt * 255.f;
		}

		m_alpha = Math::Clamp<float>(m_alpha, 0.f, 255.f);

		CAudioManager::GetInstance().SetMusicVolume((1.f-(m_alpha / 255.f)) * m_originalMusicVolume);

		m_currentColor.a = static_cast<short>(m_alpha);

		if (m_alpha == 0.f)
		{
			CGameEventMaster::GetInstance().SendGameEvent(EGameEvent::FadeFinished);
			m_isFading = false;
		}
		else if (m_alpha == 255.f)
		{
			m_isFadingOut = true;
			CGameEventMaster::GetInstance().SendGameEvent(EGameEvent::FadeReachBlack);
		}
		
		sf::RectangleShape fullscreenRect;
		fullscreenRect.setSize(CRenderer::GetInstance().GetWindowDimensions());
		fullscreenRect.setFillColor(m_currentColor);

		CRenderer::GetInstance().PushUIRenderCommand(fullscreenRect);
	}

}

bool CFullscreenFader::GetIsFading() const
{
	return m_isFading;
}

void CFullscreenFader::StartFade()
{
	m_isFading = true;
	m_isFadingOut = false;
	m_currentColor.a = 0;
	m_alpha = 0.f;
	m_originalMusicVolume = CAudioManager::GetInstance().GetMusicVolume();
}
