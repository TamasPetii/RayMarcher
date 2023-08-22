#pragma once
#define _USE_MATH_DEFINES 
#include <GLM/glm.hpp>
#include <stdlib.h>
#include <cmath>
#include "../../Engine/Abstractions/Program.h"

enum Material
{
	DIFFUSE,
	REFLECTIVE
};

class Shape 
{
public:
	Shape() : Shape(glm::vec3(1, 1, 1), DIFFUSE) {}
	Shape(glm::vec3 color, Material material) : color(color), material(material) {}

	static float RandomFloat() { return static_cast<float>(rand()) / static_cast<float>(RAND_MAX); }
	virtual void AttachToShader(Program* program) = 0;
	inline glm::vec3& GetColor() { return color; }
	inline bool& GetSubtract() { return subtract; }
	inline Material& GetMaterial() { return material; }
protected:
	Material material;
	bool subtract = false;
	glm::vec3 color;
};

