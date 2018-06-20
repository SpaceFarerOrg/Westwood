#pragma once
#include "Tool.h"

class CPickaxe : public ITool
{
public:
	void Init() override;
	void Use(CAvatar& a_user) override;
};