#ifndef _MODULETEXTURES_H
#define _MODULETEXTURES_H

#include "Module.h"
#include "Globals.h"
#include "p2List.h"
#include "SDL\include\SDL.h"

class ModuleTextures : public Module
{
public:
	ModuleTextures(bool start_enabled = true);
	~ModuleTextures();

	bool Start();
	bool CleanUp();

	SDL_Texture* const Load(const char* path);
	void Unload(SDL_Texture* texture);
	void GetSize(const SDL_Texture* texture, uint& width, uint& height) const;

public:
	p2List<SDL_Texture*> textures;
};

#endif