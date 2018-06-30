#include "Bed.h"
#include "Player.h"

CBed::CBed()
{
	sf::IntRect textureRect;
	textureRect.left = 0;
	textureRect.top = 0;
	textureRect.width = 192;
	textureRect.height = 192;
	Init(192.f, 192.f, textureRect);
}

void CBed::Interact(CPlayer& a_user)
{
	a_user.SetShouldSleep();
}