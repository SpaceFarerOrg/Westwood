#pragma once
#include "Tool.h"

class CShovel : public ITool
{
public:
	void Init() override;
	void Use(CPlayer& a_user, CWorldZone& a_zone) override;
};
