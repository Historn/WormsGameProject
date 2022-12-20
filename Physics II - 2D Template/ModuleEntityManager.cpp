#include "ModuleEntityManager.h"
#include "Application.h"

ModuleEntityManager::ModuleEntityManager(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleEntityManager::~ModuleEntityManager()
{}

// Load assets
bool ModuleEntityManager::Start()
{
	LOG("Loading Entities");
	return true;
}

// Unload assets
bool ModuleEntityManager::CleanUp()
{
	LOG("Unloading Entities");

	p2List_item<Entity*>* item;
	Entity* entities = NULL;

	return true;
}

// Update: draw background
update_status ModuleEntityManager::Update()
{
	return UPDATE_CONTINUE;
}