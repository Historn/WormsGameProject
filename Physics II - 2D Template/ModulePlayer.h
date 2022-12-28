#ifndef _MODULEPLAYER_H
#define _MODULEPLAYER_H

#include "Entity.h"
#include "Animation.h"
#include "Globals.h"
#include "ModulePhysics.h"
#include "p2Point.h"
#include "vector"
#include "SDL/include/SDL.h"

struct Object
{
	SDL_Texture* graphic;
	uint fx;

	Object() : graphic(NULL)
	{}
};

class ModulePlayer : public Entity
{
public:
	ModulePlayer();
	virtual ~ModulePlayer();

	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();

	void Collisions();

	bool CleanUp();
	void SetVelocity();
	void SetAngle();

	void ShootingFlow();

public:

	//Textures

	//Animations

	Animation* currentAnim = nullptr;

	Animation idlePlayer;
	Animation IdleBandanaPlayer;
	Animation attackrdyPlayer;
	Animation jumpPlayer;
	Animation parachutePlayer;
	Animation deathPlayer;
	Animation hitPlayer;
	Animation attackoffPlayer;


	uint RocketLaunchSFX = 0;
	uint BandanaSFX = 0;
	uint DeathSFX = 0;
	//Collider Player
	/*Collider* collider = nullptr;*/

	bool godMode = false;

	//bool isDefeated = false;
	//bool isCelebrating = false;

	bool onGround = false;
	bool dead = false;
	bool onCollision = false; 
	bool settingattack = false;
	bool jumping;
	bool playershoots = false;

	bool VelSet = false;
	bool AngleSet = false;

	bool isHit = false;

	//Turn bool to decide if is users shoot turn
	bool isTurn = false;

	int hp;

	int x;
	int y;

	Vec2D velocity;
	int projVel = 50;
	int projAngle = 0;
	Vec2D startPos;

	PhysBody* pbody;

private:

	SDL_Texture* texture;
	const char* texturePath;

	bool isFliped = false;
	SDL_RendererFlip fliped = SDL_FLIP_NONE;

};

#endif //MODULEPLAYER