#ifndef _APPLICATION_H
#define _APPLICATION_H

#include "Module.h"
#include "p2List.h"
#include "Globals.h"
#include "Dummy.h"
#include "SString.h"
#include "Defs.h"


class ModuleRender;
class ModuleWindow;
class ModuleTextures;
class ModuleInput;
class ModuleAudio;
class FadeToBlack;
class TitleScreen;
class ModuleSceneIntro;
class ModuleEntityManager;
class ModuleProjectile;
class Fonts;
class UI;
class ModulePhysics;
class ModuleEnding;

class Application
{
public:

	Application();
	virtual ~Application();

	bool Start();
	update_status Update();
	bool CleanUp();

	int fps = FPS;
	bool fullscreen = false;

public:
	ModuleRender* renderer;
	ModuleWindow* window;
	ModuleTextures* textures;
	ModuleInput* input;
	ModuleAudio* audio;
	FadeToBlack* fade;
	TitleScreen* title_screen;
	ModuleSceneIntro* scene_intro;
	ModuleEnding* ending_screen;
	ModuleEntityManager* entityManager;
	Fonts* fonts;
	UI* ui;
	ModulePhysics* physics;


private:

	p2List<Module*> list_modules;

private:

	void AddModule(Module* mod);
};

extern Application* app;

#endif // !_APPLICATION_H