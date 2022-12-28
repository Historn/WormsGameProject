#ifndef _APPLICATION_H
#define _APPLICATION_H

#include "Module.h"
#include "p2List.h"
#include "Globals.h"
#include "Dummy.h"
#include "SString.h"
#include "Defs.h"


#include "PugiXml/src/pugixml.hpp"

#define CONFIG_FILENAME		"config.xml"
#define SAVE_STATE_FILENAME "save_game.xml"

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
//class MopduleEnding;

class Application
{
public:

	Application();
	virtual ~Application();

	bool Start();
	update_status Update();
	bool CleanUp();

	int fps = FPS;

public:
	ModuleRender* renderer;
	ModuleWindow* window;
	ModuleTextures* textures;
	ModuleInput* input;
	ModuleAudio* audio;
	FadeToBlack* fade;
	TitleScreen* title_screen;
	ModuleSceneIntro* scene_intro;
	//ModuleEnding* module_ending;
	ModuleEntityManager* entityManager;
	Fonts* fonts;
	UI* ui;
	ModulePhysics* physics;


	// xml_document to store the config file and
	// xml_node(s) to read specific branches of the xml
	/*pugi::xml_document configFile;
	pugi::xml_node configNode;*/

private:

	p2List<Module*> list_modules;

	// Create control variables to control that the real Load and Save happens at the end of the frame
	bool saveGameRequested;
	bool loadGameRequested;

private:

	void AddModule(Module* mod);
};

extern Application* app;

#endif // !_APPLICATION_H