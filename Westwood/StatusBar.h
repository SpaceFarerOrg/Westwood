#pragma once
#include <SFML\System\Vector2.hpp>
#include <SFML\Graphics\Color.hpp>
#include <functional>

class CStatusBar
{
public:
	enum class EType
	{
		vertical,
		horizontal,
	};
public:
	CStatusBar();
	void Init(float a_maxValue, float a_width, float a_height, EType a_type);
	void BindCallbackToOnEmpty(std::function<void()> a_callbackOnEmpty);
	void SetToMax();
	void AddToValue(float a_valueToAdd);
	
	sf::Vector2f GetSize() const;
	
	void Render(const sf::Vector2f& a_positionInUI);
private:
	std::function<void()> m_callbackOnEmpty;

	float m_width;
	float m_height;
	float m_maxValue;
	float m_value;
	EType m_type;

	bool m_hasCallback : 1;
};