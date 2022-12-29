#ifndef __UI_H__
#define __UI_H__

#include "Module.h"
#include "Fonts.h"
#include "SDL_mixer/include/SDL_mixer.h"


struct SDL_Texture;

class UI : public Module
{
public:
	UI(bool start_enabled = true);

	// Destructor
	~UI();

	bool Start();
	update_status Update();
	bool CleanUp();


	/* Blit UI graphics funtions */
	void BlitPlayerXPos();
	void BlitPlayerYPos();
	void BlitPlayerHP();
	void BlitPlayerAngle();
	void BlitPlayerVelocity();
	void BlitPlayer2XPos();
	void BlitPlayer2YPos();
	void BlitPlayer2HP();
	void BlitPlayer2Angle();
	void BlitPlayer2Velocity();
	void BlitFPS();
	void BlitGravityX();
	void BlitGravityY();
	void BlitWindX();
	void BlitWindY();
	void BlitAtmosphereDensity();

	uint font1_id = -1;
	uint font2_id = -1;

private:

	const char* font1Path;
	const char* font2Path;

};

#endif // __UI_H__