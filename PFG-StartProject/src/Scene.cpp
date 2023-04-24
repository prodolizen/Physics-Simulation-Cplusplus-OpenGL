#include "Scene.h"
/*! \brief Brief description.
*  Scene class is a container for loading all the game objects in your simulation or your game.
*
*/
Scene::Scene()
{
	// Set up your scene here......
	// Set a camera
	_camera = new Camera();
	// Don't start simulation yet
	_simulation_start = false;

	// Position of the light, in world-space
	_lightPosition = glm::vec3(10, 10, 0);

	//create a kinematics object
	_physics_object_arrow = new KinematicsObject();
	//_physics_object_apple = new KinematicsObject();
	_physics_object_apple = new DynamicObject();
	// Create a game object
	//_physics_object = new GameObject();
	//_physics_object2 = new GameObject();
	
	// Create a game level object
	_level = new GameObject();
	
	// Create the material for the game object- level
	Material *modelMaterial = new Material();
	// Shaders are now in files
	modelMaterial->LoadShaders("assets/shaders/VertShader.txt", "assets/shaders/FragShader.txt");
	// You can set some simple material properties, these values are passed to the shader
	// This colour modulates the texture colour
	modelMaterial->SetDiffuseColour(glm::vec3(0.8, 0.8, 0.8));
	// The material currently supports one texture
	// This is multiplied by all the light components (ambient, diffuse, specular)
	// Note that the diffuse colour set with the line above will be multiplied by the texture colour
	// If you want just the texture colour, use modelMaterial->SetDiffuseColour( glm::vec3(1,1,1) );
	modelMaterial->SetTexture("assets/textures/diffuse.bmp");
	// Need to tell the material the light's position
	// If you change the light's position you need to call this again
	modelMaterial->SetLightPosition(_lightPosition);
	// Tell the level object to use this material
	_level->SetMaterial(modelMaterial);

	// The mesh is the geometry for the floor
	Mesh *groundMesh = new Mesh();
	// Load from OBJ file. This must have triangulated geometry
	groundMesh->LoadOBJ("assets/models/woodfloor.obj");
	// Tell the game object to use this mesh
	_level->SetMesh(groundMesh);
	_level->SetPosition(0.0f, 0.0f, 0.0f);
	_level->SetRotation(3.141590f, 0.0f, 0.0f);


	// Create the material for the game object- level arrow
	radius_ball1 = 0.5f;
	Material *objectMaterial = new Material();
	// Shaders are now in files
	objectMaterial->LoadShaders("assets/shaders/VertShader.txt", "assets/shaders/FragShader.txt");
	// You can set some simple material properties, these values are passed to the shader
	// This colour modulates the texture colour
	objectMaterial->SetDiffuseColour(glm::vec3(0.8, 0.1, 0.1));
	// The material currently supports one texture
	// This is multiplied by all the light components (ambient, diffuse, specular)
	// Note that the diffuse colour set with the line above will be multiplied by the texture colour
	// If you want just the texture colour, use modelMaterial->SetDiffuseColour( glm::vec3(1,1,1) );
	objectMaterial->SetTexture("assets/textures/default.bmp");
	// Need to tell the material the light's position
	// If you change the light's position you need to call this again
	objectMaterial->SetLightPosition(_lightPosition);
	// Tell the level object to use this material
	_physics_object_arrow->SetMaterial(objectMaterial);

	// Set the geometry for the object
	Mesh *modelMesh = new Mesh();
	// Load from OBJ file. This must have triangulated geometry
	modelMesh->LoadOBJ("assets/models/sphere.obj");
	// Tell the game object to use this mesh
	_physics_object_arrow->SetMesh(modelMesh);
	_physics_object_arrow->SetPosition(glm::vec3(0.0f, radius_ball1, 0.0f));
	//_physics_object->SetScale(radius_ball1, radius_ball1, radius_ball1);			//comment out when kinematic obj
	//Set initial velocity if using phyics object									//comment out when kinematic obj
	//_v_c = glm::vec3(0.0f, 2.0f, 0.0f);											//comment out when kinematic obj
	accRobber = 5.0f; //acc robber
	//for kinematic..																					//UNCOMMENT when kinematic obj
	float accelY = accRobber;																			//UNCOMMENT when kinematic obj
	float accelX = accelY / tan(glm::radians(75.0f)); //give vector X component using TOA				//UNCOMMENT when kinematic obj
	float accelZ = accelX * tan(glm::radians(-10.0f)); //give vector Z component of displacement		//UNCOMMENT when kinematic obj
	_physics_object_arrow->SetScale(glm::vec3(radius_ball1, radius_ball1, radius_ball1));						//UNCOMMENT when kinematic obj
	_physics_object_arrow->SetVelocity(glm::vec3(0.0f, 2.0f, 0.0f));											//UNCOMMENT when kinematic obj
	_physics_object_arrow->SetAcceleration(glm::vec3(accelX, accelY, accelZ));								//UNCOMMENT when kinematic obj


	//2nd ball apple
	radius_ball2 = 0.3f;
	// Create the material for the game object- level
	Material *objectMaterial2 = new Material();
	// Shaders are now in files
	objectMaterial2->LoadShaders("assets/shaders/VertShader.txt", "assets/shaders/FragShader.txt");
	// You can set some simple material properties, these values are passed to the shader
	// This colour modulates the texture colour
	objectMaterial2->SetDiffuseColour(glm::vec3(0.8, 0.1, 0.1));
	// The material currently supports one texture
	// This is multiplied by all the light components (ambient, diffuse, specular)
	// Note that the diffuse colour set with the line above will be multiplied by the texture colour
	// If you want just the texture colour, use modelMaterial->SetDiffuseColour( glm::vec3(1,1,1) );
	objectMaterial2->SetTexture("assets/textures/default.bmp");
	// Need to tell the material the light's position
	// If you change the light's position you need to call this again
	objectMaterial2->SetLightPosition(_lightPosition);
	// Tell the level object to use this material
	_physics_object_apple->SetMaterial(objectMaterial2);

	// Set the geometry for the object | stationary ball 
	Mesh *modelMesh2 = new Mesh();
	// Load from OBJ file. This must have triangulated geometry
	modelMesh2->LoadOBJ("assets/models/sphere.obj");
	// Tell the game object to use this mesh
	//_physics_object_apple->SetMesh(modelMesh2);
	//_physics_object_apple->SetPosition(glm::vec3(2.0f, 10.0f, 0.0f));
	//_physics_object2->SetScale(radius_ball2, radius_ball2, radius_ball2);					//comment out when kinematic obj
	////Set initial velocity																	//comment out when kinematic obj
	//_v_c2 = glm::vec3(0.0f, 0.0f, 0.0f);													//comment out when kinematic obj
	accCop = 0.1f; // acceleration of cop 

 // //for kinematic..																		//UNCOMMENT when kinematic obj
	//_physics_object_apple->SetScale(glm::vec3(radius_ball2, radius_ball2, radius_ball2));		//UNCOMMENT when kinematic obj
	//_physics_object_apple->SetVelocity(glm::vec3(0.0f, 0.0f, 0.0f));								//UNCOMMENT when kinematic obj
	//_physics_object_apple->SetAcceleration(glm::vec3(0.0f,accCop,0.0f));		//UNCOMMENT when kinematic obj

	//dynamic stuff 
	_physics_object_apple->SetMesh(modelMesh2);
	_physics_object_apple->SetPosition(glm::vec3(2.0f, 10.0f, 0.0f));
	_physics_object_apple->SetVelocity(glm::vec3(0.0f, 0.0f, 0.0f));
	_physics_object_apple->SetMass(2.0f);
	_physics_object_apple->SetScale(glm::vec3(0.3f, 0.3f, 0.3f));
	_physics_object_apple->SetBoundingRadius(0.3f);
}

