#include "Globals.h"
#include "Application.h"
#include "ModulePhysics.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "math.h"
#include <cmath>

ModulePhysics::ModulePhysics(bool start_enabled) : Module(start_enabled)
{
	name.Create("ModulePhysics");
	debug = true;
}

// Destructor
ModulePhysics::~ModulePhysics()
{
}

bool ModulePhysics::Start()
{
	LOG("Creating Physics 2D environment");
	
	// Create ground
	ground1->x = 0.0f; // [m]
	ground1->y = 0.0f; // [m]
	ground1->w = 10.2f; // [m]
	ground1->h = 3.6f; // [m]

	ground2->x = 15.4f; // [m]
	ground2->y = 0.0f; // [m]
	ground2->w = 15.2f; // [m]
	ground2->h = 5.5f; // [m]

	ground3->x = 5.9f; // [m]
	ground3->y = 9.6f; // [m]
	ground3->w = 7.5f; // [m]
	ground3->h = 1.0; // [m]

	ground4->x = 0.0f; // [m]
	ground4->y = 14.5f; // [m]
	ground4->w = 10.2f; // [m]
	ground4->h = 3.3f; // [m]

	ground5->x = 30.5f; // [m]
	ground5->y = 0.0f; // [m]
	ground5->w = 5.2f; // [m]
	ground5->h = 3.7f; // [m]



	// Create Water
	water = Water();
	water.x = 10.2f; // Start where ground ends [m]
	water.y = 0.0f; // [m]
	water.w = 5.2f; // [m]
	water.h = 3.6f; // [m]
	water.density = 50.0f; // [kg/m^3]
	water.vx = -1.0f; // [m/s]
	water.vy = -5.0f; // [m/s]

	// Create atmosphere
	atmosphere = Atmosphere();
	atmosphere.windx = 10.0f; // [m/s]
	atmosphere.windy = 5.0f; // [m/s]
	atmosphere.density = 1.0f; // [kg/m^3]

	// Set static properties of the ball
	ball->mass = 10.0f; // [kg]
	ball->surface = 1.0f; // [m^2]
	ball->radius = 0.5f; // [m]
	ball->cd = 0.4f; // [-]
	ball->cl = 1.2f; // [-]
	ball->b = 10.0f; // [...]
	ball->coef_friction = 0.9f; // [-]
	ball->coef_restitution = 0.8f; // [-]

	// Set initial position and velocity of the ball
	ball->x = 2.0f;
	ball->y = 4.0f;
	ball->vx = 5.0f;
	ball->vy = 10.0f;

	// Add ball to the collection
	bodies.add(ball);
	grounds.add(ground1);
	grounds.add(ground2);
	grounds.add(ground3);
	grounds.add(ground4);
	grounds.add(ground5);

	return true;
}

// 
update_status ModulePhysics::PreUpdate()
{
	p2List_item<PhysBody*>* item = bodies.getFirst();
	PhysBody* aux = NULL;

	// Process all balls in the scenario
	while (item != NULL)
	{
		aux = item->data;
		// Skip ball if physics not enabled
		if (!aux->physics_enabled)
		{
			continue;
		}

		// Step #0: Clear old values
		// ----------------------------------------------------------------------------------------

		// Reset total acceleration and total accumulated force of the ball
		aux->fx = aux->fy = 0.0f;
		aux->ax = aux->ay = 0.0f;

		// Step #1: Compute forces
		// ----------------------------------------------------------------------------------------

		// Gravity force
		float fgx = aux->mass * 0.0f;
		float fgy = aux->mass * -10.0f; // Let's assume gravity is constant and downwards
		aux->fx += fgx; aux->fy += fgy; // Add this force to ball's total force

		// Aerodynamic Drag force (only when not in water)
		if (!is_colliding_with_water(aux, water))
		{
			float fdx = 0.0f; float fdy = 0.0f;
			compute_aerodynamic_drag(fdx, fdy, aux, atmosphere);
			aux->fx += fdx; aux->fy += fdy; // Add this force to ball's total force
		}

		// Hydrodynamic forces (only when in water)
		if (is_colliding_with_water(aux, water))
		{
			// Hydrodynamic Drag force
			float fhdx = 0.0f; float fhdy = 0.0f;
			compute_hydrodynamic_drag(fhdx, fhdy, aux, water);
			aux->fx += fhdx; aux->fy += fhdy; // Add this force to ball's total force

			// Hydrodynamic Buoyancy force
			float fhbx = 0.0f; float fhby = 0.0f;
			compute_hydrodynamic_buoyancy(fhbx, fhby, aux, water);
			aux->fx += fhbx; aux->fy += fhby; // Add this force to ball's total force
		}

		// Other forces
		// ...

		// Step #2: 2nd Newton's Law
		// ----------------------------------------------------------------------------------------

		// SUM_Forces = mass * accel --> accel = SUM_Forces / mass
		aux->ax = aux->fx / aux->mass;
		aux->ay = aux->fy / aux->mass;

		// Step #3: Integrate --> from accel to new velocity & new position
		// ----------------------------------------------------------------------------------------

		// We will use the 2nd order "Velocity Verlet" method for integration.
		integrator_velocity_verlet(aux, dt);

		// Step #4: solve collisions
		// ----------------------------------------------------------------------------------------
		p2List_item<Ground*>* ground = grounds.getFirst();

		while (ground != NULL)
		{
			// Solve collision between ball and ground
			if (is_colliding_with_ground(aux, ground->data))
			{
				// TP ball to ground surface
				if (aux->x > ground->data->x && aux->y > ground->data->y && aux->x < ground->data->x + ground->data->w) {
					aux->y = ground->data->y + ground->data->h + aux->radius;
					// Elastic bounce with ground
					aux->vy = -aux->vy;
				}

				
				if (aux->x >= ground->data->x + ground->data->w && aux->y > ground->data->y) {
					aux->x = ground->data->x + ground->data->w + aux->radius;
					aux->vx = -aux->vx;
				}
					

				if (aux->x <= ground->data->x && aux->y > ground->data->y) {
					aux->x = ground->data->x - aux->radius;
					aux->vx = -aux->vx;
				}

				// FUYM non-elasticity
				aux->vx *= aux->coef_friction;
				aux->vy *= aux->coef_restitution;
			}
			ground = ground->next;
		}	
		
		item = item->next;
	}

	return UPDATE_CONTINUE;
}

