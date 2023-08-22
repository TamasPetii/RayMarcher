#pragma once
#include "Shape.h"

class Torus : public Shape
{
public:
	Torus(glm::vec3 color, glm::vec3 origin, float radiusPrimary, float radiusSecondary) : Shape(color), origin(origin), radiusPrimary(radiusPrimary), radiusSecondary(radiusSecondary) {}
	
	void AttachToShader(Program* program) override;
	static int Index;
	
	inline glm::vec3& GetOrigin() { return origin; }
	inline float& GetRadiusPrimary() { return radiusPrimary; }
	inline float& GetRadiusSecondary() { return radiusSecondary; }
private:
	glm::vec3 origin;
	float radiusPrimary;
	float radiusSecondary;
};