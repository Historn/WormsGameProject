#ifndef _MODULEPHYSISCS_H
#define _MODULEPHYSISCS_H

#include "Module.h"
#include "Entity.h"
#include "Globals.h"
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

enum class BodyType {
	UNKNOWN,
	STATIC,
	KINEMATIC,
	DYNAMIC
};

enum class ColliderType {
	UNKNOWN,
	PLAYER1,
	PLAYER2,
	FLOOR
};

// Small class to return to other modules to track position and rotation of physics bodies
class PhysBody
{
public:
	PhysBody() : cType(ColliderType::UNKNOWN), bType(BodyType::UNKNOWN)
	{}
	//~PhysBody();

	int width, height;
	float radius;
	//b2Body* body;
	Entity* listener;
	ColliderType cType;

	Vec2D position;
	Vec2D velocity;
	Vec2D acceleration;
	float angle;

	//Body Mass in kg
	float mass;

	// Coefficients of friction & restitution (for bounces)
	float coef_friction;
	float coef_restitution;

	// Aerodynamics stuff
	float surface; // Effective wet surface
	float cl; // Aerodynamic Lift coefficient
	float cd; // Aerodynamic Drag coefficient
	float b; // Hydrodynamic Drag coefficient

	/// The body type.
	/// static: zero mass, zero velocity, may be manually moved
	/// kinematic: zero mass, non-zero velocity set by user, moved by solver
	/// dynamic: positive mass, non-zero velocity determined by forces, moved by solver
	BodyType bType;

	// Has physics enabled?
	bool physics_enabled = true;

};

//Class water
class Water {
public:
	float x, y, w, h; // Geometry (x,y,w,h)
	//SDL_Rect pixels(); // Convert geometry to pixels to draw w/ SDL
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

class ModulePhysics : public Module
{
public:
	ModulePhysics(bool start_enabled = true);
	~ModulePhysics();

	bool Start();
	update_status PreUpdate();
	update_status PostUpdate();
	bool CleanUp();

	PhysBody* CreateCircle(int x, int y, float radius, BodyType bType, ColliderType ctype);
	PhysBody* CreateRectangle(int x, int y, int width, int height, BodyType bType, ColliderType ctype, float angle = 0.0f);
	PhysBody* CreateRectangleSensor(int x, int y, int width, int height, BodyType bType, ColliderType ctype, float angle = 0.0f);
	PhysBody* CreateChain(int x, int y, int* points, int size, BodyType bType, ColliderType ctype);

private:

	bool debug;

public:

	std::vector<PhysBody> bodies{};
	Atmosphere atmosphere{};
	Water water{};
};

/*
// Compute Aerodynamic Drag force
void compute_aerodynamic_drag(float& fx, float& fy, const PhysBody& body, const Atmosphere& atmosphere);

// Compute Hydrodynamic Drag force
void compute_hydrodynamic_drag(float& fx, float& fy, const PhysBody& body, const Water& water);

// Compute Hydrodynamic Buoyancy force
void compute_hydrodynamic_buoyancy(float& fx, float& fy, const PhysBody& body, const Water& water);

// Integration scheme: Velocity Verlet
void integrator_velocity_verlet(PhysBody& body, float dt);

// Detect collision with water
bool is_colliding_with_water(const PhysBody& body, const Water& water);
*/

#endif 