#pragma once
#include "Tool.h"
#include <array>

//Actual Tools
#include "Shovel.h"
#include "Axe.h"
#include "Pickaxe.h"
#include "WaterCan.h"

class CPlayer;
class CWorldZone;

class CToolBank
{
public:
	void InitTools();

	void SetRelevantToolAsActive(short a_currentActiveItemID);
	const std::string& GetActiveToolName();

	bool UseActiveTool(CPlayer& a_user, CWorldZone& a_zone);
private:
	void AddToolAsRawTool(ITool& a_tool, EToolType a_toolType);
	std::array<ITool*, static_cast<size_t>(EToolType::Count)> m_rawTools;
	short m_activeTool;

	CShovel m_shovel;
	CAxe m_axe;
	CPickaxe m_pickaxe;
	CWaterCan m_waterCan;
};