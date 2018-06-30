#pragma once

class CPlayer;

class IUseable
{
public:
	virtual void Init() = 0;
	virtual void Use(CPlayer& a_user) = 0;

	short GetItemID() const
	{
		return m_itemID;
	};
protected:
	short m_itemID;
};