#include "DynamicObject.h"
#include <GLM/gtc/type_ptr.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtx/rotate_vector.hpp>
#include "Utility.h"


DynamicObject::DynamicObject()
{
	//set values for physics params
	_force = glm::vec3(0.0f, 0.0f, 0.0f);
	_velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	_mass = 0.0f;
	_bRadius = 0.0f;
	//_other_object = new DynamicObject();

	//set values for params
	_scale = glm::vec3(1.0f, 1.0f, 1.0f);
	_start = false;
}

DynamicObject::~DynamicObject()
{

}

void DynamicObject::AddCollisionObject(DynamicObject* obj)
{
	if (!obj)
	{
		return;
	}

	_other_object = obj;

}

void DynamicObject::Update(float deltaTs)
{
	if (_start == true)
	{
		//1: clear all forces on object
		ClearForces();
		//2: compute forces that act on object (only gravity at the moment)
		glm::vec3 gravityForce = glm::vec3(0.0f, -9.8 * _mass, 0.0f);
		//add force to total force
		AddForce(gravityForce);

		////3: compute collisions and responses
		//glm::vec3 bounceForce;
		//glm::vec3 n = glm::vec3(0.0f, 1.0f, 0.0f); //plane normal
		//glm::vec3 c0 = _position; //point on plane
		//glm::vec3 q = glm::vec3(0.0f, 0.0f, 0.0f); //plane vel
		//glm::vec3 c1 = _position + _velocity * deltaTs;
		//glm::vec3 ci(0);
		//float r = GetBoundingRadius();
		////float d = PFG::DistanceToPlane(n, c0, q);

		//bool collision = PFG::MovingSphereToPlaneCollision(n, c0, c1, q, r, ci);
		//if (collision)
		//{
		//	_position = glm::vec3(c0.x, r, c0.z);
		//	//_position = ci;
		//	//_position = ci + glm::vec3(0.0f, r, 0.0f);

		//	glm::vec3 contact_force = glm::vec3(0.0f, 9.8f * _mass, 0.0f);
		//	AddForce(contact_force);
		//	glm::vec3 bounceForce = glm::vec3(0.0f, 150.0f, 0.0f);
		//	AddForce(bounceForce);
		//}
		//4: euler integration
		ComputeCollisionForces(deltaTs);
		Euler(deltaTs);
		//Verlet(deltaTs);
		//RungeKutta2(deltaTs);
		//RungeKutta4(deltaTs);
	}

	//update model matrix with current pos, orientation and scale
	UpdateModelMatrix();
}

