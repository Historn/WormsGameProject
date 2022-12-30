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
	playerthree = (ModulePlayer*)app->entityManager->CreateEntity(EntityType::PLAYER);
	playerfour = (ModulePlayerTwo*)app->entityManager->CreateEntity(EntityType::PLAYERTWO);
	
	weapon = (ModuleWeapon*)app->entityManager->CreateEntity(EntityType::WEAPON);

	app->renderer->camera.x = app->renderer->camera.y = 0;

	// Enable modules
	app->physics->Enable();
	app->entityManager->Enable();

	app->audio->PlayMusic("Assets/Audio/Music/MainScreen.ogg");

	map_img = app->textures->Load("Assets/Textures/PotentialMap.png");


	playerthree->pbody->y = 18;
	playerthree->pbody->x = 6;
	playerthree->isTurn = false;
	playerfour->pbody->x = 34;
	playerfour->pbody->y = 19;

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

	//UI Blit
	app->ui->BlitPlayerHP();
	app->ui->BlitPlayer2HP();
	app->ui->BlitPlayer3HP();
	app->ui->BlitPlayer4HP();

	// Debug UI info
	if (app->physics->debug)
	{
		// Blit UI
		app->ui->BlitPlayerXPos();
		app->ui->BlitPlayerYPos();

		app->ui->BlitPlayer2XPos();
		app->ui->BlitPlayer2YPos();

		app->ui->BlitPlayer3XPos();
		app->ui->BlitPlayer3YPos();

		app->ui->BlitPlayer4XPos();
		app->ui->BlitPlayer4YPos();

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
	//Player3
	if (playerthree->isAiming == true) {
		app->ui->BlitPlayer3Angle(); //->Cambiar dentro crear un if para p1 y p3
		app->ui->BlitPlayer3Velocity();
		app->renderer->DrawLine(METERS_TO_PIXELS(playerthree->pbody->x), SCREEN_HEIGHT - METERS_TO_PIXELS(playerthree->pbody->y), METERS_TO_PIXELS(playerthree->pbody->x + (playerthree->projVel * cos(DEGTORAD * playerthree->projAngle))), SCREEN_HEIGHT - METERS_TO_PIXELS(playerthree->pbody->y + (playerthree->projVel * sin(DEGTORAD * playerthree->projAngle))), 255, 0, 0);
	}
	//Player4
	if (playerfour->isAiming == true) {
		app->ui->BlitPlayer4Angle();//->Cambiar dentro crear un if para p2 y p4
		app->ui->BlitPlayer4Velocity();
		app->renderer->DrawLine(METERS_TO_PIXELS(playerfour->pbody->x), SCREEN_HEIGHT - METERS_TO_PIXELS(playerfour->pbody->y), METERS_TO_PIXELS(playerfour->pbody->x + (playerfour->projVel * cos(DEGTORAD * playerfour->projAngle))), SCREEN_HEIGHT - METERS_TO_PIXELS(playerfour->pbody->y + (playerfour->projVel * sin(DEGTORAD * playerfour->projAngle))), 255, 0, 0);
	}

	ProjectileShot();

	if (app->scene_intro->player->dead == true && app->scene_intro->playerthree->dead == true) {
		app->fade->FadeBlack(this, (Module*)app->ending_screen, 90);
	}


	if (app->scene_intro->playertwo->dead == true && app->scene_intro->playerfour->dead == true) {
		app->fade->FadeBlack(this, (Module*)app->ending_screen, 90);
	}


	if (app->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN) {
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


void ModuleSceneIntro::ProjectileShot() {

	/*Projectile Shot --> Sets here the momentum initial Pos and Vel*/
	//Player1
	if (player->playershoots == true) {
		projectile = (ModuleProjectile*)app->entityManager->CreateEntity(EntityType::PROJECTILE);
		if(player->fliped == SDL_FLIP_HORIZONTAL)
			projectile->pbody->x = player->pbody->x + (player->pbody->radius * 2);
		if(player->fliped == SDL_FLIP_NONE)
			projectile->pbody->x = player->pbody->x - (player->pbody->radius * 2);
		projectile->pbody->y = player->pbody->y;
		projectile->pbody->vx = player->projVel * cos(DEGTORAD * player->projAngle);
		projectile->pbody->vy = player->projVel * sin(DEGTORAD * player->projAngle);
		player->playershoots = false;
		
		if(playertwo->dead == false)
			playertwo->isTurn = true;
		else if(playertwo->dead == true)
			playerfour->isTurn = true;
	}
	//Player2
	if (playertwo->playershoots == true) {
		projectile = (ModuleProjectile*)app->entityManager->CreateEntity(EntityType::PROJECTILE);
		if (playertwo->fliped == SDL_FLIP_HORIZONTAL)
			projectile->pbody->x = playertwo->pbody->x + (playertwo->pbody->radius * 2);
		if (playertwo->fliped == SDL_FLIP_NONE)
			projectile->pbody->x = playertwo->pbody->x - (playertwo->pbody->radius * 2);
		projectile->pbody->y = playertwo->pbody->y;
		projectile->pbody->vx = playertwo->projVel * cos(DEGTORAD * playertwo->projAngle);
		projectile->pbody->vy = playertwo->projVel * sin(DEGTORAD * playertwo->projAngle);
		playertwo->playershoots = false;

		if(playerthree->dead == false)
			playerthree->isTurn = true;
		else if(playerthree->dead == true)
			player->isTurn = true;
	}
	//Player3
	if (playerthree->playershoots == true) {
		projectile = (ModuleProjectile*)app->entityManager->CreateEntity(EntityType::PROJECTILE);
		if (playerthree->fliped == SDL_FLIP_HORIZONTAL)
			projectile->pbody->x = playerthree->pbody->x + (playerthree->pbody->radius * 2);
		if (playerthree->fliped == SDL_FLIP_NONE)
			projectile->pbody->x = playerthree->pbody->x - (playerthree->pbody->radius * 2);
		projectile->pbody->y = playerthree->pbody->y;
		projectile->pbody->vx = playerthree->projVel * cos(DEGTORAD * playerthree->projAngle);
		projectile->pbody->vy = playerthree->projVel * sin(DEGTORAD * playerthree->projAngle);
		playerthree->playershoots = false;

		if (playerfour->dead == false)
			playerfour->isTurn = true;
		else if (playerfour->dead == true)
			playertwo->isTurn = true;
	}
	//Player4
	if (playerfour->playershoots == true) {
		projectile = (ModuleProjectile*)app->entityManager->CreateEntity(EntityType::PROJECTILE);
		if (playerfour->fliped == SDL_FLIP_HORIZONTAL)
			projectile->pbody->x = playerfour->pbody->x + (playerfour->pbody->radius * 2);
		if (playerfour->fliped == SDL_FLIP_NONE)
			projectile->pbody->x = playerfour->pbody->x - (playerfour->pbody->radius * 2);
		projectile->pbody->y = playerfour->pbody->y;
		projectile->pbody->vx = playerfour->projVel * cos(DEGTORAD * playerfour->projAngle);
		projectile->pbody->vy = playerfour->projVel * sin(DEGTORAD * playerfour->projAngle);
		playerfour->playershoots = false;

		if (player->dead == false)
			player->isTurn = true;
		else if (player->dead == true)
			playerthree->isTurn = true;
	}


}