#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"

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
	Cube wall1(310, 10, 10);
	wall1.SetPos(0, 0, 0);
	App->physics->AddBody(wall1, 0);

	Cube wall2(10, 10, 300);
	wall2.SetPos(-150, 0, 155);
	App->physics->AddBody(wall2, 0);

	Cube wall3(10, 10, 300);
	wall3.SetPos(150, 0, 155);
	App->physics->AddBody(wall3, 0);

	Cube wall4(310, 10, 10);
	wall4.SetPos(0, 0, 310);
	App->physics->AddBody(wall4, 0);

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

	Cube wall1(310, 10, 10);
	wall1.SetPos(0, 0, 0);
	wall1.Render();

	Cube wall2(10, 10, 300);
	wall2.SetPos(-150, 0, 155);
	wall2.Render();

	Cube wall3(10, 10, 300);
	wall3.SetPos(150, 0, 155);
	wall3.Render();

	Cube wall4(310, 10, 10);
	wall4.SetPos(0, 0, 310);
	wall4.Render();




	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}

