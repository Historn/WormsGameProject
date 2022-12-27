#include "Globals.h"
#include "Application.h"
#include "ModuleWeapon.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"


ModuleWeapon::ModuleWeapon() : Entity(EntityType::WEAPON) {
	name.Create("ModuleWeapon");
}

ModuleWeapon::~ModuleWeapon()
{}

// Load assets
bool ModuleWeapon::Start()
{
	LOG("Loading Weapon");
	return true;

	startPos.x = 2;
	startPos.y = 0.5f;

	//Cant use B2Vec2 cause no Box2D just do start pos as x,y
	/*startPos.x = app->player->position.x;
	startPos.y = app->player->position.y;*/

	//Textures Load
	/*texturePath = parameters.attribute("texturepath").as_string();*/
	texture = app->textures->Load("Assets/Textures/Worms_spritesheet_full.png");

	//Animations
	readying.PushBack({ 93, 112, 28, 28 });
	readying.PushBack({ 93, 140, 28, 28 });
	readying.PushBack({ 93, 168, 28, 28 });
	readying.loop = false;
	readying.speed = 0.1f;

	idle.PushBack({ 93, 168, 28, 28 });
	idle.loop = true;
	idle.speed = 0.05f;

	putAway.PushBack({ 93, 168, 28, 28 });
	putAway.PushBack({ 93, 196, 28, 28 });
	putAway.PushBack({ 93, 224, 28, 28 });
	putAway.loop = false;
	putAway.speed = 0.1f;

	aimUp45.PushBack({ 93, 140, 28, 28 });
	aimUp45.loop = true;
	aimUp45.speed = 0.1f;

	aimDown45.PushBack({ 93, 196, 28, 28 });
	aimDown45.loop = true;
	aimDown45.speed = 0.1f;

	aimUp90.PushBack({ 93,112,28,28 });
	aimUp90.loop = true;
	aimUp90.speed = 0.1f;

	aimDown90.PushBack({ 93, 224, 28, 28 });
	aimDown90.loop = true;
	aimDown90.speed = 0.1f;

	launchSmoke.PushBack({ 73, 313, 34, 35 });
	launchSmoke.PushBack({ 107, 315, 20, 29 });
	launchSmoke.PushBack({ 126, 319, 14, 19 });
	launchSmoke.loop = false;
	launchSmoke.speed = 0.1f;

	//Life Status 
	currentAnim = &idle;
	pbody = app->physics->CreateCircle(startPos.x, startPos.y, 0.5f, ColliderType::WEAPON);
	pbody->listener = this;
	// Add ball to the collection
	app->physics->bodies.add(pbody);

	LOG("CREATES Weapon");

	return true;
}

// Unload assets
bool ModuleWeapon::CleanUp()
{
	LOG("Unloading Weapon");

	return true;
}


update_status ModuleWeapon::PreUpdate()
{
	return UPDATE_CONTINUE;
}

// Update: draw background
update_status ModuleWeapon::Update() {

	currentAnim = &idle;


	//Weapon Movement


	return UPDATE_CONTINUE;
}


update_status ModuleWeapon::PostUpdate()
{
	return UPDATE_CONTINUE;
}

void ModuleWeapon::Drawn() {

	//bool isDrawn to decide if is turn to shoot.
	while (isDrawn == true)
	{
		//Attack Player has player put bandana On, then can shoot
		currentAnim = &readying;

		//Once bandana on enter attack mode
		if (readying.HasFinished()) {

			currentAnim = &idle;
			readying.Reset();
			readying.ResetLoopCount();
			
			// start at 0 degrees launchDegree Variable

			bool hasShot = false;

			while (hasShot == false) {

				/*Anims for each degree of aim - if we do aim with mouse or smaller increments make 
				animations for range instead */

				//..aimingAnimation();..

				/*check player inputs to decide which degree we are at, this is for sending to the animations above*/
				if (app->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN) {
					// up key was pressed, increase the degree by 5
					launchDegree += 5;
					if (launchDegree > 90) {
						launchDegree = -90;  // wrap around to 0 degrees
					}
				}
				if (app->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN) {
					// down key was pressed, decrease the degree by 5
					launchDegree -= 5;
					if (launchDegree < -90) {
						launchDegree = 90;  // wrap around to 180 degrees
					}
				}
				if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {
						currentAnim = &putAway;
						hasShot = true;
				}
			}
		
		}
		if (putAway.HasFinished()) {
			putAway.Reset();
			putAway.ResetLoopCount();
			isDrawn = false;
		}
	}
}

void aimingAnimations() {

	/*code idea*/
	/*if (-90 <= launchDegree < -45) {
		currentAnim = launchdegree
	}*/

}