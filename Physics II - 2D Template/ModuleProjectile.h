#ifndef _MODULEPROJECTILE_H
#define _MODULEPROJECTILE_H

#include "Entity.h"
#include "Animation.h"
#include "Globals.h"
#include "ModulePhysics.h"
#include "p2Point.h"
#include "vector"
#include "SDL/include/SDL.h"



class ModuleProjectile : public Entity
{
public:
	ModuleProjectile();
	virtual ~ModuleProjectile();


	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();


	bool CleanUp();

public:

	//Textures

	//Animations

	Animation* currentAnim = nullptr;

	Animation proj0;


	//Collider Player
	/*Collider* collider = nullptr;*/

	//bool isDefeated = false;
	//bool isCelebrating = false;

	bool onGround = false;
	bool dead = false;
	bool onCollision = false;

	//Turn bool to decide if is users shoot turn

	Vec2D startPos;

	PhysBody* pbody;

private:

	SDL_Texture* texture;
	const char* texturePath;

	bool isFliped = false;
	SDL_RendererFlip fliped = SDL_FLIP_NONE;

};

#endif //MODULEPROJECTILE
