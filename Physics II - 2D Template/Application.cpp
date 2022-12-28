

#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "FadeToBlack.h"
#include "TitleScreen.h"
#include "ModulePlayer.h"
#include "ModuleWeapon.h"
#include "ModuleProjectile.h"
#include "ModulePhysics.h"
#include "ModuleEntityManager.h"
#include "ModuleSceneIntro.h"
#include "Fonts.h"
#include "UI.h"
//#include "ModuleEnding.h"

#include "Application.h"


Application::Application()
{
	renderer = new ModuleRender(true);
	window = new ModuleWindow(true);
	textures = new ModuleTextures(true);
	input = new ModuleInput(true);
	audio = new ModuleAudio(true);
	fade = new FadeToBlack(true);
	title_screen = new TitleScreen(true);
	scene_intro = new ModuleSceneIntro(false);
	//module_ending = new ModuleEnding(false);
	entityManager = new ModuleEntityManager(false);
	fonts = new Fonts(true);
	ui = new UI(true);
	physics = new ModulePhysics(false);

	// The order of calls is very important!
	// Modules will Init() Start() and Update in this order
	// They will CleanUp() in reverse order

	// Main Modules
	AddModule(window);
	AddModule(physics);
	AddModule(renderer);
	AddModule(textures);
	AddModule(input);
	AddModule(audio);
	AddModule(fonts);
	AddModule(ui);
	// Entities
	
	// Scenes
	AddModule(title_screen);
	AddModule(scene_intro);
	//AddModule(module_ending);


	
	AddModule(entityManager);

	//FadeToBlack
	AddModule(fade);
}

Application::~Application()
{
	p2List_item<Module*>* item = list_modules.getLast();

	while(item != NULL)
	{
		delete item->data;
		item = item->prev;
	}
}

bool Application::Start()
{
	bool ret = true;

	p2List_item<Module*>* item = list_modules.getFirst();

		// After all Init calls we call Start() in all modules
	LOG("Application Start --------------");

	while(item != NULL && ret == true)
	{
		if(item->data->IsEnabled())
			ret = item->data->Start();
		item = item->next;
	}
	
	return ret;
}

// Call PreUpdate, Update and PostUpdate on all modules
update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;
	p2List_item<Module*>* item = list_modules.getFirst();

	while(item != NULL && ret == UPDATE_CONTINUE)
	{
		if(item->data->IsEnabled())
			ret = item->data->PreUpdate();
		item = item->next;
	}

	item = list_modules.getFirst();

	while(item != NULL && ret == UPDATE_CONTINUE)
	{
		if(item->data->IsEnabled())
  			ret = item->data->Update();
		item = item->next;
	}

	item = list_modules.getFirst();

	while(item != NULL && ret == UPDATE_CONTINUE)
	{
		if(item->data->IsEnabled())
			ret = item->data->PostUpdate();
		item = item->next;
	}

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;
	p2List_item<Module*>* item = list_modules.getLast();

	while(item != NULL && ret == true)
	{
		ret = item->data->CleanUp();
		item = item->prev;
	}
	return ret;
}

void Application::AddModule(Module* mod)
{
	list_modules.add(mod);
}