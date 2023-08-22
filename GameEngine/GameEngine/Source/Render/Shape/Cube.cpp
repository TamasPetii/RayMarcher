#include "Cube.h"

int Cube::Index = 0;

void Cube::AttachToShader(Program* program)
{
	program->Bind();
	program->SetUniform("uCubes[" + std::to_string(Index) + "].color", color);
	program->SetUniform("uCubes[" + std::to_string(Index) + "].origin", origin);
	program->SetUniform("uCubes[" + std::to_string(Index) + "].parameters", parameters);
	program->SetUniform("uCubes[" + std::to_string(Index) + "].material", (int)material);
	program->SetUniform("uCubeNumber", ++Index);
	program->UnBind();

}

Cube* Cube::RandomCube()
{
	glm::vec3 color = glm::vec3(Shape::RandomFloat(), Shape::RandomFloat(), Shape::RandomFloat());
	glm::vec3 parameters = 2.f * glm::vec3(0.5 + Shape::RandomFloat() / 2, 0.5 + Shape::RandomFloat() / 2, 0.5 + Shape::RandomFloat() / 2);
	glm::vec3 origin = glm::vec3(15 * cosf(Shape::RandomFloat() * 2 * M_PI), parameters.y, 15 * sinf(Shape::RandomFloat() * 2 * M_PI));	
	Material material = Shape::RandomFloat() > 0.9f ? REFLECTIVE : DIFFUSE;
	return new Cube(color, origin, parameters, material);
}