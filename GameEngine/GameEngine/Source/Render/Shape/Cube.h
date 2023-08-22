#pragma once
#include "Shape.h"

class Cube : public Shape
{
public:
	Cube(glm::vec3 color, glm::vec3 origin, glm::vec3 parameters, Material material) : Shape(color, material), origin(origin), parameters(parameters) {}
	~Cube() {}
	
	void AttachToShader(Program* program) override;
	static int Index;
	static Cube* RandomCube();

	inline glm::vec3& GetOrigin() { return origin; }
	inline glm::vec3& GetParameters() { return parameters; }
private:
	glm::vec3 origin;
	glm::vec3 parameters;
};