// 
update_status ModulePhysics::PostUpdate()
{
	if(app->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	if(!debug)
		return UPDATE_CONTINUE;

	// Colors
	int color_r, color_g, color_b;

	// Draw grounds
	color_r = 0; color_g = 255; color_b = 0;
	app->renderer->DrawQuad(ground1->pixels(), color_r, color_g, color_b);

	color_r = 0; color_g = 255; color_b = 0;
	app->renderer->DrawQuad(ground2->pixels(), color_r, color_g, color_b);

	color_r = 0; color_g = 255; color_b = 0;
	app->renderer->DrawQuad(ground3->pixels(), color_r, color_g, color_b);

	color_r = 0; color_g = 255; color_b = 0;
	app->renderer->DrawQuad(ground4->pixels(), color_r, color_g, color_b);

	color_r = 0; color_g = 255; color_b = 0;
	app->renderer->DrawQuad(ground5->pixels(), color_r, color_g, color_b);


	// Draw water
	color_r = 0; color_g = 0; color_b = 255;
	app->renderer->DrawQuad(water.pixels(), color_r, color_g, color_b);


	p2List_item<PhysBody*>* item = bodies.getFirst();
	// Draw all balls in the scenario
	while (item != NULL)
	{
		// Convert from physical magnitudes to geometrical pixels
		int pos_x = METERS_TO_PIXELS(item->data->x);
		int pos_y = SCREEN_HEIGHT - METERS_TO_PIXELS(item->data->y);
		int size_r = METERS_TO_PIXELS(item->data->radius);

		// Select color
		if (item->data->physics_enabled)
		{
			color_r = 255; color_g = 255; color_b = 255;
		}
		else
		{
			color_r = 255; color_g = 0; color_b = 0;
		}

		// Draw ball
		app->renderer->DrawCircle(pos_x, pos_y, size_r, color_r, color_g, color_b);
		item = item->next;
	}

	return UPDATE_CONTINUE;
}


// Called before quitting
bool ModulePhysics::CleanUp()
{
	LOG("Destroying physics world");

	bodies.clear();
	grounds.clear();

	return true;
}

// Compute modulus of a vector
float modulus(float vx, float vy)
{
	return std::sqrt(vx * vx + vy * vy);
}

// Compute Aerodynamic Drag force
void compute_aerodynamic_drag(float& fx, float& fy, const PhysBody* body, const Atmosphere& atmosphere)
{
	float rel_vel[2] = { body->vx - atmosphere.windx, body->vy - atmosphere.windy }; // Relative velocity
	float speed = modulus(rel_vel[0], rel_vel[1]); // Modulus of the relative velocity
	float rel_vel_unitary[2] = { rel_vel[0] / speed, rel_vel[1] / speed }; // Unitary vector of relative velocity
	float fdrag_modulus = 0.5f * atmosphere.density * speed * speed * body->surface * body->cd; // Drag force (modulus)
	fx = -rel_vel_unitary[0] * fdrag_modulus; // Drag is antiparallel to relative velocity
	fy = -rel_vel_unitary[1] * fdrag_modulus; // Drag is antiparallel to relative velocity
}

// Compute Hydrodynamic Drag force
void compute_hydrodynamic_drag(float& fx, float& fy, const PhysBody* body, const Water& water)
{
	float rel_vel[2] = { body->vx - water.vx, body->vy - water.vy }; // Relative velocity
	float speed = modulus(rel_vel[0], rel_vel[1]); // Modulus of the relative velocity
	float rel_vel_unitary[2] = { rel_vel[0] / speed, rel_vel[1] / speed }; // Unitary vector of relative velocity
	float fdrag_modulus = body->b * speed; // Drag force (modulus)
	fx = -rel_vel_unitary[0] * fdrag_modulus; // Drag is antiparallel to relative velocity
	fy = -rel_vel_unitary[1] * fdrag_modulus; // Drag is antiparallel to relative velocity
}

// Compute Hydrodynamic Buoyancy force
void compute_hydrodynamic_buoyancy(float& fx, float& fy, const PhysBody* body, const Water& water)
{
	// Compute submerged area (assume ball is a rectangle, for simplicity)
	float water_top_level = water.y + water.h; // Water top level y
	float h = 2.0f * body->radius; // Ball "hitbox" height
	float surf = h * (water_top_level - body->y); // Submerged surface
	if ((body->y + body->radius) < water_top_level) surf = h * h; // If ball completely submerged, use just all ball area
	surf *= 0.4; // FUYM to adjust values (should compute the area of circle segment correctly instead; I'm too lazy for that)

	// Compute Buoyancy force
	double fbuoyancy_modulus = water.density * 10.0 * surf; // Buoyancy force (modulus)
	fx = 0.0; // Buoyancy is parallel to pressure gradient
	fy = fbuoyancy_modulus; // Buoyancy is parallel to pressure gradient
}

// Integration scheme: Velocity Verlet
void integrator_velocity_verlet(PhysBody* body, float dt)
{
	body->x += body->vx * dt + 0.5f * body->ax * dt * dt;
	body->y += body->vy * dt + 0.5f * body->ay * dt * dt;
	body->vx += body->ax * dt;
	body->vy += body->ay * dt;
}

// Detect collision with ground
bool is_colliding_with_ground(const PhysBody* body, const Ground* ground)
{
	float rect_x = (ground->x + ground->w / 2.0f); // Center of rectangle
	float rect_y = (ground->y + ground->h / 2.0f); // Center of rectangle
	return check_collision_circle_rectangle(body->x, body->y, body->radius, rect_x, rect_y, ground->w, ground->h);
}

// Detect collision with water
bool is_colliding_with_water(const PhysBody* body, const Water& water)
{
	float rect_x = (water.x + water.w / 2.0f); // Center of rectangle
	float rect_y = (water.y + water.h / 2.0f); // Center of rectangle
	return check_collision_circle_rectangle(body->x, body->y, body->radius, rect_x, rect_y, water.w, water.h);
}

// Detect collision between circle and rectange
bool check_collision_circle_rectangle(float cx, float cy, float cr, float rx, float ry, float rw, float rh)
{
	// Algorithm taken from https://stackoverflow.com/a/402010

	// Distance from center of circle to center of rectangle
	float dist_x = std::abs(cx - rx);
	float dist_y = std::abs(cy - ry);

	// If circle is further than half-rectangle, not intersecting
	if (dist_x > (rw / 2.0f + cr)) { return false; }
	if (dist_y > (rh / 2.0f + cr)) { return false; }

	// If circle is closer than half-rectangle, is intersecting
	if (dist_x <= (rw / 2.0f)) { return true; }
	if (dist_y <= (rh / 2.0f)) { return true; }

	// If all of above fails, check corners
	float a = dist_x - rw / 2.0f;
	float b = dist_y - rh / 2.0f;
	float cornerDistance_sq = a * a + b * b;
	return (cornerDistance_sq <= (cr * cr));
}

// Convert from meters to pixels (for SDL drawing)
SDL_Rect Ground::pixels()
{
	SDL_Rect pos_px{};
	pos_px.x = METERS_TO_PIXELS(x);
	pos_px.y = SCREEN_HEIGHT - METERS_TO_PIXELS(y);
	pos_px.w = METERS_TO_PIXELS(w);
	pos_px.h = METERS_TO_PIXELS(-h); // Can I do this? LOL
	return pos_px;
}

PhysBody* ModulePhysics::CreateCircle(int x, int y, float radius, ColliderType ctype) {

	PhysBody* body = new PhysBody();

	// Set static properties of the ball
	body->mass = 5.0f; // [kg]
	body->surface = 1.0f; // [m^2]
	body->radius = radius; // [m]
	body->cd = 0.4f; // [-]
	body->cl = 1.2f; // [-]
	body->b = 10.0f; // [...]
	body->coef_friction = 0.9f; // [-]
	body->coef_restitution = 0.8f; // [-]

	// Set initial position and velocity of the ball
	body->x = x;
	body->y = y;
	body->vx = 0.0f;
	body->vy = 0.0f;

	body->cType = ctype;

	return body;
}