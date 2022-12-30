#include "UI.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModulePlayer.h"
#include "ModulePlayerTwo.h"
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
	char playerHP[25];
	sprintf_s(playerHP, 25, "player1 hp: %d", app->scene_intro->player->hp);
	app->fonts->BlitText(20, 160, font1_id, playerHP);
}

void UI::BlitPlayer2HP()
{
	char playertwoHP[25];
	sprintf_s(playertwoHP, 25, "player2 hp:%d", app->scene_intro->playertwo->hp);
	app->fonts->BlitText(1040, 165, font1_id, playertwoHP);
}

void UI::BlitPlayerAngle()
{
	char playerangle[30];
	sprintf_s(playerangle, 30, "angle: %.1f degs", app->scene_intro->player->projAngle);
	app->fonts->BlitText(20, 180, font1_id, playerangle);

}

void UI::BlitPlayer2Angle()
{
	char playertwoangle[30];
	sprintf_s(playertwoangle, 30, "angle:%.1f degs", app->scene_intro->playertwo->projAngle);
	app->fonts->BlitText(1040, 185, font1_id, playertwoangle);

}

void UI::BlitPlayerVelocity()
{
	char playervel[30];
	sprintf_s(playervel, 30, "velocity: %d m/s", app->scene_intro->player->projVel);
	app->fonts->BlitText(20, 200, font1_id, playervel);
}

void UI::BlitPlayer2Velocity()
{
	char playertwovel[30];
	sprintf_s(playertwovel, 30, "velocity:%d m/s", app->scene_intro->playertwo->projVel);
	app->fonts->BlitText(1040, 205, font1_id, playertwovel);
}

/* UI DEBUG INFO WITH FONT 2 */
void UI::BlitPlayerXPos()
{
	char playerXPos[25];
	sprintf_s(playerXPos, 25, "position x; %.2f", app->scene_intro->player->pbody->x);
	app->fonts->BlitText(10, 615, font2_id, playerXPos);
}

void UI::BlitPlayer2XPos()
{
	char playertwoXPos[25];
	sprintf_s(playertwoXPos, 25, "position x; %.2f", app->scene_intro->playertwo->pbody->x);
	app->fonts->BlitText(985, 620, font2_id, playertwoXPos);
}

void UI::BlitPlayerYPos()
{
	char playerYPos[25];
	sprintf_s(playerYPos, 25, "position y; %.2f", app->scene_intro->player->pbody->y);
	app->fonts->BlitText(10, 625, font2_id, playerYPos);
}

void UI::BlitPlayer2YPos()
{
	char playertwoYPos[25];
	sprintf_s(playertwoYPos, 25, "position y; %.2f", app->scene_intro->playertwo->pbody->y);
	app->fonts->BlitText(985, 630, font2_id, playertwoYPos);
}

void UI::BlitFPS()
{
	char fps[25];
	sprintf_s(fps, 25, "fps; %d", app->fps);
	app->fonts->BlitText(510, 555, font2_id, fps);
}

void UI::BlitGravityX()
{
	char gravityX[25];
	sprintf_s(gravityX, 25, "gravity x; %.2f m/s2", app->physics->gravity.x);
	app->fonts->BlitText(510, 565, font2_id, gravityX);
}

void UI::BlitGravityY()
{
	char gravityY[25];
	sprintf_s(gravityY, 25, "gravity y; %.2f m/s2", app->physics->gravity.y);
	app->fonts->BlitText(510, 575, font2_id, gravityY);
}

void UI::BlitWindX()
{
	char windX[25];
	sprintf_s(windX, 25, "wind x; %.2f m/s", app->physics->atmosphere.windx);
	app->fonts->BlitText(510, 585, font2_id, windX);
}

void UI::BlitWindY()
{
	char windY[25];
	sprintf_s(windY, 25, "wind y; %.2f m/s", app->physics->atmosphere.windy);
	app->fonts->BlitText(510, 595, font2_id, windY);
}

void UI::BlitAtmosphereDensity()
{
	char density[40];
	sprintf_s(density, 40, "atmosphere density; %.2f kg/m3", app->physics->atmosphere.density);
	app->fonts->BlitText(510, 605, font2_id, density);
}

void UI::BlitDeltaTime()
{
	char deltaTime[40];
	sprintf_s(deltaTime, 40, "delta time scheme; %.6f ms", app->physics->dt);
	app->fonts->BlitText(510, 615, font2_id, deltaTime);
}

void UI::BlitWindIsEnabled()
{
	char wind[40];
	sprintf_s(wind, 40, "wind is enabled? %s", app->physics->windEnabled ? "true" : "false");
	app->fonts->BlitText(770, 555, font2_id, wind);
}