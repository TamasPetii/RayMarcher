#pragma once
#include "Shape.h"

class Sphere : public Shape
{
public:
	Sphere(glm::vec3 color, glm::vec3 origin, float radius) : Shape(color), origin(origin), radius(radius) {}

	void AttachToShader(Program* program) override;
	static int Index;

	inline glm::vec3& GetOrigin() { return origin; }
	inline float& GetRadius() { return radius; }
private:
	glm::vec3 origin;
	float radius;
};

