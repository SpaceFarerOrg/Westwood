#include "ButtonManager.h"



CButtonManager::CButtonManager()
{
}


CButtonManager::~CButtonManager()
{
}

CUIButton & CButtonManager::AddButton()
{
	m_buttons.push_back(CUIButton());
	return m_buttons.back();
}

void CButtonManager::Update()
{
	for (CUIButton& button : m_buttons)
	{
		button.Update();
	}
}

void CButtonManager::Render()
{
	for (CUIButton& button : m_buttons)
	{
		button.Render();
	}
}
