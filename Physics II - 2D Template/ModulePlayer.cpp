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
	
	//Cant use B2Vec2 cause no Box2D just do start pos as x,y
	startPos.x = parameters.attribute("x").as_int();
	startPos.y = parameters.attribute("y").as_int();

	//Textures Load
	texturePath = parameters.attribute("texturepath").as_string();

	//Animations
	idlePlayer.PushBack({ 0, 0, 19, 28 });
	idlePlayer.PushBack({ 19, 0, 17, 28 });
	idlePlayer.PushBack({ 36, 0, 18, 28 });
	idlePlayer.loop = true;
	idlePlayer.speed = 0.1f;

	attackrdyPlayer.PushBack({ 0, 128, 65, 33 });
	attackrdyPlayer.PushBack({ 64, 128, 65, 33 });
	attackrdyPlayer.loop = false;
	attackrdyPlayer.speed = 0.3f;

	IdleBandanaPlayer.PushBack({ 0, 128, 65, 33 });
	IdleBandanaPlayer.PushBack({ 0, 128, 65, 33 });
	IdleBandanaPlayer.loop = false;
	IdleBandanaPlayer.speed = 0.3f;

	currentAnim = &idlePlayer;

	//Life Status 
	dead = false;
	hp = 100;

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

	currentAnim = &idlePlayer;
	velocity = { 0, 0 };

	if (isTurn == true) {
		Attack();
	}
}


update_status ModulePlayer::PostUpdate()
{
	return UPDATE_CONTINUE;
}

void ModulePlayer::Attack() {

	//bool isTurn to decide if is turn to shoot. After shot enemy bool isTurn gets switched
	if (isTurn == true)
	{
		//Attack Player has player put bandana On, then can shoot
		currentAnim = &attackrdyPlayer;

		//Once bandana on enter attack mode
		if (attackrdyPlayer.HasFinished()) {

			currentAnim = &IdleBandanaPlayer;
			attackrdy = true;
			attackrdyPlayer.Reset();
			attackrdyPlayer.ResetLoopCount();

			//draws current linked list weapon class (exp string rpg, with damage and velocity values

			if (app->input->GetKey(SDL_SCANCODE_Q) == KEY_DOWN) {
				//linked list next node for next weapon
				//draws next linked list weapon class (exp string rpg, with damage and velocity values
			}

			if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {
				/*Player Shoots
				attackrdy = false;*/
				isTurn = false;
			}
		}
	}
}



