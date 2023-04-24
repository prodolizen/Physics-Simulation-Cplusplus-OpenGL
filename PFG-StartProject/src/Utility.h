#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace PFG
{
	/*
	A signed distance 'd' from a point in space 'p'
	to a plane is calculated by a dot product of the plane's normal vector 'n'
	with the vector '(p-q)', where 'q' is any point on the plane
	*/
	float DistanceToPlane(const glm::vec3& n, const glm::vec3& p, const glm::vec3& q);

	/*
	A sphere to a plane collision detection is calculated by finding the parameter between the centre of the sphere c0
	at time step t0 and predict its movement using 'v'. Then find the position of the centre of the sphere using
	the parameter 't'. This also returns new centre point
	*/
	bool MovingSphereToPlaneCollision(const glm::vec3& n, const glm::vec3& c0, const glm::vec3& c1, const glm::vec3& q, float r, glm::vec3& ci);


	/*
	Sphere to sphere collision detection is calculated by finding the distance between the centre of the sphere c0
	and the centre of the sphere c1. This function also finds the contact point cp on the sphere
	*/
	bool SphereToSphereCollision(const glm::vec3& c0, const glm::vec3 c1, float r1, float r2, glm::vec3& cp);
}