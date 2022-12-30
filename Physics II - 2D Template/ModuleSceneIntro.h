#ifndef _MODULESCENEINTRO_H
#define _MODULESCENEINTRO_H

#include "Module.h"
#include "Animation.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "ModulePlayer.h"
#include "ModulePlayerTwo.h"
#include "ModuleWeapon.h"
#include "ModuleProjectile.h"


#define BOUNCER_TIME 200

class ModuleSceneIntro;


class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();


	void ProjectileShot();

public:

	SDL_Texture* map_img;

	//Entities
	ModulePlayer* player;
	ModulePlayer* playerthree;
	ModulePlayerTwo* playertwo;
	ModulePlayerTwo* playerfour;
	ModuleWeapon* weapon;
	ModuleProjectile* projectile;
	
	uint player_die_fx;
	uint select_fx;
	uint selection_fx;
};

#endif