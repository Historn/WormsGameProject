#ifndef __MODULEENDING_H__
#define __MODULEENDING_H__

#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"
#include "Animation.h"
#include "ModulePhysics.h"

struct SDL_Texture;

class ModuleEnding : public Module
{
public:

	ModuleEnding(Application* app, bool start_enabled = true);

	// Destructor
	virtual ~ModuleEnding();

	// Called before the first frame
	bool Start();

	// Called before all Updates

	// Called each loop iteration
	update_status Update();

	// Called before all Updates

	// Called before quitting
	bool CleanUp();

public:
	uint startSFX = 0;
	SDL_Texture* img;

private:


};

#endif // !__TITLE_H__


