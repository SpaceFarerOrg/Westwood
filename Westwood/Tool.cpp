#include "Tool.h"
#include "Player.h"

void ITool::Use(CPlayer & a_user, CWorldZone& a_zone)
{
	a_user.DrainEnergy(m_energyDrainage);
}

const std::string & ITool::GetItemName()
{
	return m_name;
}
