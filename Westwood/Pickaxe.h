#pragma once
#include "Tool.h"

class CPickaxe : public ITool
{
public:
	void Init() override;
	void Use(CPlayer& a_user) override;
};