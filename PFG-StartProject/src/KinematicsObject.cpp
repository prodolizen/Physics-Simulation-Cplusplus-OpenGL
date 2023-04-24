#include "KinematicsObject.h"

KinematicsObject::KinematicsObject()
{
	GameObject::GameObject();
}

KinematicsObject::~KinematicsObject()
{
	GameObject::~GameObject();
}

void KinematicsObject::Update(float deltaTs)
{
	
	
	GameObject::SetPosition(_position);
	GameObject::Update(deltaTs);
}

void KinematicsObject::UpdateKinematics(float deltaTs)
{
	_velocity = _velocity + (_acceleration * deltaTs);
	_position = (_velocity * deltaTs) + 0.5f * _acceleration * pow(deltaTs, 2.0f); //*
}

void KinematicsObject::UpdateModelMatrix()
{
	
}
