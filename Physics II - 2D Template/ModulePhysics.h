#ifndef _MODULEPHYSISCS_H
#define _MODULEPHYSISCS_H

#include "Module.h"
#include "Globals.h"
#include "Entity.h"
#include "SDL/include/SDL_rect.h"
#include <vector>

#define GRAVITY_X 0.0f
#define GRAVITY_Y -10.0f

#define PIXELS_PER_METER 32.0f // if touched change METER_PER_PIXEL too
#define METER_PER_PIXEL 0.03125f // this is 1 / PIXELS_PER_METER !
#define RAD_PER_DEG ((float)180/b2_pi)
#define DEG_PER_RAD ((float)b2_pi/180)

#define METERS_TO_PIXELS(m) ((int) floor(PIXELS_PER_METER * m))
#define PIXEL_TO_METERS(p)  ((float) METER_PER_PIXEL * p)
#define RAD_TO_DEG(r) ((float) RAD_PER_DEG * r)
#define DEG_TO_RAD(r) ((float) DEG_PER_RAD * r)
#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f


enum class ColliderType {
	UNKNOWN,
	PLAYER1,
	PLAYER2,
	FLOOR,
	PROJECTILE,
	WEAPON
};

// Small class to return to other modules to track position and rotation of physics bodies
class PhysBody
{
public:
	/*PhysBody() : cType(ColliderType::UNKNOWN), bType(BodyType::UNKNOWN)
	{}
	~PhysBody();*/

	float x;
	float y;

	// Velocity
	float vx;
	float vy;

	// Acceleration
	float ax;
	float ay;

	// Force (total) applied to the ball
	float fx;
	float fy;

	//Body Mass in kg
	float mass;

	// Aerodynamics variables
	float surface; // Effective wet surface
	float cl; // Aerodynamic Lift coefficient
	float cd; // Aerodynamic Drag coefficient
	float b; // Hydrodynamic Drag coefficient

	// Coefficients of friction & restitution (used for bounces)
	float coef_friction;
	float coef_restitution;

	float radius;
	float w, h;
	
	Entity* listener;
	ColliderType cType;
	
	float angle;

	// Has physics enabled?
	bool physics_enabled = true;
};

// Class: Ground
class Ground : public SDL_Rect
{
public:
	float x,y,w,h; // Geometry (x,y,w,h)
	SDL_Rect pixels(); // Convert geometry to pixels to draw w/ SDL
};

//Class water
class Water : public Ground {
public:
	float density; // Density of fluid
	float vx; // Velocity x
	float vy; // Velocity y
};

//Class atmosphere
class Atmosphere
{
public:
	float density; // Density of air
	float windx; // Wind x
	float windy; // Wind y
};

class Screen : public SDL_Rect
{
public:
	float x, y, w, h; // Geometry (x,y,w,h)
};

class ModulePhysics : public Module
{
public:
	ModulePhysics(bool start_enabled = true);
	~ModulePhysics();

	bool Start();
	update_status PreUpdate();
	update_status PostUpdate();
	bool CleanUp();

	PhysBody* CreateCircle(int x, int y, float radius, ColliderType ctype);
	PhysBody* CreateRectangle(int x, int y, int width, int height, ColliderType ctype, float angle = 0.0f);
	PhysBody* CreateRectangleSensor(int x, int y, int width, int height, ColliderType ctype, float angle = 0.0f);
	PhysBody* CreateChain(int x, int y, int* points, int size, ColliderType ctype);

private:


public:

	p2List<PhysBody*> bodies{};
	p2List<Water*> waters{};
	p2List<Ground*> grounds{};
	Atmosphere atmosphere{};
	Screen screen{};

	// Create a ball
	PhysBody* ball = new PhysBody();

	// Create a water
	Water* water1 = new Water();
	Water* water2 = new Water(); 

	// Create a ground
	Ground* ground1 = new Ground();	// First collider (where player starts)
	Ground* ground2 = new Ground();	// Right collider
	Ground* ground3 = new Ground();	// First platform collider
	Ground* ground4 = new Ground();	// Left upper platform collider
	Ground* ground5 = new Ground();	// Right bottom collider
	Ground* ground6 = new Ground(); // Upper right collider
	Ground* ground7 = new Ground(); // Left central platform collider
	Ground* ground8 = new Ground(); // Right central platform collider
	Ground* leftWall = new Ground();
	Ground* rightWall = new Ground();
	Ground* upperRoof = new Ground();
	Ground* lowerRoof = new Ground();


	// Misc
	float dt = 1.0 / 60.0;

	bool debug;
};

// Compute modulus of a vector
float modulus(float vx, float vy);

// Compute Aerodynamic Drag force
void compute_aerodynamic_drag(float& fx, float& fy, const PhysBody* body, const Atmosphere& atmosphere);

// Compute Hydrodynamic Drag force
void compute_hydrodynamic_drag(float& fx, float& fy, const PhysBody* body, const Water* water);

// Compute Hydrodynamic Buoyancy force
void compute_hydrodynamic_buoyancy(float& fx, float& fy, const PhysBody* body, const Water* water);

// Integration scheme: Velocity Verlet
void integrator_velocity_verlet(PhysBody* body, float dt);

// Detect collision with ground
bool is_colliding_with_ground(const PhysBody* body, const Ground* ground);

// Detect collision with water
bool is_colliding_with_water(const PhysBody* body, const Water* water);

// Detect collision between circle and rectange
bool check_collision_circle_rectangle(float cx, float cy, float cr, float rx, float ry, float rw, float rh);

#endif 