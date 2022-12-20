#ifndef _MODULEENTITYMANAGER_H
#define _MODULEENTITYMANAGER_H

#include "Module.h"
#include "Globals.h"
#include "Entity.h"
#include "p2List.h"

class ModuleEntityManager : public Module
{
public:

	ModuleEntityManager(Application* app, bool start_enabled = true);
	~ModuleEntityManager();

	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

	// Additional methods
	Entity* CreateEntity(EntityType type);

	void DestroyEntity(Entity* entity);

	void AddEntity(Entity* entity);

private:

	p2List<Entity*> entities;

};

#endif //_MODULEENTITYMANAGER_H