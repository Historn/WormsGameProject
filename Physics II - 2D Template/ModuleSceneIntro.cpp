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
	playertwo = (ModulePlayerTwo*)app->entityManager->CreateEntity(EntityType::PLAYERTWO);
	weapon = (ModuleWeapon*)app->entityManager->CreateEntity(EntityType::WEAPON);

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
	
	if (app->input->GetKey(SDL_SCANCODE_F11) == KEY_DOWN)
		app->fullscreen = !app->fullscreen;

	app->renderer->Blit(map_img, 0, 0, NULL);

	// UI blit
	app->ui->BlitPlayerHP();
	app->ui->BlitPlayer2HP();

	// Debug UI info
	if (app->physics->debug)
	{
		// Blit UI
		app->ui->BlitPlayerXPos();
		app->ui->BlitPlayerYPos();

		app->ui->BlitPlayer2XPos();
		app->ui->BlitPlayer2YPos();

		app->ui->BlitFPS();
		app->ui->BlitGravityX();
		app->ui->BlitGravityY();
		app->ui->BlitWindX();
		app->ui->BlitWindY();
		app->ui->BlitAtmosphereDensity();
		app->ui->BlitDeltaTime();
		app->ui->BlitWindIsEnabled();

		//Changes FPS
		if (app->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN)
			app->fps++;
		if (app->input->GetKey(SDL_SCANCODE_F) == KEY_DOWN)
			app->fps--;

		//Changes GRAVITY X
		if (app->input->GetKey(SDL_SCANCODE_T) == KEY_DOWN)
			app->physics->gravity.x += .5f;
		if (app->input->GetKey(SDL_SCANCODE_G) == KEY_DOWN)
			app->physics->gravity.x -= .5f;
		//Changes GRAVITY Y
		if (app->input->GetKey(SDL_SCANCODE_Y) == KEY_DOWN)
			app->physics->gravity.y += .5f;
		if (app->input->GetKey(SDL_SCANCODE_H) == KEY_DOWN)
			app->physics->gravity.y -= .5f;

		//Changes WIND X
		if (app->input->GetKey(SDL_SCANCODE_Z) == KEY_DOWN)
			app->physics->atmosphere.windx -= .5f;
		if (app->input->GetKey(SDL_SCANCODE_X) == KEY_DOWN)
			app->physics->atmosphere.windx += .5f;
		//Changes WIND Y
		if (app->input->GetKey(SDL_SCANCODE_C) == KEY_DOWN)
			app->physics->atmosphere.windy -= .5f;
		if (app->input->GetKey(SDL_SCANCODE_V) == KEY_DOWN)
			app->physics->atmosphere.windy += .5f;

		//Changes ATMOSPHERE DENSITY
		if (app->input->GetKey(SDL_SCANCODE_B) == KEY_DOWN)
			app->physics->atmosphere.density -= .5f;
		if (app->input->GetKey(SDL_SCANCODE_N) == KEY_DOWN)
			app->physics->atmosphere.density += .5f;

		//Changes DELTA TIME SCHEME
		if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN)
			app->physics->dtValue -= 10.0f;
		if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN)
			app->physics->dtValue += 10.0f;
	}
	
	// Enable/Disable WIND force
	if (app->input->GetKey(SDL_SCANCODE_P) == KEY_DOWN)
		app->physics->windEnabled = !app->physics->windEnabled;


	//Player1
	if (player->isAiming == true) {
		app->ui->BlitPlayerAngle();
		app->ui->BlitPlayerVelocity();
		app->renderer->DrawLine(METERS_TO_PIXELS(player->pbody->x), SCREEN_HEIGHT - METERS_TO_PIXELS(player->pbody->y), METERS_TO_PIXELS(player->pbody->x + (player->projVel * cos(DEGTORAD * player->projAngle))), SCREEN_HEIGHT - METERS_TO_PIXELS(player->pbody->y + (player->projVel * sin(DEGTORAD * player->projAngle))), 255, 0, 0);
	}
	//Player2
	if (playertwo->isAiming == true) {
		app->ui->BlitPlayer2Angle();
		app->ui->BlitPlayer2Velocity();
		app->renderer->DrawLine(METERS_TO_PIXELS(playertwo->pbody->x), SCREEN_HEIGHT - METERS_TO_PIXELS(playertwo->pbody->y), METERS_TO_PIXELS(playertwo->pbody->x + (playertwo->projVel * cos(DEGTORAD * playertwo->projAngle))), SCREEN_HEIGHT - METERS_TO_PIXELS(playertwo->pbody->y + (playertwo->projVel * sin(DEGTORAD * playertwo->projAngle))), 255, 0, 0);
	}

	/*Projectile Shot --> Sets here the momentum initial Pos and Vel*/
	//Player1
	if (app->scene_intro->player->playershoots == true) {
		projectile = (ModuleProjectile*)app->entityManager->CreateEntity(EntityType::PROJECTILE);
		projectile->pbody->x = player->pbody->x + (player->pbody->radius * 2);
		projectile->pbody->y = player->pbody->y;
		projectile->pbody->vx = player->projVel * cos(DEGTORAD * player->projAngle);
		projectile->pbody->vy = player->projVel * sin(DEGTORAD * player->projAngle);
		app->scene_intro->player->playershoots = false;
		app->scene_intro->playertwo->isTurn = true;
	}

	//Player2
	if (app->scene_intro->playertwo->playershoots == true) {
		projectile = (ModuleProjectile*)app->entityManager->CreateEntity(EntityType::PROJECTILE);
		projectile->pbody->x = playertwo->pbody->x - (playertwo->pbody->radius * 2);
		projectile->pbody->y = playertwo->pbody->y;
		projectile->pbody->vx = playertwo->projVel * cos(DEGTORAD * playertwo->projAngle);
		projectile->pbody->vy = playertwo->projVel * sin(DEGTORAD * playertwo->projAngle);
		app->scene_intro->playertwo->playershoots = false;
		app->scene_intro->player->isTurn = true;
	}


	if (app->scene_intro->player->dead == true) {
		app->fade->FadeBlack(this, (Module*)app->ending_screen, 90);
	}


	if (app->scene_intro->playertwo->dead == true) {
		app->fade->FadeBlack(this, (Module*)app->ending_screen, 90);
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
	app->entityManager->Disable();
	app->physics->Disable();

	app->textures->Unload(map_img);

	return true;
}


