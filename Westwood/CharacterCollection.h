#pragma once
#include <unordered_map>
#include "Character.h"

class CCharacterCollection
{
public:
	void Update(float a_dt);
	void Render(const sf::Vector2f& a_position);
	
	void AddCharacterToCollection(const char* a_textureFile, const char* a_characterFile, size_t a_stateToBindTo, short a_direction);

	void SetCurrentState(size_t a_state);
	CCharacter& GetCurrentCharacter();
	const CCharacter& GetCurrentCharacter() const;
private:

	std::unordered_map<size_t, CCharacter> m_collection;
	size_t m_currentState;
};