Scene::~Scene()
{
	// You should neatly clean everything up here
	delete _physics_object_arrow;
	delete _physics_object_apple;
	delete _level;
	delete _camera;
}

void Scene::Update(float deltaTs, Input* input)
{
	std::cout << "Ball 1 radius " << radius_ball1 << "ball 2 radius " << radius_ball2 << endl;
	// Update the game object (this is currently hard-coded motion)
	if (input->cmd_x)
	{
		_simulation_start = true;
	}
	if (_simulation_start == true)
	{

		////update velocity of ball so it doesnt fall at const speed												//comment out when kinematic obj
		//_v_c.y = _v_c.y + (accRobber * deltaTs);																	//comment out when kinematic obj
		////calculate how far it moves																				//comment out when kinematic obj
		//float displacementY = (_v_c.y * deltaTs) + 0.5 * accRobber * pow(deltaTs, 2);								//comment out when kinematic obj
		//float displacementX = displacementY / tan(glm::radians(63.0f)); //give vector X component using TOA		//comment out when kinematic obj
		//float displacementZ = displacementX * tan(glm::radians(0.0f)); //give vector Z component of displacement	//comment out when kinematic obj
		
		if (arrowCanShoot == true)
		{
			_physics_object_arrow->UpdateKinematics(deltaTs);														//UNCOMMENT when kinematic obj
			//pos += glm::vec3(displacementX, displacementY, displacementZ); //moves ball							//comment out when kinematic obj
			//_physics_object->SetPosition(pos);																	//comment out when kinematic obj
		}

		//ball 2 put in Update function kinematics cpp, 1 set kinematic eq, keep collision detection here. basically make generic kinematic equation and change values for each ball
		//update velocity of ball so it doesnt fall at const speed
		_v_c2.y = _v_c2.y + (accCop * deltaTs); //*
		//calculate how far it moves
		float displacementApple = (_v_c2.y * deltaTs) + 0.5 * accCop * pow(deltaTs, 2); //*

		// Get the positions of the two balls
		glm::vec3 ball1Pos = _physics_object_arrow->GetPosition();
		glm::vec3 ball2Pos = _physics_object_apple->GetPosition();

		if(arrowCanShoot == false) //applies the downwards displacement of the apple to the arrow once they collide so they fall together
		{
			ball1Pos += glm::vec3(0.0f, -displacementApple, 0.0f); //moves ball
			_physics_object_arrow->SetPosition(ball1Pos);
			_physics_object_arrow->SetVelocity(glm::vec3(0,0,0));								//UNCOMMENT when kinematic obj
			_physics_object_arrow->SetAcceleration(glm::vec3(0, accCop, 0));					//UNCOMMENT when kinematic obj
		}

		// Calculate the distance between the two balls' center points
		float distance = glm::distance(ball1Pos+radius_ball1, ball2Pos+radius_ball2);   

		// Calculate the sum of the two balls' radii
		float sumRadii = radius_ball1 + radius_ball2;
		//std::cout << distance - sumRadii << endl;
		// If the distance between the balls is less than or equal to the sum of their radii, then they have collided
		if (distance <= sumRadii)
		{
			std::cout << "hit" << endl;
			arrowHit = true;
			arrowCanShoot = false;
		}

	/*	float distanceLeft = glm::distance(ball1Pos + radius_ball1, ball2Pos - radius_ball2);
		float distanceRight = glm::distance(ball1Pos - radius_ball1, ball2Pos + radius_ball2);

		if (distanceLeft <= sumRadii)
		{
			std::cout << "left hit" << endl;
			arrowHit = true;
			arrowCanShoot = false;
		}
		if(distanceRight <= sumRadii)
		{
			std::cout << "right hit" << endl;
			arrowHit = true;
			arrowCanShoot = false;
		}*/


		if (arrowHit == true)
		{
			ball2Pos += glm::vec3(0.0, -displacementApple, 0.0); //moves ball
			_physics_object_apple->SetPosition(ball2Pos);
		}

		
		

		// Lab2: Use kinematics equations to compute kinematics motion
		// We compute the motion of the object with a series of time steps. 
		// For each of the time steps, following procedures should be carried out
		//     1. Get the current position of the object
		//     2. Given the initial quantities, Compute the velocity of the current time step 
		//     2. Given the initial quantities, Compute the velocity of the current time step 
		//     3. Use the kinematics equations to compute the x, y, and x position at the current time step
		//     4. Assign the current velocity to the initial velocity for the next time step 
		//     5. Set the current position for the object
		//     6  Do collision detections and responses
		//     7 Update the model matrix for graphics engine to draw 
		//   
	 
		// Lab 2: Exercise 4: compute collision with the ground
		if (ball1Pos.y < radius_ball1)
		{
			ball1Pos.y = radius_ball1;
			_physics_object_arrow->SetPosition(ball1Pos);
		}
		if (ball2Pos.y < radius_ball2)
		{
			ball2Pos.y = radius_ball2;
			_physics_object_apple->SetPosition(ball2Pos);
		}
	}
	_physics_object_arrow->Update(deltaTs);
	_physics_object_apple->Update(deltaTs);
	_level->Update(deltaTs);
	_camera->Update(input);

	_viewMatrix = _camera->GetView();
	_projMatrix = _camera->GetProj();
														
}

void Scene::Draw()
{
	// Draw objects, giving the camera's position and projection
	_physics_object_arrow->Draw(_viewMatrix, _projMatrix);
	_physics_object_apple->Draw(_viewMatrix, _projMatrix);
	_level->Draw(_viewMatrix, _projMatrix);

}


