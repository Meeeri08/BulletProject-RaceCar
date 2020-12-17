#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include "ModulePlayer.h"
#include "PhysVehicle3D.h"
#include "Module.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	//Collisions
	//limits
	Cube wall1(310, 50, 10);
	wall1.SetPos(0, 0, -100);
	App->physics->AddBody(wall1, 0);

	Cube wall2(10, 50, 300);
	wall2.SetPos(-150, 0, 155);
	App->physics->AddBody(wall2, 0);

	Cube wall3(10, 50, 300);
	wall3.SetPos(150, 0, 155);
	App->physics->AddBody(wall3, 0);

	Cube wall4(310, 50, 10);
	wall4.SetPos(0, 0, 310);
	App->physics->AddBody(wall4, 0);

	//start
	Cube wall5(2, 10, 100);
	wall5.SetPos(-15, 0, 30);
	App->physics->AddBody(wall5, 0);

	Cube wall6(2, 10, 100);
	wall6.SetPos(15, 0, 30);
	App->physics->AddBody(wall6, 0);

	Cube wall7(32, 10, 2);
	wall7.SetPos(0, 0, -20);
	App->physics->AddBody(wall7, 0);

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();

	Cube wall1(310, 50, 10);
	wall1.SetPos(0, 0, -100);
	wall1.Render();

	Cube wall2(10, 50, 500);
	wall2.SetPos(-150, 0, 155);
	wall2.Render();

	Cube wall3(10, 50, 500);
	wall3.SetPos(150, 0, 155);
	wall3.Render();

	Cube wall4(310, 50, 10);
	wall4.SetPos(0, 0, 310);
	wall4.Render();

	Cube wall5(2, 10, 100);
	wall5.SetPos(-15, 0, 30);
	wall5.Render();

	Cube wall6(2, 10, 100);
	wall6.SetPos(15, 0, 30);
	wall6.Render();

	Cube wall7(32, 10, 2);
	wall7.SetPos(0, 0, -20);
	wall7.Render();
	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}

