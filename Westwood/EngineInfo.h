#pragma once
#include <SFML\System\String.hpp>

class CEngineInfo
{
public:
	struct SVersion
	{
		SVersion(short a_major, short a_minor, short a_patch)
		{
			m_major = a_major;
			m_minor = a_minor;
			m_patch = a_patch;
		}

		void operator=(const SVersion& a_version)
		{
			m_major = a_version.m_major;
			m_minor = a_version.m_minor;
			m_patch = a_version.m_patch;
		}

		sf::String GetVersionString()
		{
			sf::String versionString = "";
			versionString += std::to_string(m_major);
			versionString += ".";
			versionString += std::to_string(m_minor);
			versionString += ".";
			versionString += std::to_string(m_patch);

			return std::move(versionString);
		}

	private:
		short m_major;
		short m_minor;
		short m_patch;
	};
public:
	CEngineInfo();
	void CalculateFPS(float a_currentDeltaTime);
	void RenderInfo();
private:
	SVersion m_version;
	short m_currentFPS;
	
};