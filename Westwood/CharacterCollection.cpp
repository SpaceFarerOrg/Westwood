#include "CharacterCollection.h"

void CCharacterCollection::Update(float a_dt)
{
	m_collection[m_currentState].Update(a_dt);
}

void CCharacterCollection::Render(const sf::Vector2f & a_position)
{
	m_collection[m_currentState].Render(a_position);
}

void CCharacterCollection::AddCharacterToCollection(const char * a_textureFile, const char * a_characterFile, size_t a_stateToBindTo)
{
	m_collection[a_stateToBindTo].LoadCharacter(a_textureFile, a_characterFile);
	m_currentState = a_stateToBindTo;
}

void CCharacterCollection::SetCurrentState(size_t a_state)
{
	m_currentState = a_state;
}

CCharacter & CCharacterCollection::GetCurrentCharacter()
{
	return m_collection[m_currentState];
}
