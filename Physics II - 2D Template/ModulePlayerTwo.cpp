#include "Globals.h"
#include "Application.h"
#include "ModulePlayerTwo.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"
#include "FadeToBlack.h" 
#include "ModuleEntityManager.h"
#include "Entity.h"
#include "ModuleSceneIntro.h"



ModulePlayerTwo::ModulePlayerTwo() : Entity(EntityType::PLAYERTWO){
	name.Create("ModulePlayer2");
}

ModulePlayerTwo::~ModulePlayerTwo()
{}

// Load assets
bool ModulePlayerTwo::Start()
{
	LOG("Loading player2");

	//Cant use B2Vec2 cause no Box2D just do start pos as x,y
	startPos.x = 28;
	startPos.y = 2;

	//Textures Load
	texture = app->textures->Load("Assets/Textures/Worms_spritesheet_full.png");

	//Sounds
	RocketLaunchSFX = app->audio->LoadFx("Assets/Audio/Fx/RocketLaunch.wav");
	BandanaSFX = app->audio->LoadFx("Assets/Audio/Fx/Bandana.wav");
	DeathSFX = app->audio->LoadFx("Assets/Audio/Fx/DeathSFX.wav");

	//Animations
	idlePlayer.PushBack({ 3, 9, 15, 19 });
	idlePlayer.PushBack({ 20, 9, 15, 19 });
	idlePlayer.PushBack({ 37, 9, 15, 19 });
	idlePlayer.PushBack({ 3, 33, 15, 19 });
	idlePlayer.PushBack({ 21, 33, 15, 19 });
	idlePlayer.PushBack({ 40, 33, 16, 19 });
	idlePlayer.loop = true;
	idlePlayer.speed = 0.05f;

	attackrdyPlayer.PushBack({ 61, 9, 17, 18 }); //Putting Bandana On
	attackrdyPlayer.PushBack({ 81, 9, 19, 18 });
	attackrdyPlayer.PushBack({ 105, 9, 19, 18 });
	attackrdyPlayer.PushBack({ 126, 9, 14, 18 });
	attackrdyPlayer.loop = false;
	attackrdyPlayer.speed = 0.05f;

	attackoffPlayer.PushBack({ 126, 9, 14, 18 }); //Bandana Off
	attackoffPlayer.PushBack({ 105, 9, 19, 18 });
	attackoffPlayer.PushBack({ 81, 9, 19, 18 });
	attackoffPlayer.PushBack({ 61, 9, 17, 18 });
	attackoffPlayer.loop = false;
	attackoffPlayer.speed = 0.05f;

	IdleBandanaPlayer.PushBack({ 126, 9, 14, 18 });
	IdleBandanaPlayer.PushBack({ 143, 11, 14, 16 });
	IdleBandanaPlayer.PushBack({ 159, 13, 14, 14 });
	IdleBandanaPlayer.loop = true;
	IdleBandanaPlayer.speed = 0.05f;

	//Can Only jump when isTurn = true // With Bandana On
	jumpPlayer.PushBack({ 126, 9, 15, 18 });
	jumpPlayer.PushBack({ 143, 11, 14, 16 });
	jumpPlayer.PushBack({ 159, 13, 14, 14 });
	jumpPlayer.PushBack({ 177, 5, 13, 22 });
	jumpPlayer.PushBack({ 195, 5, 13, 22 });
	jumpPlayer.PushBack({ 213, 5, 11, 22 });
	jumpPlayer.PushBack({ 230, 5, 11, 22 });
	jumpPlayer.loop = false;
	jumpPlayer.speed = 0.1f;

	parachutePlayer.PushBack({ 487, 153, 32, 52 });
	parachutePlayer.loop = true;
	parachutePlayer.speed = 0.1f;

	deathPlayer.PushBack({ 399, 104, 14, 18 });
	deathPlayer.PushBack({ 418, 104, 14, 18 });
	deathPlayer.PushBack({ 436, 104, 14, 18 });
	deathPlayer.PushBack({ 453, 102, 18, 22 });
	deathPlayer.PushBack({ 473, 103, 16, 20 });
	deathPlayer.PushBack({ 491, 107, 10, 12 });
	deathPlayer.PushBack({ 504, 109, 7, 8 });
	deathPlayer.PushBack({ 513, 110, 6, 6 });
	deathPlayer.loop = false;
	deathPlayer.speed = 0.1f;

	hitPlayer.PushBack({ 453, 102, 18, 22 });
	hitPlayer.PushBack({ 4, 84, 16, 20 });
	hitPlayer.PushBack({ 453, 102, 18, 22 });
	hitPlayer.PushBack({ 4, 84, 16, 20 });
	hitPlayer.loop = false;
	hitPlayer.speed = 0.05f;

	currentAnim = &idlePlayer;

	//Life Status 
	dead = false;
	hp = 100;

	LOG("CREATES PLAYER2");
	pbody = app->physics->CreateCircle(startPos.x, startPos.y, 0.35f, ColliderType::PLAYER2);
	pbody->listener = this;
	pbody->cd = 0;
	pbody->coef_restitution = 0.0f;
	// Add ball to the collection
	app->physics->bodies.add(pbody);


	return true;
}

// Unload assets
bool ModulePlayerTwo::CleanUp()
{
	LOG("Unloading player");

	return true;
}


update_status ModulePlayerTwo::PreUpdate()
{
	return UPDATE_CONTINUE;
}

