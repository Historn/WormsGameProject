#ifndef _ModuleEntityManager_H
#define _ModuleEntityManager_H

#include "Module.h"
#include "Globals.h"
#include "Entity.h"
#include "p2List.h"

class ModuleEntityManager : public Module 
{
public:

	ModuleEntityManager(Application* app, bool start_enabled = true);

	virtual ~ModuleEntityManager();

	bool Start();
	update_status Update();
	bool CleanUp();

private:

	p2List<Entity*> listEntities;

public:

}
#endif //_MODULEENTITYMANAGER_H