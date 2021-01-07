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

	//circuit
	Cube wall5(2, 10, 100);
	wall5.SetPos(-15, 0, 30);
	App->physics->AddBody(wall5, 0);

	Cube wall6(2, 10, 130);
	wall6.SetPos(15, 0, 45);
	App->physics->AddBody(wall6, 0);

	Cube wall7(32, 10, 2);
	wall7.SetPos(0, 0, -20);
	App->physics->AddBody(wall7, 0);

	Cube wall8(70, 10, 2);
	wall8.SetPos(-60, 0, 80);
	App->physics->AddBody(wall8, 0);

	Cube wall9(70, 10, 2);
	wall9.SetPos(-20, 0, 110);
	App->physics->AddBody(wall9, 0);

	Cube wall10(2, 10, 70);
	wall10.SetPos(-85, 0, 110);
	App->physics->AddBody(wall10, 0);

	Cube wall11(150, 10, 2);
	wall11.SetPos(-10, 0, 145);
	App->physics->AddBody(wall11, 0);

	Cube wall12(2, 10, 110);
	wall12.SetPos(65, 0, 95);
	App->physics->AddBody(wall12, 0);

	Cube wall13(50, 10, 2);
	wall13.SetPos(90, 0, 40);
	App->physics->AddBody(wall13, 0);

	Cube wall14(60, 10, 2);
	wall14.SetPos(45, 0, 10);
	App->physics->AddBody(wall14, 0);

	Cube wall15(2, 10, 80);
	wall15.SetPos(115, 0, 0);
	App->physics->AddBody(wall15, 0);

	Cube wall16(2, 10, 70);
	wall16.SetPos(75, 0, -25);
	App->physics->AddBody(wall16, 0);

	Cube wall17(70, 10, 2);
	wall17.SetPos(110, 0, -60);
	App->physics->AddBody(wall17, 0);

	Cube wall18(50, 10, 2);
	wall18.SetPos(120, 0, 70);
	App->physics->AddBody(wall18, 0);

	Cube wall19(2, 10, 40);
	wall19.SetPos(95, 0, 90);
	App->physics->AddBody(wall19, 0);


	//Cube ramp1(40, 40, 1);
	//ramp1.SetRotation(120.0f, vec3(1.0f, 0.0f, 1.0f));
	//ramp1.SetPos(0, 0, 50);
	//App->physics->AddBody(ramp1, 0);

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
	//limits
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

	//circuit
	Cube wall5(2, 10, 100);
	wall5.SetPos(-15, 0, 30);
	wall5.Render();

	Cube wall6(2, 10, 130);
	wall6.SetPos(15, 0, 45);
	wall6.Render();

	Cube wall7(32, 10, 2);
	wall7.SetPos(0, 0, -20);
	wall7.Render();

	Cube wall8(70, 10, 2);
	wall8.SetPos(-50, 0, 80);
	wall8.Render();

	Cube wall9(70, 10, 2);
	wall9.SetPos(-20, 0, 110);
	wall9.Render();

	Cube wall10(2, 10, 70);
	wall10.SetPos(-85, 0, 110);
	wall10.Render();

	Cube wall11(150, 10, 2);
	wall11.SetPos(-10, 0, 145);
	wall11.Render();

	Cube wall12(2, 10, 110);
	wall12.SetPos(65, 0, 95);
	wall12.Render();

	Cube wall13(50, 10, 2);
	wall13.SetPos(90, 0, 40);
	wall13.Render();

	Cube wall14(60, 10, 2);
	wall14.SetPos(45, 0, 10);
	wall14.Render();

	Cube wall15(2, 10, 80);
	wall15.SetPos(115, 0, 0);
	wall15.Render();

	Cube wall16(2, 10, 70);
	wall16.SetPos(75, 0, -25);
	wall16.Render();

	Cube wall17(70, 10, 2);
	wall17.SetPos(110, 0, -60);
	wall17.Render();

	Cube wall18(50, 10, 2);
	wall18.SetPos(120, 0, 70);
	wall18.Render();

	Cube wall19(2, 10, 40);
	wall19.SetPos(95, 0, 90);
	wall19.Render();
	//Cube ramp1(40, 40, 1);
	//ramp1.SetRotation(120.0f, vec3(1.0f, 0.0f, 5.0f));
	//ramp1.SetPos(0, 0, 50);
	//ramp1.Render();

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}

