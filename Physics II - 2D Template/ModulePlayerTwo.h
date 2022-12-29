#ifndef _MODULEPLAYERTWO_H
#define _MODULEPLAYERTWO_H

#include "Entity.h"
#include "Animation.h"
#include "Globals.h"
#include "ModulePhysics.h"
#include "p2Point.h"
#include "vector"
#include "SDL/include/SDL.h"

class ModulePlayerTwo : public Entity
{
public:
	ModulePlayerTwo();
	virtual ~ModulePlayerTwo();

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

	int jumpingTime;

	//Jump Variables
	float jumpVel = GRAVITY_Y;
	bool jumping = false;
	bool longPress = false;

	bool onGround = true;
	bool dead = false;
	bool onCollision = false;
	bool settingattack = false;
	bool playershoots = false;

	bool VelSet = false;
	bool AngleSet = false;

	bool isHit = false;

	//Turn bool to decide if is users shoot turn
	bool isTurn = false;
	bool isAiming = false;
	bool showWeapon = false;

	int hp;
	int timeToDie = 75;

	Vec2D velocity;
	int projVel = 50;
	float projAngle = 180.0f;
	Vec2D startPos;

	PhysBody* pbody;

	SDL_RendererFlip fliped = SDL_FLIP_NONE;

private:

	SDL_Texture* texture;
	const char* texturePath;

};

#endif //MODULEPLAYERTWO