#pragma once
#include "Tool.h"

class CWaterCan : public ITool
{
public:
	void Init() override;
	void Use(CPlayer& a_user) override;
};