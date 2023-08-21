#pragma once
#include <GLM/glm.hpp>

class Torus
{
public:
	Torus(glm::vec3 color, glm::vec3 origin, float radiusPrimary, float radiusSecondary) : color(color), origin(origin), radiusPrimary(radiusPrimary), radiusSecondary(radiusSecondary) {}
	inline glm::vec3& GetColor() { return color; }
	inline glm::vec3& GetOrigin() { return origin; }
	inline float& GetRadiusPrimary() { return radiusPrimary; }
	inline float& GetRadiusSecondary() { return radiusSecondary; }
private:
	glm::vec3 color;
	glm::vec3 origin;
	float radiusPrimary;
	float radiusSecondary;
};