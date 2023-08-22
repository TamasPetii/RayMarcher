#pragma once
#include "Shape.h"

class Capsule : public Shape
{
public:
	Capsule(glm::vec3 color, glm::vec3 origin1, glm::vec3 origin2, float radius) : Shape(color), origin1(origin1), origin2(origin2), radius(radius) {}
	~Capsule() {}

	void AttachToShader(Program* program) override;
	static int Index;

	inline glm::vec3& GetOrigin1() { return origin1; }
	inline glm::vec3& GetOrigin2() { return origin2; }
	inline float& GetRadius() { return radius; }
private:
	glm::vec3 origin1;
	glm::vec3 origin2;
	float radius;
};

