#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"

struct PhysVehicle3D;

#define MAX_ACCELERATION 2000.0f
#define TURN_DEGREES 15.0f * DEGTORAD
#define BRAKE_POWER 500.0f
#define JUMP_COOLDOWN 1.3f
#define JUMP_IMPULSE 5000.0f
#define SPEED_LIMIT 140.0f

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();
	void Restart();

public:
	Timer jump_cooldown;
	PhysVehicle3D* vehicle;
	float turn;
	float acceleration;
	float brake;
	bool dead = false;
	bool win = false;
	int timer = 0;
	Timer game_timer;
	int timerTurbo = 0;

	int lowtime_total = 0;
	int lowtime_mil = 0;
	int lowtime_sec = 0;
	int lowtime_min = 0;

	bool best_time = true;

	int secExact = 0;

	bool turbo = false;
	bool turboUp = false;
	bool turboWait = false;
	int timeTurbo = 1;


	//Audio
	uint jumpFx;
	uint turboFx;
};