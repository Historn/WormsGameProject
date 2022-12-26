
#include "Application.h"
#include "ModuleWeapon.h"
#include "ModuleInput.h"


ModuleWeapon::ModuleWeapon() : Entity(EntityType::WEAPON) {
	name.Create("ModuleWeapon");
}

ModuleWeapon::~ModuleWeapon()
{}

// Load assets
bool ModuleWeapon::Start()
{
	LOG("Loading player");
	return true;

	//Cant use B2Vec2 cause no Box2D just do start pos as x,y
	/*startPos.x = app->player->position.x;
	startPos.y = app->player->position.y;*/

	//Textures Load
	/*texturePath = parameters.attribute("texturepath").as_string();*/
	texturePath = ("Assets/Textures/Worms_spritesheet_full.png");

	//Animations
	readying.PushBack({ 93, 112, 28, 28 });
	readying.PushBack({ 93, 140, 28, 28 });
	readying.PushBack({ 93, 168, 28, 28 });
	readying.loop = false;
	readying.speed = 0.1f;

	idle.PushBack({ 93, 168, 28, 28 });
	idle.loop = true;
	idle.speed = 0.1f;

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

}

// Unload assets
bool ModuleWeapon::CleanUp()
{
	LOG("Unloading player");

	return true;
}


update_status ModuleWeapon::PreUpdate()
{
	return UPDATE_CONTINUE;
}

// Update: draw background
update_status ModuleWeapon::Update()
{
	/*if (app->player->isTurn == true) {
		(isDrawn = true);
		Drawn();
	}

	position.x = app->player->position.x;
	position.y = app->player->position.y;*/

	return UPDATE_CONTINUE;
}


update_status ModuleWeapon::PostUpdate()
{
	return UPDATE_CONTINUE;
}

void ModuleWeapon::Drawn() {

	//bool isDrawn to decide if is turn to shoot.
	if (isDrawn == true)
	{
		//Attack Player has player put bandana On, then can shoot
		currentAnim = &readying;

		//Once bandana on enter attack mode
		if (readying.HasFinished()) {

			currentAnim = &idle;
			readying.Reset();
			readying.ResetLoopCount();

			if (app->input->GetKey(SDL_SCANCODE_Q) == KEY_DOWN) {
				//pseudo code to draw new weapon (for example readying smg instead of rpg
			}

			if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {
				/*Player Shoots
				attackrdy = false;*/
				currentAnim = &shooting;
				if (shooting.HasFinished()) {
					currentAnim = &putAway;
					if (putAway.HasFinished()) {
						isDrawn = false;
						putAway.Reset();
						putAway.ResetLoopCount();

					}
				}
			}
		}
	}
}



