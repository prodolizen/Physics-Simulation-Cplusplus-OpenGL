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
	_physics_object_ball1 = new DynamicObject();
	_physics_object_ball2 = new DynamicObject();
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
	_level->SetScale(2.0f, 1.0f, 2.0f);


	// Create the material for the game object- level arrow
	radiusArrow = 0.3f;
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
	_physics_object_arrow->SetPosition(glm::vec3(0.0f, radiusArrow, 0.0f));
	//_physics_object->SetScale(radiusArrow, radiusArrow, radiusArrow);			//comment out when kinematic obj
	//Set initial velocity if using phyics object									//comment out when kinematic obj
	//_v_c = glm::vec3(0.0f, 2.0f, 0.0f);											//comment out when kinematic obj
	accelerationArrow = 5.0f; //acc robber
	//for kinematic..																					//UNCOMMENT when kinematic obj

	float angle = 35.8f;
	angle = glm::radians(angle);																		//UNCOMMENT when kinematic obj
	float vel_magnitude = 25.0f;
	vel.x = vel_magnitude * cos(angle);
	vel.y = vel_magnitude * sin(angle);
	vel.z = 0.0f;
	//UNCOMMENT when kinematic obj
	_physics_object_arrow->SetScale(glm::vec3(radiusArrow, radiusArrow, radiusArrow));						//UNCOMMENT when kinematic obj
	_physics_object_arrow->SetVelocity(glm::vec3(vel.x, vel.y, vel.z));											//UNCOMMENT when kinematic obj
	//_physics_object_arrow->SetAcceleration(glm::vec3(accelX, accelY, accelZ));								//UNCOMMENT when kinematic obj
	_physics_object_arrow->SetAcceleration(glm::vec3(0.0f, -9.8f, 0.0f));
	

	//2nd ball apple
	radiusApple = 0.3f;
	// Create the material for the game object- level
	Material *objectMaterial2 = new Material();
	// Shaders are now in files
	objectMaterial2->LoadShaders("assets/shaders/VertShader.txt", "assets/shaders/FragShader.txt");
	// You can set some simple material properties, these values are passed to the shader
	// This colour modulates the texture colour
	objectMaterial2->SetDiffuseColour(glm::vec3(0.1, 0.8, 0.1));
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
	//_physics_object2->SetScale(radiusApple, radiusApple, radiusApple);					//comment out when kinematic obj
	////Set initial velocity																	//comment out when kinematic obj
	//_v_c2 = glm::vec3(0.0f, 0.0f, 0.0f);													//comment out when kinematic obj
	//accelerationApple = 0.1f; // acceleration of cop 

 // //for kinematic..																		//UNCOMMENT when kinematic obj
	//_physics_object_apple->SetScale(glm::vec3(radiusApple, radiusApple, radiusApple));		//UNCOMMENT when kinematic obj
	//_physics_object_apple->SetVelocity(glm::vec3(0.0f, 0.0f, 0.0f));								//UNCOMMENT when kinematic obj
	//_physics_object_apple->SetAcceleration(glm::vec3(0.0f,accelerationApple,0.0f));		//UNCOMMENT when kinematic obj

	//dynamic stuff 
	_physics_object_apple->SetMesh(modelMesh2);
	_physics_object_apple->SetPosition(glm::vec3(7.0f, 5.0f, 0.0f));
	_physics_object_apple->SetVelocity(glm::vec3(0.0f, 0.0f, 0.0f));
	_physics_object_apple->SetMass(3.0f);
	_physics_object_apple->SetScale(glm::vec3(radiusApple, radiusApple, radiusApple));
	_physics_object_apple->SetBoundingRadius(0.3f);

	//lab 7 / ball1
	_physics_object_ball1->SetMesh(modelMesh);
	_physics_object_ball1->SetPosition(glm::vec3(0.0f, 5.0f, 0.0f));
	_physics_object_ball1->SetMass(3.0f);
	_physics_object_ball1->SetBoundingRadius(0.3f);
	_physics_object_ball1->SetScale(glm::vec3(0.3f, 0.3f, 0.3f));

	Material* objectMaterial4 = new Material();
	objectMaterial4->LoadShaders("assets/shaders/VertShader.txt", "assets/shaders/FragShader.txt");
	objectMaterial4->SetDiffuseColour(glm::vec3(0.0, 1.0, 1.0));
	objectMaterial4->SetTexture("assets/textures/default.bmp");
	objectMaterial4->SetLightPosition(_lightPosition);

	_physics_object_ball1->SetMaterial(objectMaterial4);
	_physics_object_ball1->SetVelocity(glm::vec3(0.0f, 0.0f, 0.0f));
	
	//ball 2
	_physics_object_ball2->SetMesh(modelMesh);
	_physics_object_ball2->SetPosition(glm::vec3(0.0f, 1.3f, 0.0f));
	_physics_object_ball2->SetMass(30.0f);
	_physics_object_ball2->SetBoundingRadius(0.3f);
	_physics_object_ball2->SetScale(glm::vec3(0.3f, 0.3f, 0.3f));

	Material* objectMaterial3 = new Material();
	objectMaterial3->LoadShaders("assets/shaders/VertShader.txt", "assets/shaders/FragShader.txt");
	objectMaterial3->SetDiffuseColour(glm::vec3(1.0, 0.0, 1.0));
	objectMaterial3->SetTexture("assets/textures/default.bmp");
	objectMaterial3->SetLightPosition(_lightPosition);

	_physics_object_ball2->SetMaterial(objectMaterial3);
	_physics_object_ball2->SetVelocity(glm::vec3(0.0f, 0.0f, 0.0f));
}

