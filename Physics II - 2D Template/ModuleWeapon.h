#ifndef _MODULEWEAPON_H
#define _MODULEWEAPON_H

#include "Entity.h"
#include "Animation.h"
#include "Globals.h"
#include "ModulePhysics.h"
#include "p2Point.h"
#include "vector"
#include "SDL/include/SDL.h"


class ModuleWeapon : public Entity
{
public:
	ModuleWeapon();
	virtual ~ModuleWeapon();

	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	
	bool CleanUp();

	void Drawn();


public:

	int currentweapon = 0;

	int launchDegree = 0;

	//Textures

	//Animations

	bool isDrawn = false;

	Animation* currentAnim = nullptr;

	Animation readying;
	Animation idle;
	Animation putAway;
	Animation aimUp45;
	Animation aimDown45;
	Animation aimDown90;
	Animation aimUp90;
	Animation launchSmoke;


	//Collider Player
	/*Collider* collider = nullptr;*/

	bool godMode = false;

	//bool isDefeated = false;
	//bool isCelebrating = false;

	bool active = false;

	Vec2D velocity;
	Vec2D startPos;

	int x;
	int y;

	PhysBody* pbody;


private:

	SDL_Texture* texture;
	const char* texturePath;

	bool isFliped = false;
	SDL_RendererFlip fliped = SDL_FLIP_NONE;

};

#endif //MODULEWEAPON