// Update: draw background
update_status ModulePlayerTwo::Update()
{
	if (isHit == false && dead == false) {
		currentAnim = &idlePlayer;
	}


	Collisions();

	// Player's movement
	if (isTurn == true && isAiming == false) 
	{
		if (app->input->GetKey(SDL_SCANCODE_L) == KEY_REPEAT) {
			pbody->x += 0.1f;
			if (fliped == SDL_FLIP_NONE) {
				projAngle = 0.0f;
				fliped = SDL_FLIP_HORIZONTAL;
			}
		}
		if (app->input->GetKey(SDL_SCANCODE_J) == KEY_REPEAT) {
			pbody->x -= 0.1f;
			if (fliped == SDL_FLIP_HORIZONTAL) {
				projAngle = 180.0f;
				fliped = SDL_FLIP_NONE;
			}
		}
		if (app->input->GetKey(SDL_SCANCODE_O) == KEY_DOWN) {
			if (isAiming == false) {
				showWeapon = true;
			}
			isAiming = true;

		}
	}


	if (isAiming == true) {
		ShootingFlow();
	}

	if (hp <= 0) {
		dead == true;
	}

	if (dead == true) {
		currentAnim = &deathPlayer;
		if (deathPlayer.HasFinished()) {
			pbody->listener->Disable();
		}
	}

	if (isHit == true) {
		currentAnim = &deathPlayer;
		if (deathPlayer.HasFinished()) {
			isHit = false;
		}
	}

	//if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {
	//  currentAnim = &jumpPlayer;
	//	if (onGround == true) {
	//		jumping = true;
	//		jumpingTime = 0;
	//	}
	//	onGround = false;
	//}

	////Jumping Function
	//if (jumping == true) {
	//	velocity.y = +jumpVel;

	//	jumpVel += 1.0f;

	//	jumpingTime++;
	//}



	SDL_Rect rect = currentAnim->GetCurrentFrame();
	//app->renderer->Blit(texture, METERS_TO_PIXELS(pbody->x) - rect.w / 2, SCREEN_HEIGHT - METERS_TO_PIXELS(pbody->y) - rect.h / 6, &rect, fliped);
	app->renderer->Blit(texture, METERS_TO_PIXELS(pbody->x) - rect.w / 2, SCREEN_HEIGHT - METERS_TO_PIXELS(pbody->y) - rect.h / 2, &rect, fliped);
	currentAnim->Update();

	return UPDATE_CONTINUE;
}


update_status ModulePlayerTwo::PostUpdate()
{
	return UPDATE_CONTINUE;
}


void ModulePlayerTwo::ShootingFlow() {

	currentAnim = &attackrdyPlayer;
	if (attackrdyPlayer.HasFinished() == false) {
		app->audio->PlayFx(BandanaSFX,0);
	}
	if (attackrdyPlayer.HasFinished()) {
		currentAnim = &IdleBandanaPlayer;

		//Projectile Inputs Horizontal = Velocity
		if (fliped == SDL_FLIP_HORIZONTAL) {
			if (app->input->GetKey(SDL_SCANCODE_I) == KEY_DOWN) {
				projAngle += 5.0f;
			}
			if (app->input->GetKey(SDL_SCANCODE_K) == KEY_DOWN) {
				projAngle -= 5.0f;
			}
		}
		else if (fliped == SDL_FLIP_NONE) {
			if (app->input->GetKey(SDL_SCANCODE_I) == KEY_DOWN) {
				projAngle -= 5.0f;
			}
			if (app->input->GetKey(SDL_SCANCODE_K) == KEY_DOWN) {
				projAngle += 5.0f;
			}
		}

		//Projectile Inputs Vertical = Angle
		if (app->input->GetKey(SDL_SCANCODE_J) == KEY_DOWN) {
			projVel += 5;
		}
		if (app->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN) {
			projVel -= 5;
		}

		//Projectile Limits
		if (projVel > 100) {
			projVel = 100;
		}
		if (projVel < 0) {
			projVel = 0;
		}

		if (fliped == SDL_FLIP_HORIZONTAL)
		{
			if (projAngle > 90.0f) {
				projAngle = 90.0f;
			}
			if (projAngle < -90.0f) {
				projAngle = -90.0f;
			}
		}
		else if (fliped == SDL_FLIP_NONE)
		{

			if (projAngle > 270.0f) {
				projAngle = 270.0f;
			}
			if (projAngle < 90.0f) {
				projAngle = 90.0f;
			}
		}

		if (app->input->GetKey(SDL_SCANCODE_U) == KEY_DOWN) {
			playershoots = true;
			app->audio->PlayFx(RocketLaunchSFX);
			attackrdyPlayer.Reset();
			attackrdyPlayer.ResetLoopCount();
			/*projAngle = 0;
			projVel = 50;*/
			isAiming = false;
			isTurn = false;
		}
	}
}

void ModulePlayerTwo::Collisions() {

	// L07 DONE 7: Detect the type of collision 
	if (is_colliding_with_water(this->pbody, app->physics->water1) == true) {
		LOG("Water Collision");
		if (timeToDie <= 0) {
			hp -= 10;
			isHit = true;
			timeToDie = 75;
		}
		app->audio->PlayFx(DeathSFX, 0);
		if (hp <= 0) {
			currentAnim = &deathPlayer;
			dead = true;
		}

		timeToDie--;
	}
	if (is_colliding_with_water(this->pbody, app->physics->water2) == true) {
		LOG("Water Collision");
		if (timeToDie <= 0) {
			hp -= 10;
			isHit = true;
			timeToDie = 75;
		}
		app->audio->PlayFx(DeathSFX, 0);
		if (hp <= 0) {
			dead = true;
		}

		timeToDie--;
	}
}







