#include "Animation.h"
#include "Math.h"
#include "Renderer.h"
#include <SFML\Graphics\Sprite.hpp>
#include "CommonUtilities.h"
#include "TextureBank.h"

CAnimation::CAnimation()
{
	Stop();
}


void CAnimation::LoadFromJson(const char* a_filePath)
{
	nlohmann::json json = OpenJson(a_filePath);

	std::string textureName = json["texture"];
	short textureIndex = CTextureBank::LoadUnorderedTexture(textureName.c_str());
	m_texture = &CTextureBank::GetUnorderedTexture(textureIndex);

	short frameSizeX = json["width"].get<short>();
	short frameSizeY = json["height"].get<short>();
	short frameCountX = m_texture->getSize().x / frameSizeX;

	sf::IntRect rect;
	rect.width = frameSizeX;
	rect.height = frameSizeY;

	for (size_t i = 0; i < json["frames"].size(); ++i)
	{
		short frameIndex = json["frames"][i]["frameIndex"].get<short>();
		short frameX = frameIndex % frameCountX;
		short frameY = frameIndex / frameCountX;

		rect.left = frameX * frameSizeX;
		rect.top = frameY * frameSizeY;

		SFrame frameToAdd;
		frameToAdd.m_rect = rect;
		frameToAdd.m_timeToShow = json["frames"][i]["time"].get<float>();

		AddFrame(frameToAdd);
	}
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

	CRenderer::GetInstance().PushRenderCommand(sprite, LAYER_OBJECT);
}

sf::Vector2f CAnimation::GetCenterOfCurrentFrame(const sf::Vector2f& a_worldPosition) const
{
	sf::Vector2f returnVector;
	returnVector.x = static_cast<float>(m_frames[m_currentFrame].m_rect.width / 2);
	returnVector.y = static_cast<float>(m_frames[m_currentFrame].m_rect.height / 2);

	returnVector += a_worldPosition;

	return std::move(returnVector);
}

bool CAnimation::IsPlaying() const
{
	return m_isPlaying;
}

void CAnimation::Play(EPlayMode a_playMode)
{
	m_isPlaying = true;
	m_currentPlayMode = a_playMode;
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
