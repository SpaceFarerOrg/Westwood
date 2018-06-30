#pragma once
#include "InteractableItem.h"

class CBed : public CInteractableItem
{
public:
	CBed();
	void Interact(CPlayer& a_user) override;
};
