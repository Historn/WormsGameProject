#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"

ModulePlayer::ModulePlayer() : Entity(EntityType::PLAYER){
	name.Create("ModulePlayer");
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");
	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	return true;
}


update_status ModulePlayer::PreUpdate()
{
	return UPDATE_CONTINUE;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	return UPDATE_CONTINUE;
}


update_status ModulePlayer::PostUpdate()
{
	return UPDATE_CONTINUE;
}