Scene::~Scene()
{
	// You should neatly clean everything up here
	delete _physics_object_arrow;
	delete _physics_object_apple;
	delete _level;
	delete _camera;
	delete _physics_object_ball1;
	delete _physics_object_ball2;
}

void Scene::Update(float deltaTs, Input* input)
{
	//std::cout << "Ball 1 radius " << radiusArrow << "ball 2 radius " << radiusApple << endl;
	// Update the game object (this is currently hard-coded motion)
	if (input->cmd_x)
	{
		_simulation_start = true;
	}
	if (_simulation_start == true)
	{

		////update velocity of ball so it doesnt fall at const speed												//comment out when kinematic obj
		//_v_c.y = _v_c.y + (accelerationArrow * deltaTs);																	//comment out when kinematic obj
		////calculate how far it moves																				//comment out when kinematic obj
		//float displacementY = (_v_c.y * deltaTs) + 0.5 * accelerationArrow * pow(deltaTs, 2);								//comment out when kinematic obj
		//float displacementX = displacementY / tan(glm::radians(63.0f)); //give vector X component using TOA		//comment out when kinematic obj
		//float displacementZ = displacementX * tan(glm::radians(0.0f)); //give vector Z component of displacement	//comment out when kinematic obj
		
		
		//_physics_object_arrow->UpdateKinematics(deltaTs);														//UNCOMMENT when kinematic obj
			//pos += glm::vec3(displacementX, displacementY, displacementZ); //moves ball							//comment out when kinematic obj
			//_physics_object->SetPosition(pos);																	//comment out when kinematic obj
		
		_physics_object_arrow->StartSimulation(_simulation_start);
		_physics_object_ball1->StartSimulation(_simulation_start);
		_physics_object_ball2->StartSimulation(_simulation_start);
		//ball 2 put in Update function kinematics cpp, 1 set kinematic eq, keep collision detection here. basically make generic kinematic equation and change values for each ball
		//update velocity of ball so it doesnt fall at const speed
		//_v_c2.y = _v_c2.y + (accelerationApple * deltaTs); //*
		//calculate how far it moves
		//float displacementApple = (_v_c2.y * deltaTs) + 0.5 * accelerationApple * pow(deltaTs, 2); //*

		// Get the positions of the two balls
		glm::vec3 posArrow = _physics_object_arrow->GetPosition();
		glm::vec3 posApple = _physics_object_apple->GetPosition();
		//_physics_object_apple->StartSimulation(_simulation_start);

		//if(arrowCanShoot == false) //applies the downwards displacement of the apple to the arrow once they collide so they fall together
		//{
			//posArrow += glm::vec3(0.0f, -displacementApple, 0.0f); //moves ball
			//_physics_object_arrow->SetPosition(posArrow);
			//_physics_object_arrow->SetVelocity(glm::vec3(0,0,0));								//UNCOMMENT when kinematic obj
		//	//_physics_object_arrow->SetAcceleration(glm::vec3(0, accelerationApple, 0));					//UNCOMMENT when kinematic obj
		//}

	//	 Calculate the distance between the two balls' center points   original coll detect
		//float distance = glm::distance(posArrow+radiusArrow, posApple+radiusApple);   
		float distance = glm::length(posApple - posArrow);
		 //Calculate the sum of the two balls' radii
		//float sumRadii = radiusArrow + radiusApple;
		//std::cout << distance - sumRadii << endl;
		// If the distance between the balls is less than or equal to the sum of their radii, then they have collided
		if (distance <= 0.6f)
		{
			std::cout << "hit" << endl;
			arrowHit = true;
			arrowCanShoot = false;
		}

		if (arrowHit == true)
		{
			//posApple += glm::vec3(0.0, -displacementApple, 0.0); //moves ball
			//_physics_object_apple->SetPosition(posApple);
			_physics_object_apple->StartSimulation(_simulation_start);
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
	 
		//// Lab 2: Exercise 4: compute collision with the ground
		//if (posArrow.y < radiusArrow)
		//{
		//	posArrow.y = radiusArrow;
		//	_physics_object_arrow->SetPosition(posArrow);
		//}
		//if (posApple.y < radiusApple)
		//{
		//	posApple.y = radiusApple;
		//	_physics_object_apple->SetPosition(posApple);
		//}
	}
	_physics_object_arrow->Update(deltaTs);
	_physics_object_apple->Update(deltaTs);
	_level->Update(deltaTs);
	_camera->Update(input);
	_physics_object_ball1->Update(deltaTs);
	_physics_object_ball2->Update(deltaTs);

	_viewMatrix = _camera->GetView();
	_projMatrix = _camera->GetProj();
	
														
}

void Scene::Draw()
{
	// Draw objects, giving the camera's position and projection
	_physics_object_arrow->Draw(_viewMatrix, _projMatrix);
	_physics_object_apple->Draw(_viewMatrix, _projMatrix);
	_level->Draw(_viewMatrix, _projMatrix);
	_physics_object_ball1->Draw(_viewMatrix, _projMatrix);
	_physics_object_ball2->Draw(_viewMatrix, _projMatrix);

}


