#ifndef __FADETOBLACK_H__
#define __FADETOBLACK_H__

#include "Module.h"
#include "SDL\include\SDL_rect.h"

class FadeToBlack : public Module
{
public:
	//Constructor
	FadeToBlack (bool start_enabled = true);

	//Destructor
	virtual ~FadeToBlack();

	// Called when the module is activated
	// Enables the blending mode for transparency
	bool Start();

	update_status PreUpdate();
	
	// Called at the middle of the application loop
	// Updates the fade logic
	update_status Update();

	//update_status PostUpdate();

	// Called at the end of the application loop
	// Performs the render call of a black rectangle with transparency

	// Called from another module
	// Starts the fade process which has two steps, fade_out and fade_in
	// After the first step, the modules should be switched
	bool FadeBlack(Module* toDisable, Module* toEnable, float frames = 60);

private:

	enum Fade_Step
	{
		NONE,
		TO_BLACK,
		FROM_BLACK
	} currentStep = Fade_Step::NONE;

	// A frame count system to handle the fade time and ratio
	Uint32 frameCount = 0;
	Uint32 maxFadeFrames = 0;

	// The rectangle of the screen, used to render the black rectangle
	SDL_Rect screenRect;

	// The modules that should be switched after the first step
	Module* moduleToEnable = nullptr;
	Module* moduleToDisable = nullptr;

	float fadeRatio;
};

#endif //__FADETOBLACK_H__

