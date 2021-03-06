#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "Primitive.h"
#include "PhysVehicle3D.h"
#include "PhysBody3D.h"
#include "ModuleAudio.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled), vehicle(NULL)
{
	turn = acceleration = brake = 0.0f;
	jump_cooldown.Start();
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	jumpFx = App->audio->LoadFx("Assets/jump.wav");
	turboFx = App->audio->LoadFx("Assets/turbo.wav");
	deadFx = App->audio->LoadFx("Assets/dead.wav");
	lapFx = App->audio->LoadFx("Assets/lap_end.wav");
	winFx = App->audio->LoadFx("Assets/win.wav");

	VehicleInfo car;
	// Car properties ----------------------------------------
	car.new_parts = 7;
	car.new_parts_size = new vec3[car.new_parts];
	car.new_parts_offset = new vec3[car.new_parts];
	car.color = new Color[car.new_parts];

	car.chassis_size.Set(3.3, 1.6, 4);
	car.chassis_offset.Set(0, 1.2, 0);

	car.new_parts_size[0].Set(car.chassis_size.x, 1.2, 1);
	car.new_parts_offset[0].Set(0, 1.2, 1.5);
	car.color[0] = Red;

	car.new_parts_size[1].Set(0.2, 1, 3);
	car.new_parts_offset[1].Set(0.5, 1.2, 0);
	car.color[1] = Pink;

	car.new_parts_size[2].Set(0.2, 1, 3);
	car.new_parts_offset[2].Set(-0.5, 1.2, 0);
	car.color[2] = Pink;

	car.new_parts_size[3].Set(0.2, 1, 3);
	car.new_parts_offset[3].Set(1.0, 1.2, 0);
	car.color[3] = Pink;

	car.new_parts_size[4].Set(0.2, 1, 3);
	car.new_parts_offset[4].Set(-1.0, 1.2, 0);
	car.color[4] = Pink;

	car.new_parts_size[5].Set(car.chassis_size.x, 1.2, 1);
	car.new_parts_offset[5].Set(0, 1.2, -1.5);
	car.color[5] = Red;

	car.new_parts_size[6].Set(0.8, 1.4, 2);
	car.new_parts_offset[6].Set(0, 1.4, 0);
	car.color[6] = Cyan;


	car.mass = 800.0f;
	car.suspensionStiffness = 4.0f;
	car.suspensionCompression = 0.83f;
	car.suspensionDamping = 0.5f;
	car.maxSuspensionTravelCm = 1000.0f;
	car.frictionSlip = 50.5;
	car.maxSuspensionForce = 6000.0f;

	// Wheel properties ---------------------------------------
	float connection_height = 1.1f;
	float wheel_radius = 0.6f;
	float wheel_width = 0.5;
	float suspensionRestLength = 1.0f;

	// Don't change anything below this line ------------------

	float half_width = car.chassis_size.x * 0.5f;
	float half_length = car.chassis_size.z * 0.5f;

	vec3 direction(0, -1, 0);
	vec3 axis(-1, 0, 0);

	car.num_wheels = 4;
	car.wheels = new Wheel[4];

	// FRONT-LEFT ------------------------
	car.wheels[0].connection.Set(half_width - 0.2f * wheel_width, connection_height, half_length - wheel_radius);
	car.wheels[0].direction = direction;
	car.wheels[0].axis = axis;
	car.wheels[0].suspensionRestLength = suspensionRestLength;
	car.wheels[0].radius = wheel_radius;
	car.wheels[0].width = wheel_width;
	car.wheels[0].front = true;
	car.wheels[0].drive = true;
	car.wheels[0].brake = false;
	car.wheels[0].steering = true;

	// FRONT-RIGHT ------------------------
	car.wheels[1].connection.Set(-half_width + 0.2f * wheel_width, connection_height, half_length - wheel_radius);
	car.wheels[1].direction = direction;
	car.wheels[1].axis = axis;
	car.wheels[1].suspensionRestLength = suspensionRestLength;
	car.wheels[1].radius = wheel_radius;
	car.wheels[1].width = wheel_width;
	car.wheels[1].front = true;
	car.wheels[1].drive = true;
	car.wheels[1].brake = false;
	car.wheels[1].steering = true;

	// REAR-LEFT ------------------------
	car.wheels[2].connection.Set(half_width - 0.2f * wheel_width, connection_height, -half_length + wheel_radius);
	car.wheels[2].direction = direction;
	car.wheels[2].axis = axis;
	car.wheels[2].suspensionRestLength = suspensionRestLength;
	car.wheels[2].radius = wheel_radius;
	car.wheels[2].width = wheel_width;
	car.wheels[2].front = false;
	car.wheels[2].drive = false;
	car.wheels[2].brake = true;
	car.wheels[2].steering = false;

	// REAR-RIGHT ------------------------
	car.wheels[3].connection.Set(-half_width + 0.2f * wheel_width, connection_height, -half_length + wheel_radius);
	car.wheels[3].direction = direction;
	car.wheels[3].axis = axis;
	car.wheels[3].suspensionRestLength = suspensionRestLength;
	car.wheels[3].radius = wheel_radius;
	car.wheels[3].width = wheel_width;
	car.wheels[3].front = false;
	car.wheels[3].drive = false;
	car.wheels[3].brake = true;
	car.wheels[3].steering = false;

	vehicle = App->physics->AddVehicle(car);
	vehicle->SetPos(0, 0,7);
	//vehicle->SetPos(0, 0, -12);
	//vehicle->SetPos(-100, 20, 490);
	laps = 0;
	game_timer.Start();

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	return true;
}

