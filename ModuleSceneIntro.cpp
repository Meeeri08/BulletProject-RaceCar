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

	DrawCollisions();

	timer_laps.Start();

	//int a = 0;

	//death sensor
	/////////////////////////////////////////////////
	s.size = vec3(300, 1, 697);
	s.SetPos(0, 5, 500);

	death_sensor = App->physics->AddBody(s, 0.0f);
	death_sensor->SetSensor(true);
	death_sensor->collision_listeners.add(this);

	/////////////////////////////////////////////////

	App->audio->PlayMusic("Assets/gamemusic.ogg");


	//jump enabled sensor
	s.size = vec3(25, 2, 2);
	s.SetPos(80, 17, 125);

	jump_sensor = App->physics->AddBody(s, 0.0f);
	jump_sensor->SetSensor(true);
	jump_sensor->collision_listeners.add(this);


	s.size = vec3(25, 2, 150);
	s.SetPos(80, 12, 210);

	jump_sensor1 = App->physics->AddBody(s, 0.0f);
	jump_sensor1->SetSensor(true);
	jump_sensor1->collision_listeners.add(this);


	s.size = vec3(25, 15, 2);
	s.SetPos(-100, 13, 580);

	jump_sensor2 = App->physics->AddBody(s, 0.0f);
	jump_sensor2->SetSensor(true);
	jump_sensor2->collision_listeners.add(this);


	s.size = vec3(20, 2, 50);
	s.SetPos(-100, 12, 500);

	jump_sensor3 = App->physics->AddBody(s, 0.0f);
	jump_sensor3->SetSensor(true);
	jump_sensor3->collision_listeners.add(this);

	s.size = vec3(100, 2, 200);
	s.SetPos(-90, 7, 530);

	jump_sensor4 = App->physics->AddBody(s, 0.0f);
	jump_sensor4->SetSensor(true);
	jump_sensor4->collision_listeners.add(this);
	//Checkpoint 0
	s.size = vec3(25, 1, 1);
	s.SetPos(0, 2, 8);

	checkpoint_sensor0 = App->physics->AddBody(s, 0.0f);
	checkpoint_sensor0->SetSensor(true);
	checkpoint_sensor0->collision_listeners.add(this);

	//Checkpoints
	s.size = vec3(10, 1, 1);
	s.SetPos(80, 2, 70);

	checkpoint_sensor1 = App->physics->AddBody(s, 0.0f);
	checkpoint_sensor1->SetSensor(true);
	checkpoint_sensor1->collision_listeners.add(this);


	//checkpoint final
	s.size = vec3(25, 1, 1);
	s.SetPos(0, 1, 0);

	checkpoint_activeFinal = App->physics->AddBody(s, 0.0f);
	checkpoint_activeFinal->SetSensor(true);
	checkpoint_activeFinal->collision_listeners.add(this);


	s.size = vec3(25, 1, 1);
	s.SetPos(0, 1, 10);

	checkpoint_final = App->physics->AddBody(s, 0.0f);
	checkpoint_final->SetSensor(true);
	checkpoint_final->collision_listeners.add(this);


	s.size = vec3(25, 20, 1);
	s.SetPos(0, 1, 2);

	barrier = App->physics->AddBody(s, 0.0f);
	barrier->SetSensor(true);
	barrier->collision_listeners.add(this);

	/////POSAR IF PER CHECPOINT FINAL
	//Cube wall7(32, 21, 1);
	//wall7.SetPos(0, 1, 6);
	//App->physics->AddBody(wall7, 0);


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

	DrawMap();

	/*	if (!checkpointTaken0)
		{
			Cube checkpoint0(25, 1, 1);
			checkpoint0.color.Set(0.0f, 0.0f, 1.0f);
			checkpoint0.SetPos(0, 2, 18);
			checkpoint0.Render();
		}*/

	if (!checkpointTaken1)
	{
		Cube checkpoint1(10, 1, 1);
		checkpoint1.color.Set(0.0f, 0.0f, 1.0f);
		checkpoint1.SetPos(80, 2, 70);
		checkpoint1.Render();
	}

	//if (!checkpointActiveFinal)
	//{
	//	Cube checkpoint_activeFinal(25, 1, 1);
	//	checkpoint_activeFinal.color.Set(0.0f, 0.0f, 1.0f);
	//	checkpoint_activeFinal.SetPos(0, 1, 0);
	//	checkpoint_activeFinal.Render();
	//}
	//if (!checkpointFinalTaken1 && checkpointActiveFinal)
	//{
	//	Cube checkpoint_final(25, 1, 1);
	//	checkpoint_final.color.Set(0.0f, 0.0f, 1.0f);
	//	checkpoint_final.SetPos(0, 1, 9);
	//	checkpoint_final.Render();
	//}

	if (App->player->dead && !finishDead)
	{

		App->player->vehicle->SetPos(posX, posY, posZ);
		checkpointTaken1 = false;
		finishDead = true;
	}


	/////POSAR IF PER CHECPOINT FINAL
	//Cube wall7(32, 21, 1);
	//wall7.SetPos(0, 1, 6);
	//App->physics->AddBody(wall7, 0);

	death_sensor->GetTransform(&s.transform);

	//checkpoints
	checkpoint_sensor0->GetTransform(&s.transform);
	checkpoint_sensor1->GetTransform(&s.transform);


	checkpoint_sensor1->GetTransform(&s.transform);
	checkpoint_final->GetTransform(&s.transform);
	barrier->GetTransform(&s.transform);


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
		App->player->vehicle->SetPos(0, 2, 7);
		/*posX = 0;
		posY = 2;
		posZ = 7;*/
		/*	posX = App->player->posX;
			posY = App->player->posY;
			posZ = App->player->posZ;*/

	}
	if (body1 == jump_sensor)
	{
		jumpEnabled = false;
	}
	if (body1 == jump_sensor1)
	{
		jumpEnabled = true;
	}
	if (body1 == jump_sensor2)
	{
		jumpEnabled = false;
	}
	if (body1 == jump_sensor3)
	{
		jumpEnabled = true;
	}
	if (body1 == jump_sensor4)
	{
		jumpEnabled = true;
	}

	if (body1 == checkpoint_sensor0)
	{
		posX = App->player->posX;
		posY = App->player->posY;
		posZ = App->player->posZ;
		checkpointTaken0 = true;

	}
	if (body1 == checkpoint_sensor1)
	{
		posX = App->player->posX;
		posY = App->player->posY;
		posZ = App->player->posZ;
		checkpointTaken1 = true;

	}


	if (body1 == checkpoint_activeFinal)
	{
		posX = App->player->posX;
		posY = App->player->posY;
		posZ = App->player->posZ;
		checkpointActiveFinal = true;

	}
	if (body1 == checkpoint_final && checkpointActiveFinal)
	{
		posX = App->player->posX;
		posY = App->player->posY;
		posZ = App->player->posZ;
		checkpointFinalTaken1 = true;
		App->player->lap = true;
		checkpointActiveFinal = false;
		//App->player->Restart();
		//App->player->dead = true;

	}

	if (body1 == barrier && !checkpointActiveFinal)
	{

		//Cube wall7(32, 21, 1);
		//wall7.SetPos(0, 1, 2);
		//App->physics->AddBody(wall7, 0);

	}
	
}

