#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"



ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	name.Create("ModuleSceneIntro");
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	app->renderer->camera.x = app->renderer->camera.y = 0;

	img = app->textures->Load("Assets/Textures/mapExample.png");

	return ret;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{




	app->renderer->Blit(img, 0, 0, NULL);

	return UPDATE_CONTINUE;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	app->textures->Unload(img);

	return true;
}