void ModulePlayer::RestartDead()
{
	if (timer < 100) {
		App->player->vehicle->Brake(BRAKE_POWER);
		//game_timer.Stop();
	}
	else
	{
		//game_timer.Start();

		//timer = 0;
		dead = false;
		App->scene_intro->finishDead = false;
	}
	timer++;
}

void ModulePlayer::RestartLap()
{

	game_timer.Stop();
	timer = 0;
	game_timer.Start();
	restartLap = true;

	lapTime = true;

}

void ModulePlayer::RestartGame()
{
	laps = 0;
	vehicle->SetPos(0, 0, 7);
	game_timer.Stop();
	timer = 0;
	game_timer.Start();
	restartLap = true;
	dead = false;
	lapTime = true;
}

// Update: draw background
update_status ModulePlayer::Update(float dt)
{
	turn = acceleration = brake = 0.0f;


	int VehicleVelocity = App->player->vehicle->GetKmh();

	posX = vehicle->getPosX();
	posY = vehicle->getPosY();
	posZ = vehicle->getPosZ();


	if (laps < 3)
	{
		if ((App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) && (VehicleVelocity <= SPEED_LIMIT))
		{
			if (vehicle->GetKmh() < -3)
				brake = BRAKE_POWER;
			acceleration = MAX_ACCELERATION;
		}

		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
		{
			if (turn < TURN_DEGREES)
				turn += TURN_DEGREES;
		}

		if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
		{
			if (turn > -TURN_DEGREES)
				turn -= TURN_DEGREES;
		}

		if ((App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) && (VehicleVelocity >= -SPEED_LIMIT))
		{
			if (vehicle->GetKmh() > 5)
				brake = BRAKE_POWER;
			acceleration = -MAX_ACCELERATION;
		}

		if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT) {
			brake = BRAKE_POWER;
		}


		if (App->input->GetKey(SDL_SCANCODE_M) == KEY_DOWN && App->scene_intro->jumpEnabled)
		{

			if ((jump_cooldown.Read() * 0.001) >= JUMP_COOLDOWN)
			{
				vehicle->Push(0.0f, JUMP_IMPULSE, 0.0f);
				jump_cooldown.Start();
				App->audio->PlayFx(jumpFx);
			}
		}

		//turbo
		if (App->input->GetKey(SDL_SCANCODE_Q) == KEY_DOWN && !turboWait)
		{
			turbo = true;
			App->audio->PlayFx(turboFx);

		}

		if ((App->input->GetKey(SDL_SCANCODE_R) == KEY_REPEAT))
		{
			vehicle->vehicle->getRigidBody()->setLinearVelocity(btVector3(0, 0, 0));
			vehicle->vehicle->getRigidBody()->setWorldTransform(reposition);
		}
	}
	else
	{
		brake = BRAKE_POWER;
		gameend = true;
		win = true;

		if ((App->input->GetKey(SDL_SCANCODE_C) == KEY_REPEAT))
		{
			RestartGame();
			gameend = false;
			win = false;
		}

	}

	if (dead == true)
	{
		RestartDead();
		App->audio->PlayFx(deadFx);
	}


	if (!turbo) vehicle->ApplyEngineForce(acceleration);
	vehicle->Turn(turn);
	vehicle->Brake(brake);

	vehicle->Render();

	//Minuts:Segons:Milisegons

	int timer_milisec_read = game_timer.Read();

	float minutes_f = timer_milisec_read * 0.001 * 0.0167;
	int minutes_i = minutes_f;
	float decimal_minutes = minutes_f - minutes_i;
	float seconds_f = decimal_minutes * 60;
	int seconds_i = seconds_f;
	float decimal_seconds = seconds_f - seconds_i;
	int miliseconds_i = decimal_seconds * 1000;

	secExact = game_timer.GetSec();
	miliExact = game_timer.GetMiliSec();

	//if(secExact !=0) lowtime_total = miliExact;

	//if (miliExact != 0)
	if (!lapTime)
	{
		bestMinutes_f = minutes_f;
		bestMinutes_i = minutes_i;
		bestDecimal_minutes = decimal_minutes;
		bestSeconds_f = seconds_f;
		bestSeconds_i = seconds_i;
		bestDecimal_seconds = decimal_seconds;
		bestMiliseconds_i = miliseconds_i;
		lowtime_total = miliExact;
		notZero = true;
	}

	if (lapTime && notZero)
	{
		best_time = true;
		notZero = false;
		lapTime = false;
	}

	if (best_time == true)
	{

		if (lastBestTime > lowtime_total)
		{
			lowtime_mil = bestMiliseconds_i;
			lowtime_sec = bestSeconds_i;
			lowtime_min = bestMinutes_i;
			lastBestTime = lowtime_total;
		}

		if (lastBestTime == 0)
		{
			lowtime_mil = bestMiliseconds_i;
			lowtime_sec = bestSeconds_i;
			lowtime_min = bestMinutes_i;
			lastBestTime = lowtime_total;
		}
		best_time = false;
	}



	if (win == false)
	{

		char title[80];
		if (laps == 0)
		{
			lowtime_mil = 0;
			lowtime_sec = 0;
			lowtime_min = 0;
			lastBestTime = 0;
		}

		sprintf_s(title, " Time: %i:%2.i:%4.i        Velocity: %4.1f Km/h       Best Time: %i:%i:%i", minutes_i, seconds_i, miliseconds_i, vehicle->GetKmh(), lowtime_min, lowtime_sec, lowtime_mil);
		App->window->SetTitle(title);
	}
	if (gameend)
	{
		char title[120];
		sprintf_s(title, "Best Time: %i:%i:%i                         YOU WIN                                      PRESS C TO CONTINUE", lowtime_min, lowtime_sec, lowtime_mil);
		App->window->SetTitle(title);
	}
	if (turbo)
	{
		timerTurbo = secExact + timeTurbo;
		turboUp = true;
		turbo = false;
		turboWait = true;
	}

	if (turboUp)
	{
		if (secExact <= timerTurbo + timeTurbo * 2)
		{
			vehicle->ApplyEngineForce(MAX_ACCELERATION * 3);
			if (lap == true)
			{
				timerTurbo = 2;
			}
		}
		else
		{
			turboUp = false;
		}
	}

	if (turboWait)
	{
		if (secExact >= timerTurbo + timeTurbo * 20) turboWait = false;
	}


	if (lap)
	{
		RestartLap();
		if(laps < 2) App->audio->PlayFx(lapFx);
		else App->audio->PlayFx(winFx);
		lap = false;
		laps++;
	}


	return UPDATE_CONTINUE;
}