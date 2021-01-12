#include "PhysVehicle3D.h"
#include "Primitive.h"
#include "Bullet/include/btBulletDynamicsCommon.h"

// ----------------------------------------------------------------------------
VehicleInfo::~VehicleInfo()
{
	//if(wheels != NULL)
		//delete wheels;
}

// ----------------------------------------------------------------------------
PhysVehicle3D::PhysVehicle3D(btRigidBody* body, btRaycastVehicle* vehicle, const VehicleInfo& info) : PhysBody3D(body), vehicle(vehicle), info(info)
{
}

// ----------------------------------------------------------------------------
PhysVehicle3D::~PhysVehicle3D()
{
	delete vehicle;
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::Render()
{
	Cylinder wheel;

	wheel.color = Pink;

	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		wheel.radius = info.wheels[0].radius;
		wheel.height = info.wheels[0].width;

		vehicle->updateWheelTransform(i);
		vehicle->getWheelInfo(i).m_worldTransform.getOpenGLMatrix(&wheel.transform);

		wheel.Render();
	}


	//Cube chassis(info.chassis_size.x, info.chassis_size.y, info.chassis_size.z);
	//vehicle->getChassisWorldTransform().getOpenGLMatrix(&chassis.transform);
	//btQuaternion q = vehicle->getChassisWorldTransform().getRotation();
	//btVector3 offset(info.chassis_offset.x, info.chassis_offset.y, info.chassis_offset.z);
	//offset = offset.rotate(q.getAxis(), q.getAngle());
	//chassis.color = Red;
	//chassis.transform.M[12] += offset.getX();
	//chassis.transform.M[13] += offset.getY();
	//chassis.transform.M[14] += offset.getZ();


	//chassis.Render();

	if (info.new_parts >= 0)
	{
		Cube new_shapes;
		for (uint i = 0; i < info.new_parts; i++)
		{
			new_shapes.size.Set(info.new_parts_size[i].x, info.new_parts_size[i].y, info.new_parts_size[i].z);
			vehicle->getChassisWorldTransform().getOpenGLMatrix(&new_shapes.transform);

			btQuaternion q = vehicle->getChassisWorldTransform().getRotation();
			btVector3 offset(info.new_parts_offset[i].x, info.new_parts_offset[i].y, info.new_parts_offset[i].z);
			offset = offset.rotate(q.getAxis(), q.getAngle());

			new_shapes.transform.M[12] += offset.getX();
			new_shapes.transform.M[13] += offset.getY();
			new_shapes.transform.M[14] += offset.getZ();
			new_shapes.color = info.color[i];

			new_shapes.Render();
		}
	}
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::ApplyEngineForce(float force)
{
	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		if(info.wheels[i].drive == true)
		{
			vehicle->applyEngineForce(force, i);
		}
	}
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::Brake(float force)
{
	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		if(info.wheels[i].brake == true)
		{
			vehicle->setBrake(force, i);
		}
	}
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::Turn(float degrees)
{
	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		if(info.wheels[i].steering == true)
		{
			vehicle->setSteeringValue(degrees, i);
		}
	}
}

// ----------------------------------------------------------------------------
float PhysVehicle3D::GetKmh() const
{
	return vehicle->getCurrentSpeedKmHour();
}