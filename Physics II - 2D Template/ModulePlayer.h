#ifndef _MODULEPLAYER_H
#define _MODULEPLAYER_H

#include "Entity.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

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
	bool CleanUp();

public:

};

#endif //MODULEPLAYER