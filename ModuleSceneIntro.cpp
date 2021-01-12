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
	ground = new Plane(0, 1, 0, 0);
	ground->axis = true;
	ground->color.Set(255, 255, 255);
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	//App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	//App->camera->LookAt(vec3(0, 0, 0));

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

	//Cube wall4(310, 50, 10);
	//wall4.SetPos(0, 0, 310);
	//App->physics->AddBody(wall4, 0);

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


	Cube ramp1(30, 60, 1);
	ramp1.SetPos(80, 5, 100);
	ramp1.SetRotation(90 - 20, { 1,0,0 });
	App->physics->AddBody(ramp1, 0);


	Cube wall20(2, 30, 150);
	wall20.SetPos(95, 10, 170);
	App->physics->AddBody(wall20, 0);

	Cube wall21(2, 30, 150);
	wall21.SetPos(65, 10, 170);
	App->physics->AddBody(wall21, 0);

	Cube wall22(30, 2, 150);
	wall22.SetPos(80, 10, 195);
	App->physics->AddBody(wall22, 0);

	Cube wall23(120, 2, 30);
	wall23.SetPos(40, 10, 260);
	App->physics->AddBody(wall23, 0);

	Cube wall24(30, 2, 100);
	wall24.SetPos(-35, 10, 295);
	App->physics->AddBody(wall24, 0);

	Cube wall25(10, 2, 100);
	wall25.SetPos(-35, 10, 395);
	App->physics->AddBody(wall25, 0);

	Cube wall26(80, 2, 10);
	wall26.SetPos(0, 10, 440);
	App->physics->AddBody(wall26, 0);

	Cube wall27(10, 2, 100);
	wall27.SetPos(40, 10, 485);
	App->physics->AddBody(wall27, 0);

	Cube wall28(10, 2, 110);
	wall28.SetPos(40, 10, 620);
	App->physics->AddBody(wall28, 0);
	
	timer_laps.Start();


	//death sensor for testing
	/////////////////////////////////////////////////
	s.size = vec3(300, 1, 700);
	s.SetPos(0, 5, 500);

	death_sensor = App->physics->AddBody(s, 0.0f);
	death_sensor->SetSensor(true);
	death_sensor->collision_listeners.add(this);

	/////////////////////////////////////////////////


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
	ground->Render();

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

	//Cube wall4(310, 50, 10);
	//wall4.SetPos(0, 0, 310);
	//wall4.Render();

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

	Cube ramp1(30, 60, 1);
	ramp1.SetRotation(90 - 20, { 1,0,0 });
	ramp1.SetPos(80, 5, 100);
	ramp1.Render();

	Cube wall20(2, 30, 150);
	wall20.SetPos(95, 10, 170);
	wall20.Render();

	Cube wall21(2, 30, 150);
	wall21.SetPos(65, 10, 170);
	wall21.Render();

	Cube wall22(30, 2, 150);
	wall22.SetPos(80, 10, 195);
	wall22.Render();

	Cube wall23(120, 2, 30);
	wall23.SetPos(40, 10, 260);
	wall23.Render();

	Cube wall24(30, 2, 100);
	wall24.SetPos(-35, 10, 295);
	wall24.Render();

	Cube wall25(10, 2, 100);
	wall25.SetPos(-35, 10, 395);
	wall25.Render();

	Cube wall26(80, 2, 10);
	wall26.SetPos(0, 10, 440);
	wall26.Render();

	Cube wall27(10, 2, 100);
	wall27.SetPos(40, 10, 485);
	wall27.Render();

	Cube wall28(10, 2, 110);
	wall28.SetPos(40, 10, 620);
	wall28.Render();


	death_sensor->GetTransform(&s.transform);
	//s.Render();

	//KM on title window
	char title[200];
	sprintf_s(title, "%.1f Km/h - %02i:%02i", App->player->vehicle->GetKmh(), timer_laps.GetSec() / 60, timer_laps.GetSec() % 60);	
	App->window->SetTitle(title);
	
	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	LOG("Hit!");
	if (body1 == death_sensor)
	{
		App->player->dead = true;
		App->player->vehicle->SetPos(0, 2, 0);
	}
}

