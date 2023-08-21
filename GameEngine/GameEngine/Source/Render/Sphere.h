#pragma once
#include <GLM/glm.hpp>

class Sphere
{
public:
	Sphere(glm::vec3 color, glm::vec3 origin, float radius) : color(color), origin(origin), radius(radius) {}
	inline glm::vec3& GetOrigin() { return origin; }
	inline glm::vec3& GetColor() { return color; }
	inline float& GetRadius() { return radius; }
private:
	glm::vec3 color;
	glm::vec3 origin;
	float radius;
};

