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
	void RestartLap();

public:
	Timer jump_cooldown;
	PhysVehicle3D* vehicle;
	float turn;
	float acceleration;
	float brake;
	bool dead = false;
	bool lap = false;
	bool win = false;
	int timer = 0;
	Timer game_timer;
	int timerTurbo = 0;

	int lowtime_total = 0;
	int lowtime_mil = 0;
	int lowtime_sec = 0;
	int lowtime_min = 0;

	bool best_time = false;
	int lastBestTime = 0;

	int secExact = 0;
	int miliExact = 0;

	bool turbo = false;
	bool turboUp = false;
	bool turboWait = false;
	int timeTurbo = 1;



	float bestMinutes_f;
	int bestMinutes_i;
	float bestDecimal_minutes;
	float bestSeconds_f;
	int bestSeconds_i;
	float bestDecimal_seconds;
	int bestMiliseconds_i;

	bool restartLap = false;
	int laps = 0;

	bool notZero = false;
	bool firstTime = false;

	float posX;
	float posY;
	float posZ;

	//Audio
	uint jumpFx;
	uint turboFx;
	uint deadFx;

};