void ModuleSceneIntro::DrawCollisions()
{

	//Collisions
	Cube wallGround(290, 1, 600);
	wallGround.SetPos(0, 0, 20);
	App->physics->AddBody(wallGround, 0);


	//limits
	Cube wall1(310, 50, 10);
	wall1.SetPos(0, 25, -100);
	App->physics->AddBody(wall1, 0);

	Cube wall2(10, 50, 800);
	wall2.SetPos(-150, 25, 305);
	App->physics->AddBody(wall2, 0);

	Cube wall3(10, 50, 800);
	wall3.SetPos(150, 25, 305);
	App->physics->AddBody(wall3, 0);

	Cube wall4(310, 50, 10);
	wall4.SetPos(0, 25, 700);
	App->physics->AddBody(wall4, 0);

	///START
	Cube start1(1, 16, 1);
	start1.SetPos(14, 6.5, 10);
	App->physics->AddBody(start1, 0);

	Cube start2(1, 16, 1);
	start2.SetPos(-14, 6.5, 10);
	App->physics->AddBody(start2, 0);


	///obstacles
	Sphere sphere1(4);
	sphere1.SetPos(0, 3, 75);
	App->physics->AddBody(sphere1, 0);

	Sphere sphere2(4);
	sphere2.SetPos(40, 3, 70);
	App->physics->AddBody(sphere2, 0);

	Sphere sphere3(4);
	sphere3.SetPos(120, 3, 55);
	App->physics->AddBody(sphere3, 0);

	Sphere sphere4(4);
	sphere4.SetPos(85, 3, 10);
	App->physics->AddBody(sphere4, 0);

	//circuit
	Cube wall5(2, 30, 100);
	wall5.SetPos(-15, 0, 30);
	App->physics->AddBody(wall5, 0);

	Cube wall6(2, 30, 130);
	wall6.SetPos(15, 0, 45);
	App->physics->AddBody(wall6, 0);

	Cube wall8(70, 30, 2);
	wall8.SetPos(-50, 0, 80);
	App->physics->AddBody(wall8, 0);

	Cube wall9(70, 30, 2);
	wall9.SetPos(-20, 0, 110);
	App->physics->AddBody(wall9, 0);

	Cube wall10(2, 30, 65);
	wall10.SetPos(-85, 0, 113);
	App->physics->AddBody(wall10, 0);

	Cube wall11(150, 30, 2);
	wall11.SetPos(-10, 0, 145);
	App->physics->AddBody(wall11, 0);

	Cube wall12(2, 30, 110);
	wall12.SetPos(65, 0, 95);
	App->physics->AddBody(wall12, 0);

	Cube wall13(50, 30, 2);
	wall13.SetPos(90, 0, 40);
	App->physics->AddBody(wall13, 0);

	Cube wall14(60, 30, 2);
	wall14.SetPos(45, 0, 10);
	App->physics->AddBody(wall14, 0);

	Cube wall15(2, 30, 80);
	wall15.SetPos(115, 0, 0);
	App->physics->AddBody(wall15, 0);

	Cube wall16(2, 30, 70);
	wall16.SetPos(75, 0, -25);
	App->physics->AddBody(wall16, 0);

	Cube wall17(70, 30, 2);
	wall17.SetPos(110, 0, -60);
	App->physics->AddBody(wall17, 0);

	Cube wall18(50, 30, 2);
	wall18.SetPos(120, 0, 70);
	App->physics->AddBody(wall18, 0);

	Cube wall19(2, 30, 40);
	wall19.SetPos(95, 0, 90);
	App->physics->AddBody(wall19, 0);

	////zone 2

	Cube ramp1(30, 60, 1);
	ramp1.SetPos(80, 5, 100);
	ramp1.SetRotation(90 - 20, { 1,0,0 });
	App->physics->AddBody(ramp1, 0);

	//hight walls
	Cube wall20(2, 30, 180);
	wall20.SetPos(95, 10, 185);
	App->physics->AddBody(wall20, 0);

	Cube wall21(2, 30, 150);
	wall21.SetPos(65, 10, 170);
	App->physics->AddBody(wall21, 0);

	//floating ground
	Cube wall22(30, 2, 150);
	wall22.SetPos(80, 10, 195);
	App->physics->AddBody(wall22, 0);

	Cube wall23(120, 2, 30);
	wall23.SetPos(40, 10, 260);
	App->physics->AddBody(wall23, 0);


	Cube wall24(30, 2, 100);
	wall24.SetPos(-35, 10, 295);
	App->physics->AddBody(wall24, 0);

	///paret anti cheat
	//Cube wallAnti(2, 20, 100);
	//wallAnti.SetPos(-51, 15, 295);
	//App->physics->AddBody(wallAnti, 0);


	///

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

	Cube wall29(70, 2, 10);
	wall29.SetPos(10, 10, 675);
	App->physics->AddBody(wall29, 0);

	Cube wall30(50, 2, 10);
	wall30.SetPos(-70, 10, 675);
	App->physics->AddBody(wall30, 0);

	Cube wall31(10, 2, 70);
	wall31.SetPos(-100, 10, 645);
	App->physics->AddBody(wall31, 0);

	Cube wall32(40, 2, 10);
	wall32.SetPos(-100, 10, 605);
	wall32.Render();
	App->physics->AddBody(wall32, 0);

	Cube ramp2(10, 15, 0.5);
	ramp2.SetRotation(90 + 8, { 1,0,0 });
	ramp2.SetPos(-100, 11.8, 593);
	App->physics->AddBody(ramp2, 0);

	Cube wall33(10, 2, 90);
	wall33.SetPos(-125, 10, 565);
	App->physics->AddBody(wall33, 0);

	Cube wall34(10, 2, 90);
	wall34.SetPos(-75, 10, 565);
	App->physics->AddBody(wall34, 0);

	Cube wall35(40, 2, 10);
	wall35.SetPos(-100, 10, 525);
	App->physics->AddBody(wall35, 0);

	Cube wall36(10, 2, 50);
	wall36.SetPos(-100, 10, 495);
	App->physics->AddBody(wall36, 0);


	///parkour

	Cube wall37(20, 2, 30);
	wall37.SetPos(-100, 10, 430);
	App->physics->AddBody(wall37, 0);

	Cube wall38(20, 2, 35);
	wall38.SetPos(-100, 10, 375);
	App->physics->AddBody(wall38, 0);

	/*Cube wall39(20, 2, 20);
	wall39.SetPos(-100, 10, 360);
	App->physics->AddBody(wall39, 0);*/

	////
	Cube wall40(20, 2, 30);
	wall40.SetPos(-100, 10, 325);
	App->physics->AddBody(wall40, 0);


	Cube wall41(60, 2, 80);
	wall41.SetPos(-100, 10, 270);
	App->physics->AddBody(wall41, 0);

	///pivots
	Cube pivot1(5, 20, 5);
	pivot1.SetPos(-100, 20, 280);
	App->physics->AddBody(pivot1, 0);

	Cube pivot2(5, 20, 5);
	pivot2.SetPos(-110, 20, 270);
	App->physics->AddBody(pivot2, 0);

	Cube pivot3(5, 20, 5);
	pivot3.SetPos(-90, 20, 295);
	App->physics->AddBody(pivot3, 0);

	Cube pivot4(5, 20, 5);
	pivot4.SetPos(-115, 20, 250);
	App->physics->AddBody(pivot4, 0);

	Cube pivot5(5, 20, 5);
	pivot5.SetPos(-85, 20, 260);
	App->physics->AddBody(pivot5, 0);

	Cube pivot6(5, 20, 5);
	pivot6.SetPos(-120, 20, 295);
	App->physics->AddBody(pivot6, 0);

	Cube pivot7(5, 20, 5);
	pivot7.SetPos(-80, 20, 245);
	App->physics->AddBody(pivot7, 0);

	Cube pivot8(5, 20, 5);
	pivot8.SetPos(-110, 20, 240);
	App->physics->AddBody(pivot8, 0);

	Cube pivot9(5, 20, 5);
	pivot9.SetPos(-115, 20, 285);
	App->physics->AddBody(pivot9, 0);

	Cube pivot10(5, 20, 5);
	pivot10.SetPos(-90, 20, 270);
	App->physics->AddBody(pivot10, 0);

	Cube pivot11(5, 20, 5);
	pivot11.SetPos(-88, 20, 250);
	App->physics->AddBody(pivot11, 0);


	Cube wall42(10, 2, 50);
	wall42.SetPos(-120, 10, 205);
	App->physics->AddBody(wall42, 0);


	Cube ramp3(30, 60, 1);
	ramp3.SetRotation(90 - 10, { 1,0,0 });
	ramp3.SetPos(-120, 5, 150);
	App->physics->AddBody(ramp3, 0);


	Cube wall43(2, 30, 230);
	wall43.SetPos(-105, 0, 65);
	App->physics->AddBody(wall43, 0);

	Cube wall44(2, 30, 280);
	wall44.SetPos(-135, 0, 40);
	App->physics->AddBody(wall44, 0);

	Cube wall45(90, 30, 2);
	wall45.SetPos(-60, 0, -50);
	App->physics->AddBody(wall45, 0);

	Cube wall46(150, 30, 2);
	wall46.SetPos(-60, 0, -95);
	App->physics->AddBody(wall46, 0);

	Cube wall47(2, 30, 30);
	wall47.SetPos(-15, 0, -35);
	App->physics->AddBody(wall47, 0);

	Cube wall48(2, 30, 80);
	wall48.SetPos(15, 0, -60);
	App->physics->AddBody(wall48, 0);
}



