#pragma once
#include <SFML\System\Vector2.hpp>
#include <SFML\Graphics\Rect.hpp>
#include <SFML\Graphics\Texture.hpp>
#include <vector>

class CAnimation
{
public:
	enum class EPlayMode
	{
		OneShot,
		Looping,
	};

	struct SFrame
	{
		sf::IntRect m_rect;
		float m_timeToShow;
	};
public:
	CAnimation();
	void AddFrame(const SFrame& a_frame);
	void BindTexture(const sf::Texture& a_texture);
	void Update(float a_dt);
	void Render(const sf::Vector2f& a_position);

	bool IsPlaying() const;
	void Play(EPlayMode a_playMode);
	void Pause();
	void Stop();
private:
	void ChangeFrame();

	std::vector<SFrame> m_frames;
	const sf::Texture* m_texture;

	EPlayMode m_currentPlayMode;
	float m_currentFrameTime;

	short m_currentFrame;

	bool m_isPlaying : 1;

};