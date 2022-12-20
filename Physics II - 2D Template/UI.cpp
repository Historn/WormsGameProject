#include "UI.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModulePlayer.h"
#include "ModuleSceneIntro.h"
#include "ModuleWindow.h"

#include "SDL/include/SDL.h"

#include "Defs.h"

UI::UI(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	name.Create("UI_Module");
}

UI::~UI()
{}


// Called before the first frame
bool UI::Start()
{
	LOG("--STARTS UI MODULE--");
	
	/*Initialize*/
	//font1Path = App->configNode.child("ui").child("font1").attribute("texturepath").as_string();
	//font2Path = App->configNode.child("ui").child("font2").attribute("texturepath").as_string();
	
	//Loading font 1
	char lookupTableFont1[] = { "! @,_./0123456789$;<&?abcdefghijklmnopqrstuvwxyz" };
	font1_id = app->fonts->Load(font1Path, lookupTableFont1, 2);

	char lookupTableFont2[] = { "! %&'()*+,-./0123456789:;<=>abcdefghijklmnopqrstuvwxyz" };
	font2_id = app->fonts->Load(font2Path, lookupTableFont2, 1);

	return true;
}

// Called each loop iteration
update_status UI::Update()
{

	return UPDATE_CONTINUE;
}


// Called before quitting
bool UI::CleanUp()
{
	LOG("Freeing UI_Module");

	app->fonts->UnLoad(font1_id);
	app->fonts->UnLoad(font2_id);

	return true;
}


/* UI DEBUG INFO WITH FONT 2 */
//void UI::BlitPlayerXPos()
//{
//	char playerXPos[25];
//	sprintf_s(playerXPos, 25, "position x: %d", app->player->position.x);
//	app->fonts->BlitText(20, 55, font2_id, playerXPos);
//}
//
//void UI::BlitPlayerYPos()
//{
//	char playerYPos[25];
//	sprintf_s(playerYPos, 25, "position y: %d", app->player->position.y);
//	app->fonts->BlitText(20, 75, font2_id, playerYPos);
//}
