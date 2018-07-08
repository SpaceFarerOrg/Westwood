#include "EngineInfo.h"
#include "Renderer.h"
#include "TextureBank.h"

CEngineInfo::CEngineInfo()
	: m_version(0,0,1)
{
	m_currentFPS = 0;
}

void CEngineInfo::CalculateFPS(float a_currentDeltaTime)
{
	m_currentFPS = static_cast<short>(1.f / a_currentDeltaTime);
}

void CEngineInfo::RenderInfo()
{
	sf::Text engineInfo;
	engineInfo.setFont(CTextureBank::GetFont(EFonts::Debug));
	engineInfo.setFillColor(sf::Color::White);
	engineInfo.setOutlineColor(sf::Color::Black);
	engineInfo.setOutlineThickness(2.f);

	sf::String infoString = "";
	infoString += "Version: " + m_version.GetVersionString() += "\n";
	infoString += "FPS: " + std::to_string(m_currentFPS);

	engineInfo.setString(infoString);
	
	CRenderer::GetInstance().PushUIRenderCommand(engineInfo);
}
