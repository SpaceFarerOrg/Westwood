#include "ToolBank.h"

void CToolBank::InitTools()
{
	m_shovel.Init();
	m_axe.Init();
	m_pickaxe.Init();
	m_waterCan.Init();
	
	AddToolAsRawTool(m_shovel, EToolType::Shovel);
	AddToolAsRawTool(m_axe, EToolType::Axe);
	AddToolAsRawTool(m_pickaxe, EToolType::Pickaxe);
	AddToolAsRawTool(m_waterCan, EToolType::WaterCan);
}

void CToolBank::SetRelevantToolAsActive(short a_currentActiveItemID)
{
	m_activeTool = -1;

	for (size_t i = 0; i < m_rawTools.max_size(); ++i)
	{
		if (m_rawTools[i]->GetItemID() == a_currentActiveItemID)
		{
			m_activeTool = static_cast<short>(i);
			break;
		}
	}
}

void CToolBank::UseActiveTool(CPlayer & a_user)
{
	if (m_activeTool == -1)
		return;

	m_rawTools[m_activeTool]->Use(a_user);
}

void CToolBank::AddToolAsRawTool(ITool & a_tool, EToolType a_toolType)
{
	m_rawTools[static_cast<size_t>(a_toolType)] = &a_tool;
}
