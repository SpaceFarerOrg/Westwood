#pragma once
#include "UIButton.h"
#include <vector>

class CButtonManager
{
public:
	CButtonManager();
	~CButtonManager();

	CUIButton& AddButton();
	void Update();
	void Render();

private:
	std::vector<CUIButton> m_buttons;
};

