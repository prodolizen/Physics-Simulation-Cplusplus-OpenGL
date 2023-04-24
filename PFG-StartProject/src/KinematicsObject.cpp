#include "KinematicsObject.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

KinematicsObject::KinematicsObject()
{
	_scale = glm::vec3(3.3f, 0.3f, 0.3f);
	_start = false;
}

KinematicsObject::~KinematicsObject()
{
	
}

void KinematicsObject::Update(float deltaTs)
{
	/*if (_start == true)
	{
		_velocity = _velocity + (_acceleration * deltaTs);
		_position = (_velocity * deltaTs) + 0.5f * _acceleration * pow(deltaTs, 2.0f);
		GameObject::SetPosition(_position);
		GameObject::Update(deltaTs);
	}
	*/
	if (_start == true)
	{

		glm::vec3 vel;
		_position.x += _velocity.x * deltaTs + 0.5f * (_acceleration.x) * deltaTs * deltaTs;
		_position.y += _velocity.y * deltaTs + 0.5f * (_acceleration.y) * deltaTs * deltaTs;
		_position.z += _velocity.z * deltaTs + 0.5f * (_acceleration.z) * deltaTs * deltaTs;
		vel.x = _velocity.x + (_acceleration.x) * deltaTs;
		vel.y = _velocity.y + (_acceleration.y) * deltaTs;
		vel.z = _velocity.z + (_acceleration.z) * deltaTs;
		_velocity = vel; //update inital velocity

		//collision detection
		if (_position.y <= 0.3f)
		{
			_position.y = 0.3f;
		}

	}
	UpdateModelMatrix();
}

void KinematicsObject::UpdateKinematics(float deltaTs)
{
	 
}

void KinematicsObject::UpdateModelMatrix()
{
	_modelMatrix = glm::translate(glm::mat4(1), _position);
	_modelMatrix = glm::scale(_modelMatrix, _scale);
}
