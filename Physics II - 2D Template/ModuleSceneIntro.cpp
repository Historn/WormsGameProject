#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "ModuleEntityManager.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModulePhysics.h"
#include "ModuleInput.h"
#include "FadeToBlack.h"
#include "ModuleAudio.h"
#include "UI.h"



ModuleSceneIntro::ModuleSceneIntro(bool start_enabled) : Module(start_enabled)
{
	name.Create("ModuleSceneIntro");
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	/*INITIALIZE ENTITIES*/
	player = (ModulePlayer*)app->entityManager->CreateEntity(EntityType::PLAYER);

	app->renderer->camera.x = app->renderer->camera.y = 0;

	// Enable modules
	app->physics->Enable();
	app->entityManager->Enable();

	app->audio->PlayMusic("Assets/Audio/Music/MainScreen.ogg");

	map_img = app->textures->Load("Assets/Textures/PotentialMap.png");

	return ret;
}

// Update: draw background
update_status ModuleSceneIntro::PreUpdate()
{

	return UPDATE_CONTINUE;
}

update_status ModuleSceneIntro::Update()
{
	
	if (app->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN)
		app->fade->FadeBlack(this, (Module*)app->title_screen, 90);

	app->renderer->Blit(map_img, 0, 0, NULL);

	// UI blit
	app->ui->BlitPlayerHP();

	if (app->physics->debug)
	{
		app->ui->BlitPlayerXPos();
		app->ui->BlitPlayerYPos();
		app->ui->BlitPlayerAngle();
		app->ui->BlitPlayerVelocity();
	}

	if (app->scene_intro->player->playershoots == true) {
		projectile = (ModuleProjectile*)app->entityManager->CreateEntity(EntityType::PROJECTILE);
	}

	if (app->scene_intro->player->isTurn == true) {
		weapon = (ModuleWeapon*)app->entityManager->CreateEntity(EntityType::WEAPON);
	}

	return UPDATE_CONTINUE;
}

update_status ModuleSceneIntro::PostUpdate()
{


	return UPDATE_CONTINUE;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	// Disable modules
	app->physics->Disable();

	app->textures->Unload(map_img);

	return true;
}


