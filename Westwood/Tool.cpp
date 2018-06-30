#include "Tool.h"
#include "Player.h"

void ITool::Use(CPlayer & a_user)
{
	a_user.DrainEnergy(m_energyDrainage);
}
