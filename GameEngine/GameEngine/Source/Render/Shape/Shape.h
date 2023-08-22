#pragma once
#include <GLM/glm.hpp>
#include "../../Engine/Abstractions/Program.h"

class Shape 
{
public:
	Shape(glm::vec3 color) : color(color) {}
	virtual void AttachToShader(Program* program) = 0;
	inline glm::vec3& GetColor() { return color; }
protected:
	glm::vec3 color;
};

