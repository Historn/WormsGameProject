#include "Application.h"
#include "ModuleEntityManager.h"
#include "ModulePlayer.h"
#include "ModuleWeapon.h"
#include "ModuleProjectile.h"

ModuleEntityManager::ModuleEntityManager(bool start_enabled) : Module(start_enabled)
{
	name.Create("ModuleEntityManager");
}

ModuleEntityManager::~ModuleEntityManager()
{}

// Load assets
bool ModuleEntityManager::Start()
{
	LOG("Loading Entities");

	bool ret = true;

	//Iterates over the entities and calls Start
	p2List_item<Entity*>* item;
	Entity* pEntity = NULL;

	for (item = entities.getFirst(); item != NULL && ret == true; item = item->next)
	{
		pEntity = item->data;

		if (pEntity->active == false) continue;
		ret = item->data->Start();
	}

	return ret;

}

// Unload assets
bool ModuleEntityManager::CleanUp()
{
	LOG("Unloading Entities");

	bool ret = true;
	p2List_item<Entity*>* item;
	item = entities.getLast();

	while (item != NULL && ret == true)
	{
		ret = item->data->CleanUp();
		item = item->prev;
	}

	entities.clear();

	return ret;
}

Entity* ModuleEntityManager::CreateEntity(EntityType type)
{
	Entity* entity = nullptr;

	//L02: DONE 2: Instantiate entity according to the type and add the new entoty it to the list of Entities

	switch (type)
	{
	case EntityType::PLAYER:
		entity = new ModulePlayer();
		break;
	case EntityType::WEAPON:
		entity = new ModuleWeapon();
		break;
	case EntityType::PROJECTILE:
		entity = new ModuleProjectile();
		break;

	default: break;
	}

	// Created entities are added to the list
	AddEntity(entity);

	return entity;
}

void ModuleEntityManager::DestroyEntity(Entity* entity)
{
	p2List_item<Entity*>* item;

	for (item = entities.getFirst(); item != NULL; item = item->next)
	{
		if (item->data == entity) entities.del(item);
	}
}

void ModuleEntityManager::AddEntity(Entity* entity)
{
	if (entity != nullptr) entities.add(entity);
	entity->Start();
}

update_status ModuleEntityManager::PreUpdate()
{
	update_status ret = UPDATE_CONTINUE;
	p2List_item<Entity*>* item;
	Entity* pEntity = NULL;

	for (item = entities.getFirst(); item != NULL && ret == UPDATE_CONTINUE; item = item->next)
	{
		pEntity = item->data;

		if (pEntity->active == false) continue;
		ret = item->data->PreUpdate();
	}

	return ret;
}

// Update: draw background
update_status ModuleEntityManager::Update()
{
	update_status ret = UPDATE_CONTINUE;
	p2List_item<Entity*>* item;
	Entity* pEntity = NULL;

	for (item = entities.getFirst(); item != NULL && ret == UPDATE_CONTINUE; item = item->next)
	{
		pEntity = item->data;

		if (pEntity->active == false) continue;
		ret = item->data->Update();
	}

	return ret;

	return UPDATE_CONTINUE;
}

update_status ModuleEntityManager::PostUpdate()
{
	update_status ret = UPDATE_CONTINUE;
	p2List_item<Entity*>* item;
	Entity* pEntity = NULL;

	for (item = entities.getFirst(); item != NULL && ret == UPDATE_CONTINUE; item = item->next)
	{
		pEntity = item->data;

		if (pEntity->active == false) continue;
		ret = item->data->PostUpdate();
	}

	return ret;
}