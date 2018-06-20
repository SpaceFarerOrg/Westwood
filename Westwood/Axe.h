#pragma once
#include "Tool.h"

class CAxe : public ITool
{
public:
	void Init() override;
	void Use(CAvatar& a_user) override;
};