void ModuleSceneIntro::DrawMap()
{
	//ground
	Cube wallGround(290, 1, 800);
	wallGround.color.Set(0.4f, 1.0f, 1.0f);
	wallGround.SetPos(0, 0, 300);
	wallGround.Render();

	Cube wallHead(290, 1, 800);
	wallGround.color.Set(1.0f, 0.0f, 0.4f);
	wallGround.SetPos(0, 50, 300);
	wallGround.Render();

	//limits
	Cube wall1(310, 50, 10);
	wall1.color.Set(1.0f, 0.0f, 0.4f);
	wall1.SetPos(0, 25, -100);
	wall1.Render();

	Cube wall2(10, 50, 800);
	wall2.color.Set(1.0f, 0.0f, 0.4f);
	wall2.SetPos(-150, 25, 305);
	wall2.Render();

	Cube wall3(10, 50, 800);
	wall3.color.Set(1.0f, 0.0f, 0.4f);
	wall3.SetPos(150, 25, 305);
	wall3.Render();

	Cube wall4(310, 50, 10);
	wall4.color.Set(1.0f, 0.0f, 0.4f);
	wall4.SetPos(0, 25, 700);
	wall4.Render();



	//START
	Cube start1(1, 16, 1);
	start1.SetPos(14, 6.5, 10);
	start1.Render();


	Cube start2(1, 16, 1);
	start2.SetPos(-14, 6.5, 10);
	start2.Render();

	////////////////////////////////////////////////////////

	Cube flag4(1, 1, 1);
	flag4.color.Set(1.0f, 1.0f, 1.0f);
	flag4.SetPos(-13, 14, 10);
	flag4.Render();

	Cube flag5(1, 1, 1);
	flag5.color.Set(0.0f, 0.0f, 0.0f);
	flag5.SetPos(-13, 13, 10);
	flag5.Render();

	Cube flag6(1, 1, 1);
	flag6.color.Set(1.0f, 1.0f, 1.0f);
	flag6.SetPos(-13, 12, 10);
	flag6.Render();

	Cube flag7(1, 1, 1);
	flag7.color.Set(0.0f, 0.0f, 0.0f);
	flag7.SetPos(-12, 14, 10);
	flag7.Render();

	Cube flag8(1, 1, 1);
	flag8.color.Set(1.0f, 1.0f, 1.0f);
	flag8.SetPos(-12, 13, 10);
	flag8.Render();

	Cube flag9(1, 1, 1);
	flag9.color.Set(0.0f, 0.0f, 0.0f);
	flag9.SetPos(-12, 12, 10);
	flag9.Render();

	Cube flag10(1, 1, 1);
	flag10.color.Set(1.0f, 1.0f, 1.0f);
	flag10.SetPos(-11, 14, 10);
	flag10.Render();

	Cube flag11(1, 1, 1);
	flag11.color.Set(0.0f, 0.0f, 0.0f);
	flag11.SetPos(-11, 13, 10);
	flag11.Render();

	Cube flag12(1, 1, 1);
	flag12.color.Set(1.0f, 1.0f, 1.0f);
	flag12.SetPos(-11, 12, 10);
	flag12.Render();

	Cube flag13(1, 1, 1);
	flag13.color.Set(0.0f, 0.0f, 0.0f);
	flag13.SetPos(-10, 14, 10);
	flag13.Render();

	Cube flag14(1, 1, 1);
	flag14.color.Set(1.0f, 1.0f, 1.0f);
	flag14.SetPos(-10, 13, 10);
	flag14.Render();

	Cube flag15(1, 1, 1);
	flag15.color.Set(0.0f, 0.0f, 0.0f);
	flag15.SetPos(-10, 12, 10);
	flag15.Render();

	Cube flag16(1, 1, 1);
	flag16.color.Set(1.0f, 1.0f, 1.0f);
	flag16.SetPos(-9, 14, 10);
	flag16.Render();

	Cube flag17(1, 1, 1);
	flag17.color.Set(0.0f, 0.0f, 0.0f);
	flag17.SetPos(-9, 13, 10);
	flag17.Render();

	Cube flag18(1, 1, 1);
	flag18.color.Set(1.0f, 1.0f, 1.0f);
	flag18.SetPos(-9, 12, 10);
	flag18.Render();

	Cube flag19(1, 1, 1);
	flag19.color.Set(0.0f, 0.0f, 0.0f);
	flag19.SetPos(-8, 14, 10);
	flag19.Render();

	Cube flag20(1, 1, 1);
	flag20.color.Set(1.0f, 1.0f, 1.0f);
	flag20.SetPos(-8, 13, 10);
	flag20.Render();

	Cube flag21(1, 1, 1);
	flag21.color.Set(0.0f, 0.0f, 0.0f);
	flag21.SetPos(-8, 12, 10);
	flag21.Render();

	Cube flag22(1, 1, 1);
	flag22.color.Set(1.0f, 1.0f, 1.0f);
	flag22.SetPos(-7, 14, 10);
	flag22.Render();

	Cube flag23(1, 1, 1);
	flag23.color.Set(0.0f, 0.0f, 0.0f);
	flag23.SetPos(-7, 13, 10);
	flag23.Render();

	Cube flag24(1, 1, 1);
	flag24.color.Set(1.0f, 1.0f, 1.0f);
	flag24.SetPos(-7, 12, 10);
	flag24.Render();

	Cube flag25(1, 1, 1);
	flag25.color.Set(0.0f, 0.0f, 0.0f);
	flag25.SetPos(-6, 14, 10);
	flag25.Render();

	Cube flag26(1, 1, 1);
	flag26.color.Set(1.0f, 1.0f, 1.0f);
	flag26.SetPos(-6, 13, 10);
	flag26.Render();

	Cube flag27(1, 1, 1);
	flag27.color.Set(0.0f, 0.0f, 0.0f);
	flag27.SetPos(-6, 12, 10);
	flag27.Render();

	Cube flag28(1, 1, 1);
	flag28.color.Set(1.0f, 1.0f, 1.0f);
	flag28.SetPos(-5, 14, 10);
	flag28.Render();

	Cube flag29(1, 1, 1);
	flag29.color.Set(0.0f, 0.0f, 0.0f);
	flag29.SetPos(-5, 13, 10);
	flag29.Render();

	Cube flag30(1, 1, 1);
	flag30.color.Set(1.0f, 1.0f, 1.0f);
	flag30.SetPos(-5, 12, 10);
	flag30.Render();

	Cube flag31(1, 1, 1);
	flag31.color.Set(0.0f, 0.0f, 0.0f);
	flag31.SetPos(-4, 14, 10);
	flag31.Render();

	Cube flag32(1, 1, 1);
	flag32.color.Set(1.0f, 1.0f, 1.0f);
	flag32.SetPos(-4, 13, 10);
	flag32.Render();

	Cube flag33(1, 1, 1);
	flag33.color.Set(0.0f, 0.0f, 0.0f);
	flag33.SetPos(-4, 12, 10);
	flag33.Render();

	Cube flag34(1, 1, 1);
	flag34.color.Set(1.0f, 1.0f, 1.0f);
	flag34.SetPos(-3, 14, 10);
	flag34.Render();

	Cube flag35(1, 1, 1);
	flag35.color.Set(0.0f, 0.0f, 0.0f);
	flag35.SetPos(-3, 13, 10);
	flag35.Render();

	Cube flag36(1, 1, 1);
	flag36.color.Set(1.0f, 1.0f, 1.0f);
	flag36.SetPos(-3, 12, 10);
	flag36.Render();

	Cube flag37(1, 1, 1);
	flag37.color.Set(0.0f, 0.0f, 0.0f);
	flag37.SetPos(-2, 14, 10);
	flag37.Render();

	Cube flag38(1, 1, 1);
	flag38.color.Set(1.0f, 1.0f, 1.0f);
	flag38.SetPos(-2, 13, 10);
	flag38.Render();

	Cube flag39(1, 1, 1);
	flag39.color.Set(0.0f, 0.0f, 0.0f);
	flag39.SetPos(-2, 12, 10);
	flag39.Render();

	Cube flag40(1, 1, 1);
	flag40.color.Set(1.0f, 1.0f, 1.0f);
	flag40.SetPos(-1, 14, 10);
	flag40.Render();

	Cube flag41(1, 1, 1);
	flag41.color.Set(0.0f, 0.0f, 0.0f);
	flag41.SetPos(-1, 13, 10);
	flag41.Render();

	Cube flag42(1, 1, 1);
	flag42.color.Set(1.0f, 1.0f, 1.0f);
	flag42.SetPos(-1, 12, 10);
	flag42.Render();

	Cube flag43(1, 1, 1);
	flag43.color.Set(0.0f, 0.0f, 0.0f);
	flag43.SetPos(0, 14, 10);
	flag43.Render();

	Cube flag44(1, 1, 1);
	flag44.color.Set(1.0f, 1.0f, 1.0f);
	flag44.SetPos(0, 13, 10);
	flag44.Render();

	Cube flag45(1, 1, 1);
	flag45.color.Set(0.0f, 0.0f, 0.0f);
	flag45.SetPos(0, 12, 10);
	flag45.Render();

	Cube flag46(1, 1, 1);
	flag46.color.Set(1.0f, 1.0f, 1.0f);
	flag46.SetPos(1, 14, 10);
	flag46.Render();

	Cube flag47(1, 1, 1);
	flag47.color.Set(0.0f, 0.0f, 0.0f);
	flag47.SetPos(1, 13, 10);
	flag47.Render();

	Cube flag48(1, 1, 1);
	flag48.color.Set(1.0f, 1.0f, 1.0f);
	flag48.SetPos(1, 12, 10);
	flag48.Render();

	Cube flag49(1, 1, 1);
	flag49.color.Set(0.0f, 0.0f, 0.0f);
	flag49.SetPos(2, 14, 10);
	flag49.Render();

	Cube flag50(1, 1, 1);
	flag50.color.Set(1.0f, 1.0f, 1.0f);
	flag50.SetPos(2, 13, 10);
	flag50.Render();

	Cube flag51(1, 1, 1);
	flag51.color.Set(0.0f, 0.0f, 0.0f);
	flag51.SetPos(2, 12, 10);
	flag51.Render();

	Cube flag52(1, 1, 1);
	flag52.color.Set(1.0f, 1.0f, 1.0f);
	flag52.SetPos(3, 14, 10);
	flag52.Render();

	Cube flag53(1, 1, 1);
	flag53.color.Set(0.0f, 0.0f, 0.0f);
	flag53.SetPos(3, 13, 10);
	flag53.Render();

	Cube flag54(1, 1, 1);
	flag54.color.Set(1.0f, 1.0f, 1.0f);
	flag54.SetPos(3, 12, 10);
	flag54.Render();

	Cube flag55(1, 1, 1);
	flag55.color.Set(0.0f, 0.0f, 0.0f);
	flag55.SetPos(4, 14, 10);
	flag55.Render();

	Cube flag56(1, 1, 1);
	flag56.color.Set(1.0f, 1.0f, 1.0f);
	flag56.SetPos(4, 13, 10);
	flag56.Render();

	Cube flag57(1, 1, 1);
	flag57.color.Set(0.0f, 0.0f, 0.0f);
	flag57.SetPos(4, 12, 10);
	flag57.Render();

	Cube flag58(1, 1, 1);
	flag58.color.Set(1.0f, 1.0f, 1.0f);
	flag58.SetPos(5, 14, 10);
	flag58.Render();

	Cube flag59(1, 1, 1);
	flag59.color.Set(0.0f, 0.0f, 0.0f);
	flag59.SetPos(5, 13, 10);
	flag59.Render();

	Cube flag60(1, 1, 1);
	flag60.color.Set(1.0f, 1.0f, 1.0f);
	flag60.SetPos(5, 12, 10);
	flag60.Render();

	Cube flag61(1, 1, 1);
	flag61.color.Set(0.0f, 0.0f, 0.0f);
	flag61.SetPos(6, 14, 10);
	flag61.Render();

	Cube flag62(1, 1, 1);
	flag62.color.Set(1.0f, 1.0f, 1.0f);
	flag62.SetPos(6, 13, 10);
	flag62.Render();

	Cube flag63(1, 1, 1);
	flag63.color.Set(0.0f, 0.0f, 0.0f);
	flag63.SetPos(6, 12, 10);
	flag63.Render();

	Cube flag64(1, 1, 1);
	flag64.color.Set(1.0f, 1.0f, 1.0f);
	flag64.SetPos(7, 14, 10);
	flag64.Render();

	Cube flag65(1, 1, 1);
	flag65.color.Set(0.0f, 0.0f, 0.0f);
	flag65.SetPos(7, 13, 10);
	flag65.Render();

	Cube flag66(1, 1, 1);
	flag66.color.Set(1.0f, 1.0f, 1.0f);
	flag66.SetPos(7, 12, 10);
	flag66.Render();

	Cube flag67(1, 1, 1);
	flag67.color.Set(0.0f, 0.0f, 0.0f);
	flag67.SetPos(8, 14, 10);
	flag67.Render();

	Cube flag68(1, 1, 1);
	flag68.color.Set(1.0f, 1.0f, 1.0f);
	flag68.SetPos(8, 13, 10);
	flag68.Render();

	Cube flag69(1, 1, 1);
	flag69.color.Set(0.0f, 0.0f, 0.0f);
	flag69.SetPos(8, 12, 10);
	flag69.Render();

	Cube flag70(1, 1, 1);
	flag70.color.Set(1.0f, 1.0f, 1.0f);
	flag70.SetPos(9, 14, 10);
	flag70.Render();

	Cube flag71(1, 1, 1);
	flag71.color.Set(0.0f, 0.0f, 0.0f);
	flag71.SetPos(9, 13, 10);
	flag71.Render();

	Cube flag72(1, 1, 1);
	flag72.color.Set(1.0f, 1.0f, 1.0f);
	flag72.SetPos(9, 12, 10);
	flag72.Render();

	Cube flag73(1, 1, 1);
	flag73.color.Set(0.0f, 0.0f, 0.0f);
	flag73.SetPos(10, 14, 10);
	flag73.Render();

	Cube flag74(1, 1, 1);
	flag74.color.Set(1.0f, 1.0f, 1.0f);
	flag74.SetPos(10, 13, 10);
	flag74.Render();

	Cube flag75(1, 1, 1);
	flag75.color.Set(0.0f, 0.0f, 0.0f);
	flag75.SetPos(10, 12, 10);
	flag75.Render();

	Cube flag76(1, 1, 1);
	flag76.color.Set(1.0f, 1.0f, 1.0f);
	flag76.SetPos(11, 14, 10);
	flag76.Render();

	Cube flag77(1, 1, 1);
	flag77.color.Set(0.0f, 0.0f, 0.0f);
	flag77.SetPos(11, 13, 10);
	flag77.Render();

	Cube flag78(1, 1, 1);
	flag78.color.Set(1.0f, 1.0f, 1.0f);
	flag78.SetPos(11, 12, 10);
	flag78.Render();

	Cube flag79(1, 1, 1);
	flag78.color.Set(0.0f, 0.0f, 0.0f);
	flag78.SetPos(12, 14, 10);
	flag78.Render();

	Cube flag80(1, 1, 1);
	flag80.color.Set(1.0f, 1.0f, 1.0f);
	flag80.SetPos(12, 13, 10);
	flag80.Render();

	Cube flag81(1, 1, 1);
	flag81.color.Set(0.0f, 0.0f, 0.0f);
	flag81.SetPos(12, 12, 10);
	flag81.Render();

	Cube flag82(1, 1, 1);
	flag82.color.Set(1.0f, 1.0f, 1.0f);
	flag82.SetPos(13, 14, 10);
	flag82.Render();

	Cube flag83(1, 1, 1);
	flag83.color.Set(0.0f, 0.0f, 0.0f);
	flag83.SetPos(13, 13, 10);
	flag83.Render();

	Cube flag84(1, 1, 1);
	flag84.color.Set(1.0f, 1.0f, 1.0f);
	flag84.SetPos(13, 12, 10);
	flag84.Render();




	///////////////////////////////////////////////////////////////




	///obstacles
	Sphere sphere1(4);
	sphere1.color.Set(1.0f, 1.0f, 0.0f);
	sphere1.SetPos(0, 3, 75);
	sphere1.Render();

	Sphere sphere2(4);
	sphere2.color.Set(1.0f, 1.0f, 0.0f);
	sphere2.SetPos(40, 3, 70);
	sphere2.Render();

	Sphere sphere3(4);
	sphere3.color.Set(1.0f, 1.0f, 0.0f);
	sphere3.SetPos(120, 3, 55);
	sphere3.Render();

	Sphere sphere4(4);
	sphere4.color.Set(1.0f, 1.0f, 0.0f);
	sphere4.SetPos(85, 3, 10);
	sphere4.Render();

	//circuit
	Cube wall5(2, 30, 100);
	wall5.color.Set(1.0f, 0.0f, 1.0f);
	wall5.SetPos(-15, 0, 30);
	wall5.Render();

	Cube wall6(2, 30, 130);
	wall6.color.Set(1.0f, 0.0f, 1.0f);
	wall6.SetPos(15, 0, 45);
	wall6.Render();



	/////POSAR IF PER CHECPOINT FINAL
	//Cube wall7(32, 1, 1);
	//wall7.color.Set(1.0f, 0.0f, 1.0f);
	//wall7.SetPos(0, 1, 9);
	//wall7.Render();

	Cube wall8(70, 30, 2);
	wall8.color.Set(1.0f, 0.0f, 1.0f);
	wall8.SetPos(-50, 0, 80);
	wall8.Render();

	Cube wall9(70, 30, 2);
	wall9.color.Set(1.0f, 0.0f, 1.0f);
	wall9.SetPos(-20, 0, 110);
	wall9.Render();

	Cube wall10(2, 30, 65);
	wall10.color.Set(1.0f, 0.0f, 1.0f);
	wall10.SetPos(-85, 0, 113);
	wall10.Render();

	Cube wall11(150, 30, 2);
	wall11.color.Set(1.0f, 0.0f, 1.0f);
	wall11.SetPos(-10, 0, 145);
	wall11.Render();

	Cube wall12(2, 30, 110);
	wall12.color.Set(1.0f, 0.0f, 1.0f);
	wall12.SetPos(65, 0, 95);
	wall12.Render();

	Cube wall13(50, 30, 2);
	wall13.color.Set(1.0f, 0.0f, 1.0f);
	wall13.SetPos(90, 0, 40);
	wall13.Render();

	Cube wall14(60, 30, 2);
	wall14.color.Set(1.0f, 0.0f, 1.0f);
	wall14.SetPos(45, 0, 10);
	wall14.Render();

	Cube wall15(2, 30, 80);
	wall15.color.Set(1.0f, 0.0f, 1.0f);
	wall15.SetPos(115, 0, 0);
	wall15.Render();

	Cube wall16(2, 30, 70);
	wall16.color.Set(1.0f, 0.0f, 1.0f);
	wall16.SetPos(75, 0, -25);
	wall16.Render();

	Cube wall17(70, 30, 2);
	wall17.color.Set(1.0f, 0.0f, 1.0f);
	wall17.SetPos(110, 0, -60);
	wall17.Render();

	Cube wall18(50, 30, 2);
	wall18.color.Set(1.0f, 0.0f, 1.0f);
	wall18.SetPos(120, 0, 70);
	wall18.Render();

	Cube wall19(2, 30, 40);
	wall19.color.Set(1.0f, 0.0f, 1.0f);
	wall19.SetPos(95, 0, 90);
	wall19.Render();

	/////zone 2
	Cube ramp1(30, 60, 1);
	ramp1.color.Set(0.4f, 1.0f, 1.0f);
	ramp1.SetRotation(90 - 20, { 1,0,0 });
	ramp1.SetPos(80, 5, 100);
	ramp1.Render();

	//high walls
	Cube wall20(2, 30, 180);
	wall20.color.Set(1.0f, 0.0f, 1.0f);
	wall20.SetPos(95, 10, 185);
	wall20.Render();

	Cube wall21(2, 30, 150);
	wall21.color.Set(1.0f, 0.0f, 1.0f);
	wall21.SetPos(65, 10, 170);
	wall21.Render();

	//floating ground
	Cube wall22(30, 2, 150);
	wall22.color.Set(0.6f, 0.2f, 1.0f);
	wall22.SetPos(80, 10, 195);
	wall22.Render();

	Cube wall23(120, 2, 30);
	wall23.color.Set(0.6f, 0.2f, 1.0f);
	wall23.SetPos(40, 10, 260);
	wall23.Render();

	Cube wall24(30, 2, 100);
	wall24.color.Set(0.6f, 0.2f, 1.0f);
	wall24.SetPos(-35, 10, 295);
	wall24.Render();

	///anticheat wall
	Cube wallAnti(2, 20, 100);
	wallAnti.color.Set(1.0f, 0.0f, 1.0f);
	wallAnti.SetPos(-51, 15, 295);
	wallAnti.Render();
	///

	Cube wall25(10, 2, 100);
	wall25.color.Set(0.6f, 0.2f, 1.0f);
	wall25.SetPos(-35, 10, 395);
	wall25.Render();

	Cube wall26(80, 2, 10);
	wall26.color.Set(0.6f, 0.2f, 1.0f);
	wall26.SetPos(0, 10, 440);
	wall26.Render();

	Cube wall27(10, 2, 100);
	wall27.color.Set(0.6f, 0.2f, 1.0f);
	wall27.SetPos(40, 10, 485);
	wall27.Render();

	Cube wall28(10, 2, 110);
	wall28.color.Set(0.6f, 0.2f, 1.0f);
	wall28.SetPos(40, 10, 620);
	wall28.Render();

	Cube wall29(70, 2, 10);
	wall29.color.Set(0.6f, 0.2f, 1.0f);
	wall29.SetPos(10, 10, 675);
	wall29.Render();

	Cube wall30(50, 2, 10);
	wall30.color.Set(0.6f, 0.2f, 1.0f);
	wall30.SetPos(-70, 10, 675);
	wall30.Render();

	Cube wall31(10, 2, 70);
	wall31.color.Set(0.6f, 0.2f, 1.0f);
	wall31.SetPos(-100, 10, 645);
	wall31.Render();

	Cube wall32(40, 2, 10);
	wall32.color.Set(0.6f, 0.2f, 1.0f);
	wall32.SetPos(-100, 10, 605);
	wall32.Render();


	Cube ramp2(10, 15, 0.5);
	ramp2.color.Set(0.4f, 1.0f, 1.0f);
	ramp2.SetRotation(90 + 8, { 1,0,0 });
	ramp2.SetPos(-100, 11.8, 593);
	ramp2.Render();

	Cube wall33(10, 2, 90);
	wall33.color.Set(0.6f, 0.2f, 1.0f);
	wall33.SetPos(-125, 10, 565);
	wall33.Render();

	Cube wall34(10, 2, 90);
	wall34.color.Set(0.6f, 0.2f, 1.0f);
	wall34.SetPos(-75, 10, 565);
	wall34.Render();

	Cube wall35(40, 2, 10);
	wall35.color.Set(0.6f, 0.2f, 1.0f);
	wall35.SetPos(-100, 10, 525);
	wall35.Render();

	Cube wall36(10, 2, 50);
	wall36.color.Set(0.6f, 0.2f, 1.0f);
	wall36.SetPos(-100, 10, 495);
	wall36.Render();

	///parkour

	Cube wall37(20, 2, 30);
	wall37.color.Set(0.6f, 0.2f, 1.0f);
	wall37.SetPos(-100, 10, 430);
	wall37.Render();

	Cube wall38(20, 2, 35);
	wall38.color.Set(0.6f, 0.2f, 1.0f);
	wall38.SetPos(-100, 10, 375);
	wall38.Render();

	//Cube wall39(20, 2, 20);
	//wall39.color.Set(0.6f, 0.2f, 1.0f);
	//wall39.SetPos(-100, 10, 360);
	//wall39.Render();

	////

	Cube wall40(20, 2, 30);
	wall40.color.Set(0.6f, 0.2f, 1.0f);
	wall40.SetPos(-100, 10, 325);
	wall40.Render();

	Cube wall41(60, 2, 80);
	wall41.color.Set(0.6f, 0.2f, 1.0f);
	wall41.SetPos(-100, 10, 270);
	wall41.Render();

	////pivots
	Cube pivot1(5, 20, 5);
	pivot1.color.Set(0.0f, 1.0f, 0.0f);
	pivot1.SetPos(-100, 20, 280);
	pivot1.Render();

	Cube pivot2(5, 20, 5);
	pivot2.color.Set(0.0f, 1.0f, 0.0f);
	pivot2.SetPos(-110, 20, 270);
	pivot2.Render();

	Cube pivot3(5, 20, 5);
	pivot3.color.Set(0.0f, 1.0f, 0.0f);
	pivot3.SetPos(-90, 20, 295);
	pivot3.Render();

	Cube pivot4(5, 20, 5);
	pivot4.color.Set(0.0f, 1.0f, 0.0f);
	pivot4.SetPos(-115, 20, 250);
	pivot4.Render();

	Cube pivot5(5, 20, 5);
	pivot5.color.Set(0.0f, 1.0f, 0.0f);
	pivot5.SetPos(-85, 20, 260);
	pivot5.Render();

	Cube pivot6(5, 20, 5);
	pivot6.color.Set(0.0f, 1.0f, 0.0f);
	pivot6.SetPos(-120, 20, 295);
	pivot6.Render();

	Cube pivot7(5, 20, 5);
	pivot7.color.Set(0.0f, 1.0f, 0.0f);
	pivot7.SetPos(-80, 20, 245);
	pivot7.Render();

	Cube pivot8(5, 20, 5);
	pivot8.color.Set(0.0f, 1.0f, 0.0f);
	pivot8.SetPos(-110, 20, 240);
	pivot8.Render();

	Cube pivot9(5, 20, 5);
	pivot9.color.Set(0.0f, 1.0f, 0.0f);
	pivot9.SetPos(-115, 20, 285);
	pivot9.Render();

	Cube pivot10(5, 20, 5);
	pivot10.color.Set(0.0f, 1.0f, 0.0f);
	pivot10.SetPos(-90, 20, 270);
	pivot10.Render();

	Cube pivot11(5, 20, 5);
	pivot11.color.Set(0.0f, 1.0f, 0.0f);
	pivot11.SetPos(-88, 20, 250);
	pivot11.Render();


	Cube wall42(10, 2, 50);
	wall42.color.Set(0.6f, 0.2f, 1.0f);
	wall42.SetPos(-120, 10, 205);
	wall42.Render();


	Cube ramp3(30, 60, 1);
	ramp3.color.Set(0.4f, 1.0f, 1.0f);
	ramp3.SetRotation(90 - 10, { 1,0,0 });
	ramp3.SetPos(-120, 5, 150);
	ramp3.Render();

	Cube wall43(2, 30, 230);
	wall43.color.Set(1.0f, 0.0f, 1.0f);
	wall43.SetPos(-105, 0, 65);
	wall43.Render();

	Cube wall44(2, 30, 280);
	wall44.color.Set(1.0f, 0.0f, 1.0f);
	wall44.SetPos(-135, 0, 40);
	wall44.Render();

	Cube wall45(90, 30, 2);
	wall45.color.Set(1.0f, 0.0f, 1.0f);
	wall45.SetPos(-60, 0, -50);
	wall45.Render();

	Cube wall46(150, 30, 2);
	wall46.color.Set(1.0f, 0.0f, 1.0f);
	wall46.SetPos(-60, 0, -95);
	wall46.Render();

	Cube wall47(2, 30, 30);
	wall47.color.Set(1.0f, 0.0f, 1.0f);
	wall47.SetPos(-15, 0, -35);
	wall47.Render();

	Cube wall48(2, 30, 80);
	wall48.color.Set(1.0f, 0.0f, 1.0f);
	wall48.SetPos(15, 0, -60);
	wall48.Render();




}
