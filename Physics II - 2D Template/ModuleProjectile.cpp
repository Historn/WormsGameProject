#include "Globals.h"
#include "Application.h"
#include "ModuleProjectile.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleSceneIntro.h"
#include "ModuleEntityManager.h"
#include "ModuleAudio.h"


ModuleProjectile::ModuleProjectile() : Entity(EntityType::PROJECTILE) {
	name.Create("ModuleProjectile");
}

ModuleProjectile::~ModuleProjectile()
{}

// Load assets
bool ModuleProjectile::Start()
{
	LOG("Loading Projectile");

	//Cant use B2Vec2 cause no Box2D just do start pos as x,y
	//startPos.x = app->player->position.x;
	//startPos.y = app->player->position.y;

	//Textures Load
	/*texturePath = parameters.attribute("texturepath").as_string();*/
	texture = app->textures->Load("Assets/Textures/Worms_spritesheet_full.png");

	DeathSFX = app->audio->LoadFx("Assets/Audio/Fx/DeathSFX.wav");

	//Animations
	proj0.PushBack({ 167, 151, 9, 7 });
	proj0.loop = true;
	proj0.speed = 0.05f;

	projExplosion.PushBack({ 211, 312, 30, 32 });
	projExplosion.PushBack({ 241, 285, 61, 61 });
	projExplosion.PushBack({ 73, 313, 34, 35 });
	projExplosion.PushBack({ 107, 315, 20, 29 });
	projExplosion.PushBack({ 126, 319, 14, 19 });
	projExplosion.loop = false;
	projExplosion.speed = 0.05f;

	// Add ball to the collection
	startPos.x = app->scene_intro->player->position.x;
	startPos.y = app->scene_intro->player->position.y;

	LOG("CREATES PROJECTILE");
	pbody = app->physics->CreateCircle(startPos.x, startPos.y, 0.2f, ColliderType::PROJECTILE);
	pbody->listener = this;

	// Add ball to the collection
	app->physics->bodies.add(pbody);

	currentAnim = &proj0;

	life = 2;

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
	Collisions();

	SDL_Rect rect = currentAnim->GetCurrentFrame();
	app->renderer->Blit(texture, METERS_TO_PIXELS(pbody->x) - rect.w / 2, SCREEN_HEIGHT - METERS_TO_PIXELS(pbody->y) - rect.h / 6, &rect, fliped);
	currentAnim->Update();


	return UPDATE_CONTINUE;
}


update_status ModuleProjectile::PostUpdate()
{
	return UPDATE_CONTINUE;
}

void ModuleProjectile::Collisions() {

	p2List_item<Ground*>* ground = app->physics->grounds.getFirst();

	while (ground != NULL)
	{
		// Solve collision between ball and ground
		if (is_colliding_with_ground(pbody, ground->data))
		{
			--life;
			if (life < 0) {
				pbody->listener->Disable();
			}
		}
		ground = ground->next;
	}
	
	p2List_item<Water*>* water = app->physics->waters.getFirst();

	while (water != NULL)
	{
		// Solve collision between ball and ground
		if (is_colliding_with_ground(pbody, water->data))
		{
			--life;
			if (life < 0) {
				pbody->listener->Disable();
			}
		}
		water = water->next;
	}
	
	p2List_item<PhysBody*>* body = app->physics->bodies.getFirst();

	while (body != NULL)
	{
		// Solve collision between ball and ground
		if (is_colliding_with_physbody(pbody, body->data))
		{
			if(body->data->cType == ColliderType::PLAYER1 || body->data->cType == ColliderType::PLAYER2)
				pbody->listener->Disable();
			//Player Health Down by 50 on Hit
			if (body->data == app->scene_intro->player->pbody) {
				LOG("Projectile Collision");
				app->scene_intro->player->hp = app->scene_intro->player->hp - 50;
				app->audio->PlayFx(DeathSFX, 0);
				app->scene_intro->player->isHit = true;
				if (app->scene_intro->player->hp <= 0) {
					app->scene_intro->player->dead = true;
				}
			}
			if (body->data == app->scene_intro->playerthree->pbody) {
				LOG("Projectile Collision");
				app->scene_intro->playerthree->hp = app->scene_intro->playerthree->hp - 50;
				app->audio->PlayFx(DeathSFX, 0);
				app->scene_intro->playerthree->isHit = true;
				if (app->scene_intro->playerthree->hp <= 0) {
					app->scene_intro->playerthree->dead = true;
				}
			}
			if (body->data == app->scene_intro->playertwo->pbody) {
				LOG("Projectile Collision");
				app->scene_intro->playertwo->hp = app->scene_intro->playertwo->hp - 50;
				app->audio->PlayFx(DeathSFX, 0);
				app->scene_intro->playertwo->isHit = true;
				if (app->scene_intro->playertwo->hp <= 0) {
					app->scene_intro->playertwo->dead = true;
				}
			}
			if (body->data == app->scene_intro->playerfour->pbody) {
				LOG("Projectile Collision");
				app->scene_intro->playerfour->hp = app->scene_intro->playerfour->hp - 50;
				app->audio->PlayFx(DeathSFX, 0);
				app->scene_intro->playerfour->isHit = true;
				if (app->scene_intro->playerfour->hp <= 0) {
					app->scene_intro->playerfour->dead = true;
				}
			}

		}
		body = body->next;
	}
}
