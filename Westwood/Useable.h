#pragma once

class CPlayer;
class CWorldZone;

class IUseable
{
public:
	virtual void Init() = 0;
	virtual void Use(CPlayer& a_user, CWorldZone& a_zone) = 0;

	short GetItemID() const
	{
		return m_itemID;
	};
protected:
	short m_itemID;
};