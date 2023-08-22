#include "Capsule.h"

int Capsule::Index = 0;

void Capsule::AttachToShader(Program* program)
{
	program->Bind();
	program->SetUniform("uCapsules[" + std::to_string(Index) + "].color", color);
	program->SetUniform("uCapsules[" + std::to_string(Index) + "].origin1", origin1);
	program->SetUniform("uCapsules[" + std::to_string(Index) + "].origin2", origin2);
	program->SetUniform("uCapsules[" + std::to_string(Index) + "].radius", radius);
	program->SetUniform("uCapsuleNumber", ++Index);
	program->UnBind();
}

Capsule* Capsule::RandomCapsule()
{
	float radius = 0.5 + Shape::RandomFloat() / 1.5;
	glm::vec3 color = glm::vec3(Shape::RandomFloat(), Shape::RandomFloat(), Shape::RandomFloat());
	glm::vec3 origin1 = glm::vec3(Shape::RandomFloat(), Shape::RandomFloat() * 10 + 1 + radius, Shape::RandomFloat());
	glm::vec3 origin2 = glm::vec3(Shape::RandomFloat(), radius, Shape::RandomFloat());
	return new Capsule(color, origin1, origin2, radius);
}