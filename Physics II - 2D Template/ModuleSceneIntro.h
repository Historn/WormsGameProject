#ifndef _MODULESCENEINTRO_H
#define _MODULESCENEINTRO_H

#include "Module.h"
#include "Animation.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "ModulePlayer.h"
#include "ModuleWeapon.h"

#define BOUNCER_TIME 200

enum LightTypes
{
	TINY,
	MEDIUM,
	BIG
};

class ModuleSceneIntro;

struct Light
{
	Light() : texture(NULL), on(false), fx(0)
	{}

	Light(ModuleSceneIntro* physics, int x, int y, LightTypes type);

	LightTypes type;
	SDL_Texture* texture;
	bool on;
	uint fx;
	int x, y;
};

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

public:

	SDL_Texture* map_img;

	SDL_Texture* tex_light_tiny;
	SDL_Texture* tex_light_medium;
	SDL_Texture* tex_light_big;
	
	uint fx_light_tiny;
	uint fx_light_medium;
	uint fx_light_big;

	p2DynArray<Light> lights;

	//Entities
	ModulePlayer* player;
	ModuleWeapon* weapon;
	
	uint player_lose_fx;
};

#endif