#include "Globals.h"
#include "Application.h"
#include "ModuleProjectile.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleSceneIntro.h"


ModuleProjectile::ModuleProjectile() : Entity(EntityType::PROJECTILE) {
	name.Create("ModuleProjectile");
}

ModuleProjectile::~ModuleProjectile()
{}

// Load assets
bool ModuleProjectile::Start()
{
	LOG("Loading Projectile");
	return true;

	//Cant use B2Vec2 cause no Box2D just do start pos as x,y
	//startPos.x = app->player->position.x;
	//startPos.y = app->player->position.y;

	//Textures Load
	/*texturePath = parameters.attribute("texturepath").as_string();*/
	texture = app->textures->Load("Assets/Textures/Worms_spritesheet_full.png");

	//Animations
	proj0.PushBack({ 167, 151, 9, 7 });
	proj0.loop = true;
	proj0.speed = 0.05f;

	// Add ball to the collection
	startPos.x = app->scene_intro->player->position.x;
	startPos.y = app->scene_intro->player->position.y;

	LOG("CREATES PROJECTILE");
	pbody = app->physics->CreateCircle(startPos.x, startPos.y, 0.5f, ColliderType::PROJECTILE);
	pbody->listener = this;

	// Add ball to the collection
	app->physics->bodies.add(pbody);

	currentAnim = &proj0;

	return true;
}

// Unload assets
bool ModuleProjectile::CleanUp()
{
	LOG("Unloading Weapon");

	return true;
}


update_status ModuleProjectile::PreUpdate()
{
	return UPDATE_CONTINUE;
}

// Update: draw background
update_status ModuleProjectile::Update() {

	currentAnim = &proj0;

	/*OnCollision();*/

	//SDL_Rect rect = currentAnim->GetCurrentFrame();
	//app->renderer->Blit(texture, METERS_TO_PIXELS(pbody->x) - rect.w / 2, SCREEN_HEIGHT - METERS_TO_PIXELS(pbody->y) - rect.h / 6, &rect, fliped);
	//currentAnim->Update();


	return UPDATE_CONTINUE;
}


update_status ModuleProjectile::PostUpdate()
{
	return UPDATE_CONTINUE;
}
