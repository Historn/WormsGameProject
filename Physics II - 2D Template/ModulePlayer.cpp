#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePhysics.h"


ModulePlayer::ModulePlayer() : Entity(EntityType::PLAYER){
	name.Create("ModulePlayer");
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");
	
	//Cant use B2Vec2 cause no Box2D just do start pos as x,y
	/*startPos.x = parameters.attribute("x").as_int();
	startPos.y = parameters.attribute("y").as_int();*/
	startPos.x = 50;
	startPos.y = 50;

	//Textures Load
	/*texturePath = parameters.attribute("texturepath").as_string();*/
	texturePath = ("Assets/Textures/Worms_spritesheet_full.png");

	//Animations
	idlePlayer.PushBack({ 0, 0, 19, 28 });
	idlePlayer.PushBack({ 19, 0, 17, 28 });
	idlePlayer.PushBack({ 36, 0, 18, 28 });
	idlePlayer.loop = true;
	idlePlayer.speed = 0.1f;

	attackrdyPlayer.PushBack({ 61, 0, 21, 30 }); //Putting Bandana On
	attackrdyPlayer.PushBack({ 82, 0, 22, 26 });
	attackrdyPlayer.PushBack({ 105, 0, 22, 26 });
	attackrdyPlayer.PushBack({ 126, 0, 17, 26 });
	attackrdyPlayer.PushBack({ 158, 0, 17, 26 });
	attackrdyPlayer.loop = false;
	attackrdyPlayer.speed = 0.3f;

	IdleBandanaPlayer.PushBack({ 105, 0, 22, 26 });
	IdleBandanaPlayer.PushBack({ 126, 0, 17, 26 });
	IdleBandanaPlayer.PushBack({ 105, 0, 22, 26 });
	IdleBandanaPlayer.loop = true;
	IdleBandanaPlayer.speed = 0.3f;

	//Can Only jump when isTurn = true // With Bandana On
	jumpPlayer.PushBack({ 126, 0, 17, 26 });
	jumpPlayer.PushBack({ 158, 0, 17, 26 });
	jumpPlayer.PushBack({ 175, 0, 17, 29 });
	jumpPlayer.loop = false;
	jumpPlayer.speed = 0.1f;

	parachutePlayer.PushBack({ 487, 153, 32, 52 });
	parachutePlayer.loop = true;
	parachutePlayer.speed = 0.1f;

	deathPlayer.PushBack({ 396, 100, 20, 24 });
	deathPlayer.PushBack({ 416, 100, 20, 24 });
	deathPlayer.PushBack({ 436, 100, 17, 24 });
	deathPlayer.PushBack({ 453, 100, 20, 24 });
	deathPlayer.PushBack({ 473, 100, 18, 24 });
	deathPlayer.PushBack({ 490, 100, 14, 24 });
	deathPlayer.PushBack({ 503, 100, 10, 24 });
	deathPlayer.PushBack({ 512, 100, 10, 24 });
	deathPlayer.loop = false;
	deathPlayer.speed = 0.1f;

	currentAnim = &idlePlayer;

	//Life Status 
	dead = false;
	hp = 100;

	//pbody = app->physics->CreateCircle(startPos.x, startPos.y, 10, BodyType::STATIC, ColliderType::PLAYER1);

	position.x = startPos.x;
	position.y = startPos.y;

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
	currentAnim = &idlePlayer;
	velocity = { 0, 0 };

	if (isTurn == true) {
		Attack();
	}

	SDL_Rect rect = currentAnim->GetCurrentFrame();
	app->renderer->Blit(texture, position.x, position.y, &rect, fliped);
	currentAnim->Update();

	return UPDATE_CONTINUE;

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



