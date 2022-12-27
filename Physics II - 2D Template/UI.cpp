#include "UI.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModulePlayer.h"
#include "ModuleSceneIntro.h"
#include "ModuleWindow.h"
#include "ModulePhysics.h"
#include "ModuleEntityManager.h"

#include "SDL/include/SDL.h"

#include "Defs.h"

UI::UI(bool start_enabled) : Module(start_enabled)
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
	font1Path = ("Assets/Fonts/font1.png");
	font2Path = ("Assets/Fonts/font2.png");

	//Loading font 1
	char lookupTableFont1[] = { "! %&'()*+,-./0123456789:;<=>abcdefghijklmnopqrstuvwxyz" };
	font1_id = app->fonts->Load(font1Path, lookupTableFont1, 1);

	//Loading font 2
	char lookupTableFont2[] = { "! @,_./0123456789$;<&?abcdefghijklmnopqrstuvwxyz" };
	font2_id = app->fonts->Load(font2Path, lookupTableFont2, 2);

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


/* UI BLIT WITH FONT 1 */
void UI::BlitPlayerHP()
{
	char playerHP[15];
	sprintf_s(playerHP, 15, "player hp: %d", app->scene_intro->player->hp);
	app->fonts->BlitText(20, 35, font1_id, playerHP);
}

/* UI DEBUG INFO WITH FONT 2 */
void UI::BlitPlayerXPos()
{
	char playerXPos[25];
	sprintf_s(playerXPos, 25, "position x; %d", app->scene_intro->player->position.x);
	app->fonts->BlitText(20, 55, font2_id, playerXPos);
}

void UI::BlitPlayerYPos()
{
	char playerYPos[25];
	sprintf_s(playerYPos, 25, "position y; %d", app->scene_intro->player->position.y);
	app->fonts->BlitText(20, 65, font2_id, playerYPos);
}
