#include "AnimationCollection.h"

void CAnimationCollection::LoadAnimationIntoCollection(const char * a_animationFilePath, size_t a_stateToBindTo)
{
	m_animations[a_stateToBindTo].LoadFromJson(a_animationFilePath);
}

void CAnimationCollection::SetCurrentState(size_t a_state)
{
	if (a_state == m_currentState)
	{
		return;
	}

	m_animations[m_currentState].Stop();

	if (m_animations.find(a_state) != m_animations.end())
	{
		m_currentState = a_state;
	}

	m_animations[m_currentState].Play(CAnimation::EPlayMode::Looping);
}

void CAnimationCollection::Update(float a_deltaTime)
{
	m_animations[m_currentState].Update(a_deltaTime);
}

void CAnimationCollection::Render(const sf::Vector2f & a_position)
{
	m_animations[m_currentState].Render(a_position);
}

CAnimation & CAnimationCollection::GetCurrentAnimation()
{
	return m_animations[m_currentState];
}

const CAnimation & CAnimationCollection::GetCurrentAnimation() const
{
	return m_animations.at(m_currentState);
}

