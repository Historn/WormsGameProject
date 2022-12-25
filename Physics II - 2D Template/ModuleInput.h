#ifndef _MODULEINPUT_H
#define _MODULEINPUT_H

#include "Module.h"
#include "Globals.h"

#include "SDL/include/SDL_scancode.h"
#include "SDL/include/SDL_gamecontroller.h"

enum KEY_STATE
{
	KEY_IDLE = 0,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};

class ModuleInput : public Module
{
public:
	
	ModuleInput(bool start_enabled = true);
	~ModuleInput();

	bool Start();
	update_status PreUpdate();
	bool CleanUp();

	KEY_STATE GetKey(int id) const
	{
		return keyboard[id];
	}

	int GetMouseX() const
	{
		return mouse_x;
	}

	int GetMouseY() const
	{
		return mouse_y;
	}

private:
	KEY_STATE* keyboard;
	int mouse_x;
	int mouse_y;
};

#endif //MODULEINPUT