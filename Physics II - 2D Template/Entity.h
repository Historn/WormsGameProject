#ifndef _Entity_H
#define _Entity_H

#include "Globals.h"
#include "SString.h"
#include "p2Point.h"

class PhysBody;

enum class EntityType
{
	PLAYER,
	PLAYERTWO,
	ENEMY,
	FLYING_ENEMY,
	ITEM,
	COIN,
	WEAPON,
	PROJECTILE,
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

	virtual update_status PreUpdate()
	{
		return UPDATE_CONTINUE;
	}

	virtual update_status Update()
	{
		return UPDATE_CONTINUE;
	}

	virtual update_status PostUpdate()
	{
		return UPDATE_CONTINUE;
	}

	virtual bool CleanUp()
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
	
	// Possible properties, it depends on how generic we
	// want our Entity class, maybe it's not renderable...
	iPoint position;
	bool renderable = true;
};


#endif // !_Entity_H

