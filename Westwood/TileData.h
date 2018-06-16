#pragma once
#include "TileInteraction.h"

struct STileData
{
	operator short() const { return m_tileIndex; };
	void operator =(short a_index) { m_tileIndex = a_index; };

	ETileInteraction m_allowedInteraction;
	short m_tileIndex;
	bool m_isPassable : 1;
};