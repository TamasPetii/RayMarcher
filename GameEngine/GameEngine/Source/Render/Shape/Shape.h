#pragma once
#define _USE_MATH_DEFINES 
#include <GLM/glm.hpp>
#include <stdlib.h>
#include <cmath>
#include "../../Engine/Abstractions/Program.h"

class Shape 
{
public:
	Shape() : Shape(glm::vec3(1, 1, 1)) {}
	Shape(glm::vec3 color) : color(color) {}

	static float RandomFloat() { return static_cast<float>(rand()) / static_cast<float>(RAND_MAX); }
	virtual void AttachToShader(Program* program) = 0;
	inline glm::vec3& GetColor() { return color; }
	inline bool& GetSubtract() { return subtract; }
protected:
	bool subtract = false;
	glm::vec3 color;
};

