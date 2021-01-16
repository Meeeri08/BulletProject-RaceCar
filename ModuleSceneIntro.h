#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Primitive.h"

#define MAX_SNAKE 2

struct PhysBody3D;
struct PhysMotor3D;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);

	void CreateCube(vec3 dimensions, vec3 pos, int rot = 0, vec3 vecRot = { 0,0,0 });
	void DrawMap();
	void DrawCollisions();

public:
	Plane* ground;
	PhysBody3D* pb_chassis;
	Cube p_chassis;

	PhysBody3D* pb_wheel;
	Cylinder p_wheel;

	PhysBody3D* pb_wheel2;
	Cylinder p_wheel2;

	PhysMotor3D* left_wheel;
	PhysMotor3D* right_wheel;

	Timer timer_laps;
	Cube s, death, win;
	PhysBody3D* death_sensor = nullptr;
	uint best_time = 6000;
	p2List<Cube> cube;

	PhysBody3D* jump_sensor = nullptr;
	bool jumpEnabled = true;
	PhysBody3D* jump_sensor1 = nullptr;
	PhysBody3D* jump_sensor2 = nullptr;
	PhysBody3D* jump_sensor3 = nullptr;
	PhysBody3D* jump_sensor4 = nullptr;
	//checkpoints
	PhysBody3D* checkpoint_sensor0 = nullptr;
	PhysBody3D* checkpoint_sensor1 = nullptr;

	PhysBody3D* checkpoint_activeFinal = nullptr;
	PhysBody3D* checkpoint_final = nullptr;
	PhysBody3D* barrier = nullptr;

	bool checkpoint = false;
	bool checkpointTaken0 = false;
	bool checkpointTaken1 = false;

	bool checkpointActiveFinal = false;
	bool checkpointFinalTaken1 = false;


	float posX;
	float posY;
	float posZ;

	bool finishDead = false;
};
