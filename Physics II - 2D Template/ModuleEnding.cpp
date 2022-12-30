#include "Application.h"
#include "Animation.h"
#include "ModuleWindow.h"
#include "Module.h"
#include "Globals.h"
#include "ModuleAudio.h"
#include "Fonts.h"
#include "ModuleInput.h"
#include "ModulePhysics.h"
#include "ModuleRender.h"
#include "ModuleEnding.h"
#include "ModuleSceneIntro.h"
#include "ModuleTextures.h"
#include "UI.h"
#include "FadeToBlack.h"
#include "ModulePlayer.h"


#include "SDL/include/SDL_render.h"

ModuleEnding::ModuleEnding(bool start_enabled) : Module(start_enabled)
{
	name.Create("ModuleTitleScreen");
}

// Destructor
ModuleEnding::~ModuleEnding()
{}

// Called before the first frame
bool ModuleEnding::Start()
{
	LOG("Loading TitleScreen");
	bool ret = true;

	//Disable modules/entities

	// Set camera position
	app->renderer->camera.x = app->renderer->camera.y = 0;

	//Load music
	app->audio->PlayMusic("Assets/Audio/Music/EndingScreen.ogg");

	//Load SFX
	click_sfx = app->audio->LoadFx("Assets/Audio/Fx/click.wav");

	//Load tex
	img_team1 = app->textures->Load("Assets/Textures/EndingScreen_team1.png");
	img_team2 = app->textures->Load("Assets/Textures/EndingScreen_team2.png");
	img = app->textures->Load("Assets/Textures/EndingScreen.png");

	return ret;
}

// Called each loop iteration
update_status ModuleEnding::Update()
{
	// Enable/Disable Fullscreen Mode
	if (app->input->GetKey(SDL_SCANCODE_F11) == KEY_DOWN)
		app->fullscreen = !app->fullscreen;

	//Pass next screen
	if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN) {
		LOG("PASA A GAME SCENE");
		app->fade->FadeBlack(this, (Module*)app->title_screen, 90);
		app->audio->PlayFx(click_sfx);
	}

	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		return UPDATE_STOP;

	if(app->scene_intro->player->dead == true && app->scene_intro->playerthree->dead == true)
	{
		LOG("Team 2 wins!");
		app->renderer->Blit(img_team2, 0, 0, NULL);
	}
	else if (app->scene_intro->playertwo->dead == true && app->scene_intro->playerfour->dead == true)
	{
		LOG("Team 1 wins!");
		app->renderer->Blit(img_team1, 0, 0, NULL);
	}
	else 
	{
		app->renderer->Blit(img, 0, 0, NULL);
	}

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleEnding::CleanUp()
{
	LOG("Unloading Title scene");

	app->textures->Unload(img_team1);
	app->textures->Unload(img_team2);
	app->textures->Unload(img);

	return true;
}
