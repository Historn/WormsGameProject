#include "Globals.h"
#include "Application.h"
#include "ModuleWeapon.h"


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
	startPos.x = app->player->position.x;
	startPos.y = app->player->position.y;

	//Textures Load
	/*texturePath = parameters.attribute("texturepath").as_string();*/
	texturePath = ("Assets/Textures/Worms_spritesheet.png");

	//Animations
	readying.PushBack({ 0, 0, 19, 28 });
	readying.PushBack({ 19, 0, 17, 28 });
	readying.PushBack({ 36, 0, 18, 28 });
	readying.loop = true;
	readying.speed = 0.1f;

	shooting.PushBack({ 0, 128, 65, 33 });
	shooting.PushBack({ 64, 128, 65, 33 });
	shooting.loop = false;
	shooting.speed = 0.3f;

	idle.PushBack({ 0, 128, 65, 33 });
	idle.PushBack({ 0, 128, 65, 33 });
	idle.loop = false;
	idle.speed = 0.3f;

	putAway.PushBack({ 0, 128, 65, 33 });
	putAway.PushBack({ 0, 128, 65, 33 });
	putAway.loop = false;
	putAway.speed = 0.3f;

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
	if (app->player->isTurn == true) {
		(isDrawn = true);
		Drawn();
	}

	position.x = app->player->position.x;
	position.y = app->player->position.y;

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



