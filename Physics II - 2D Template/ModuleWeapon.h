#ifndef _MODULEWEAPON_H
#define _MODULEWEAPON_H

#include "Entity.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "vector"
#include "SString.h"
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

	void aimingAnimations();

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

	Vec2D startPos;

private:

	SDL_Texture* texture;
	const char* texturePath;

};

#endif //MODULEWEAPON
