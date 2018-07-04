#include "Animation.h"
#include "Math.h"
#include "Renderer.h"
#include <SFML\Graphics\Sprite.hpp>

CAnimation::CAnimation()
{
	Stop();
}


void CAnimation::AddFrame(const SFrame & a_frame)
{
	m_frames.push_back(a_frame);
}

void CAnimation::BindTexture(const sf::Texture& a_texture)
{
	m_texture = &a_texture;
}

void CAnimation::Update(float a_dt)
{
	m_currentFrameTime += a_dt;

	SFrame& currentFrame = m_frames[m_currentFrame];

	if (m_currentFrameTime >= currentFrame.m_timeToShow)
	{
		m_currentFrameTime -= currentFrame.m_timeToShow;
		ChangeFrame();
	}
}

void CAnimation::Render(const sf::Vector2f& a_position)
{
	sf::Sprite sprite;
	sprite.setTexture(*m_texture);
	sprite.setTextureRect(m_frames[m_currentFrame].m_rect);
	sprite.setPosition(a_position);

	CRenderer::GetInstance().PushRenderCommand(sprite);
}

bool CAnimation::IsPlaying() const
{
	return m_isPlaying;
}

void CAnimation::Play(EPlayMode a_playMode)
{
	m_isPlaying = true;
}

void CAnimation::Pause()
{
	m_isPlaying = false;
}

void CAnimation::Stop()
{
	m_currentFrameTime = 0.f;
	m_currentFrame = 0;
	Pause();
}

void CAnimation::ChangeFrame()
{
	if (m_currentPlayMode == EPlayMode::OneShot)
	{
		if (m_currentFrame + 1 == static_cast<short>(m_frames.size()))
		{
			Stop();
		}
	}
	else if (m_currentPlayMode == EPlayMode::Looping)
	{
		m_currentFrame += 1;

		if (m_currentFrame == static_cast<short>(m_frames.size()))
		{
			m_currentFrame = 0;
		}
	}
}
