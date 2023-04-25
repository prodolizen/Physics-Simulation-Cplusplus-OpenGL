#pragma once
#ifndef _SCENE_H_
#define _SCENE_H_

#include "GameObject.h"
#include "Camera.h"
#include <cmath>
#include "KinematicsObject.h"
#include "DynamicObject.h"

/*! \brief Brief description.
*  Scene class is a container for loading all the game objects in your simulation or your game. 
*  
*/

class Scene
{
public:

	/** Scene constructor
	* Currently the scene is set up in the constructor
	* This means the object(s) are loaded, given materials and positions as well as the camera and light
	*/
	Scene();
	/** Scene distructor
	*/
	~Scene();

	/** Scene update
	* This function is called for each simulation time step to
	* update on all objects in the scene
	*/
	void Update(float deltaTs, Input* input);

	/** 
	* Call this function to get a pointer to the camera
	* 
	*/
    Camera* GetCamera() { return _camera; }

	/** Draw the scene from the camera's point of view
	*
	*/
	void Draw();

private:

	/** A physics object
	*/
	//GameObject* _physics_object;  //comment out both for kinematic
	//GameObject* _physics_object2;

	KinematicsObject* _physics_object_arrow;       //uncomment both for kinematic
	//KinematicsObject* _physics_object_apple;
	DynamicObject* _physics_object_apple;
	// Initial velocity variable of the physics object 
	//for Exercise 5: Use kinematics equations to compute free fall
	glm::vec3 _v_c; // the initial velocity

	glm::vec3 _v_c2; // the initial velocity2

	bool caughtRobber = false;
	//ball radius'
	float radiusArrow;
	float radiusApple;
	glm::vec3 vel;

	/** An example game level in the scene
	*/
	GameObject* _level; 
	/** The main camera in the scene 
	*/
	Camera* _camera; 

	/**The position for a light that lits the scene
	*/
	glm::vec3 _lightPosition; 
	/** This matrix represents the camera's position and orientation 
	*/
	glm::mat4 _viewMatrix; 
	/** This matrix is the camera's lens
	*/
	glm::mat4 _projMatrix; 
	/** A boolen variable to control the start of the simulation This matrix is the camera's lens
	*/
	bool _simulation_start;

	
	float accelerationApple = 0.0f; // acceleration of cop 
	float accelerationArrow = 0.0f; //acc robber
	bool arrowHit = false;
	bool arrowCanShoot = true;

};

#endif // !_SCENE_H_