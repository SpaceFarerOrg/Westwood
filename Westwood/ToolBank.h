#pragma once
#include "Tool.h"
#include <array>

//Actual Tools
#include "Shovel.h"
#include "Axe.h"
#include "Pickaxe.h"
#include "WaterCan.h"

class CPlayer;

class CToolBank
{
public:
	void InitTools();

	void SetRelevantToolAsActive(short a_currentActiveItemID);

	void UseActiveTool(CPlayer& a_user);
private:
	void AddToolAsRawTool(ITool& a_tool, EToolType a_toolType);
	std::array<ITool*, static_cast<size_t>(EToolType::Count)> m_rawTools;
	short m_activeTool;

	CShovel m_shovel;
	CAxe m_axe;
	CPickaxe m_pickaxe;
	CWaterCan m_waterCan;
};