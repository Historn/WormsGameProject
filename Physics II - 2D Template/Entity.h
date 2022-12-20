#ifndef _Entity_H
#define _Entity_H

#include "Application.h"
#include "Globals.h"
#include "SString.h"


enum class EntityType
{
	PLAYER,
	ENEMY,
	FLYING_ENEMY,
	ITEM,
	COIN,
	UNKNOWN
};

class Entity 
{
public:

	Entity(EntityType type) : type(type), active(true) {}

	virtual bool Start()
	{
		return true;
	}

	virtual bool PreUpdate()
	{
		return true;
	}

	virtual bool Update()
	{
		return true;
	}

	virtual bool PostUpdate()
	{
		return true;
	}

	virtual bool CleanUp()
	{
		return true;
	}

	virtual bool LoadState(pugi::xml_node&)
	{
		return true;
	}

	virtual bool SaveState(pugi::xml_node&)
	{
		return true;
	}

	void Entity::Enable()
	{
		if (!active)
		{
			active = true;
			Start();
		}
	}

	void Entity::Disable()
	{
		if (active)
		{
			active = false;
			CleanUp();
		}
	}

	virtual void OnCollision(PhysBody* physA, PhysBody* physB) {

	};

public:

	SString name;
	EntityType type;
	bool active = true;
	pugi::xml_node parameters;

};

#endif // !_Entity_H

