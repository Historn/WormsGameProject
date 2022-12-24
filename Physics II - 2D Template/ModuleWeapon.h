#ifndef _MODULEWEAPON_H
#define _MODULEWEAPON_H

#include "Entity.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "vector"
#include "SDL/include/SDL.h"


class ModuleWeapon : public Entity
{
public:
	ModuleWeapon();
	virtual ~ModuleWeapon();

	bool Start();
	update_status Awake();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	void Drawn();

	bool CleanUp();

public:

	int currentweapon = 0;


	//Textures

	//Animations

	bool isDrawn = false;

	Animation* currentAnim = nullptr;

	Animation readying;
	Animation shooting;
	Animation idle;
	Animation putAway;


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
