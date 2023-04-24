#include "DynamicObject.h"
#include <GLM/gtc/type_ptr.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtx/rotate_vector.hpp>

DynamicObject::DynamicObject()
{
	//set values for physics params
	_force = glm::vec3(0.0f, 0.0f, 0.0f);
	_velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	_mass = 0.0f;
	_bRadius = 0.0f;

	//set values for params
	_scale = glm::vec3(1.0f, 1.0f, 1.0f);
	_start = false;
}

DynamicObject::~DynamicObject()
{

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

		//3: compute collisions and responses
		if (_position.y <= 0.3f)
		{
			_position.y = 0.3f;
			glm::vec3 bounceForce = glm::vec3(0.0f, 150.0f, 0.0f);
			AddForce(bounceForce);
		}
		//4: euler integration
		Euler(deltaTs);
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