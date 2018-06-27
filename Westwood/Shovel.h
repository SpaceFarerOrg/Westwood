#pragma once
#include "Tool.h"

class CShovel : public ITool
{
public:
	void Init() override;
	void Use(CAvatar& a_user) override;
};