void DynamicObject::Euler(float deltaTs)
{
	//this function is the numerical integration of the dynamic physics computation
	float oneOverMass = 1 / _mass;
	//compute the current velocity based on previous velocity
	_velocity += (_force * oneOverMass);
	//compute the current pos based on prev pos
	_position += _velocity * deltaTs;
}
//lab7
void DynamicObject::ComputeCollisionForces(float deltaTs)
{
	// a sphere to plane collision detection
	float elasticity1 = 0.5f;
	glm::vec3 n1 = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 c0 = _position;
	glm::vec3 q = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 c1 = _position + _velocity * deltaTs;
	glm::vec3 ci(0);
	float r = GetBoundingRadius();
	
	bool collision = PFG::MovingSphereToPlaneCollision(n1, c0, c1, q, r, ci);
	if (collision)
	{
		
		glm::vec3 plane_velocity = glm::vec3(0.0f, 0.0f, 0.0f);
		float collision_impulse = -(1 + elasticity1) * glm::dot(_velocity - plane_velocity, n1) / (1.0f / _mass);
		glm::vec3 collision_impulse_vector = collision_impulse * n1;
		_velocity += collision_impulse_vector / _mass;
		glm::vec3 contact_force = glm::vec3(0.0f, 9.8f * _mass, 0.0f);
		AddForce(contact_force);
	}

	float elasticity = 0.9f;
    glm::vec3 position_distance = -_other_object->GetPosition() + _position;
	std::cout << "pos " << _position.y << "other object position " << _other_object->GetPosition().y << std::endl;
	glm::vec3 n = glm::normalize(position_distance);
	float r1 = _bRadius;
	float r2 = _other_object->GetBoundingRadius();
	glm::vec3 object2_velocity = _other_object->GetVelocity();
	float distance = glm::length(position_distance);
	//std::cout << "position_distance " << position_distance.y << "distance " << distance << std::endl;
	if (distance <= 0.6f)
	{
		std::cout << "collision";
		float one_over_mass1 = 1.0f / _mass;
		float one_over_mass2 = 1.0f / _other_object->GetMass();
		float collision_impulse = -(1 + elasticity) * glm::dot((_velocity - object2_velocity), n) / (one_over_mass1 + one_over_mass2);
		glm::vec3 collision_impulse_vector = collision_impulse * n;;
		_velocity += collision_impulse_vector / _mass;
		//glm::vec3 contact_force = glm::vec3(0.0f, 9.8f * _mass, 0.0f);
		//AddForce(contact_force);

		object2_velocity -= collision_impulse_vector / _other_object->GetMass();
		_other_object->SetVelocity(object2_velocity);
		
		glm::vec3 contact_force2 = glm::vec3(0.0f, 9.8f * _other_object->GetMass(), 0.0f);
		_other_object->AddForce(contact_force2);
	}
}

void DynamicObject::UpdateModelMatrix()
{
	//update the model matrix with current pos, orientation and scale
	_modelMatrix = glm::translate(glm::mat4(1), _position);
	_modelMatrix = glm::scale(_modelMatrix, _scale);
	_invModelMatrix = glm::inverse(_modelMatrix);
}

void DynamicObject::RungeKutta2(float deltaTs)
{
	glm::vec3 force;
	glm::vec3 acceleration;
	glm::vec3 k0;
	glm::vec3 k1;
	
	//evaluate when at t0
	force = _force;
	acceleration = force / _mass;
	k0 = deltaTs * acceleration;
	
	//evaluate once at t0 + deltaT/2.0 using half of k0
	force = _force + k0 / 2.0f;
	acceleration = force / _mass;
	k1 = deltaTs * acceleration;

	//evaluate once at t0 + deltaT using k1
	_velocity += k1;
	_position += _velocity * deltaTs;
}

void DynamicObject::RungeKutta4(float deltaTs)
{
	glm::vec3 force;
	glm::vec3 acceleration;
	glm::vec3 k0;
	glm::vec3 k1; 
	glm::vec3 k2;
	glm::vec3 k3;

	//evaluate once at t0 to find k0
	force = _force;
	acceleration = force / _mass;
	k0 = deltaTs * acceleration;

	//evaluate twice at t0 + deltaT/2 using half of k0 and half of k1
	force = _force + k0 / 2.0f;
	acceleration = force / _mass;
	k1 = deltaTs * acceleration;
	
	force = _force + k1 / 2.0f;
	acceleration = force / _mass;
	k3 = deltaTs * acceleration;

	//evaluate once at t0 + deltaT using k2
	force = _force + k2;
	acceleration = force / _mass;
	k3 = deltaTs * acceleration;

	//evaluate at t0 + deltaT using weighted sum of k0, k1, k2 and k3
	_velocity += (k0 + 2.0f * k1 + 2.0f * k2 + k3) / 6.0f;
	//update pos
	_position += _velocity * deltaTs;
}

void DynamicObject::Verlet(float deltaTs)
{
	glm::vec3 acceleration = _force / _mass;
	_previous_position = _position;
	_position = -_previous_position + 2.0f * _position + acceleration * deltaTs * deltaTs;
	_velocity = (_position - _previous_position) / (2.0f * deltaTs);
	_velocity += acceleration * deltaTs;
}