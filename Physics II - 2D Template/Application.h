#ifndef _APPLICATION_H
#define _APPLICATION_H

#include "p2List.h"
#include "Globals.h"
#include "Module.h"
#include "Dummy.h"
#include "SString.h"
#include "Defs.h"

#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "ModulePhysics.h"
#include "ModuleEntityManager.h"
#include "ModuleSceneIntro.h"
#include "Fonts.h"
#include "UI.h"

#include "PerfTimer.h"
#include "Timer.h"

#include "PugiXml/src/pugixml.hpp"

#define CONFIG_FILENAME		"config.xml"
#define SAVE_STATE_FILENAME "save_game.xml"

class Application
{
public:
	ModuleRender* renderer;
	ModuleWindow* window;
	ModuleTextures* textures;
	ModuleInput* input;
	ModuleAudio* audio;
	ModuleEntityManager* entityManager;
	ModulePlayer* player;
	ModuleSceneIntro* scene_intro;
	Fonts* fonts;
	UI* ui;
	ModulePhysics* physics;

	// xml_document to store the config file and
	// xml_node(s) to read specific branches of the xml
	pugi::xml_document configFile;
	pugi::xml_node configNode;

private:

	p2List<Module*> list_modules;

	// Create control variables to control that the real Load and Save happens at the end of the frame
	bool saveGameRequested;
	bool loadGameRequested;

	// L13: TODO 4: Calculate some timing measures
	// required variables are provided:
	Timer timer;
	PerfTimer ptimer;

	Timer startupTime;
	Timer frameTime;
	Timer lastSecFrameTime;

	uint64 frameCount = 0;
	uint32 framesPerSecond = 0;
	uint32 lastSecFrameCount = 0;

	float averageFps = 0.0f;
	float secondsSinceStartup = 0.0f;

	uint32 maxFrameDuration = 0;

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

	int fps = FPS;

private:

	void AddModule(Module* mod);
};

//extern Application* app;

#endif // !_APPLICATION_H