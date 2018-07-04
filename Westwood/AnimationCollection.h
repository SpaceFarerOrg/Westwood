#pragma once
#include <unordered_map>
#include "Animation.h"

class CAnimationCollection
{
public:
	void LoadAnimationIntoCollection(const char* a_animationFilePath, size_t a_stateToBindTo);
	void SetCurrentState(size_t a_state);
	void Update(float a_deltaTime);
	void Render(const sf::Vector2f& a_position);

	CAnimation& GetCurrentAnimation();
private:
	std::unordered_map<size_t, CAnimation> m_animations;
	size_t m_currentState;

};