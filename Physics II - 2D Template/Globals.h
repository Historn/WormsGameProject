#ifndef _GLOBALS_H
#define _GLOBALS_H

#include <windows.h>
#include <stdio.h>
#include "math.h"

#define LOG(format, ...) log(__FILE__, __LINE__, format, __VA_ARGS__);

void log(const char file[], int line, const char* format, ...);

#define CAP(n) ((n <= 0.0f) ? n=0.0f : (n >= 1.0f) ? n=1.0f : n=n)

#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f

typedef unsigned int uint;

enum update_status
{
	UPDATE_CONTINUE = 1,
	UPDATE_STOP,
	UPDATE_ERROR
};

struct Vec2D 
{
	/// Default constructor does nothing (for performance).
	Vec2D() {}

	/// Construct using coordinates.
	Vec2D(float x, float y) : x(x), y(y) {}

	/// Set this vector to all zeros.
	void SetZero() { x = 0.0f; y = 0.0f; }

	/// Set this vector to some specified coordinates.
	void Set(float x_, float y_) { x = x_; y = y_; }

	/// Negate this vector.
	Vec2D operator -() const { Vec2D v; v.Set(-x, -y); return v; }

	/// Read from and indexed element.
	float operator () (int i) const
	{
		return (&x)[i];
	}

	/// Write to an indexed element.
	float& operator () (int i)
	{
		return (&x)[i];
	}

	/// Add a vector to this vector.
	void operator += (const Vec2D& v)
	{
		x += v.x; y += v.y;
	}

	/// Subtract a vector from this vector.
	void operator -= (const Vec2D& v)
	{
		x -= v.x; y -= v.y;
	}

	/// Multiply this vector by a scalar.
	void operator *= (float a)
	{
		x *= a; y *= a;
	}

	/// Get the length of this vector (the norm).
	float Length() const
	{
		return sqrt(x * x + y * y);
	}

	/// Get the length squared. For performance, use this instead of
	/// Vec2D::Length (if possible).
	float LengthSquared() const
	{
		return x * x + y * y;
	}

	float x, y;
};

// Configuration -----------
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define SCREEN_SIZE 1
#define WIN_FULLSCREEN false
#define WIN_RESIZABLE false
#define WIN_BORDERLESS false
#define WIN_FULLSCREEN_DESKTOP false
#define VSYNC true	//If it is FALSE game is limited to 60fps, if is TRUE it uses screen refresh rate
#define FPS 60		//Change this value to set the FPS as you want
#define TITLE "Worms Game"

#endif //_GLOBALS_H