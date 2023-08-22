#include "Sphere.h"

int Sphere::Index = 0;

void Sphere::AttachToShader(Program* program)
{
	program->Bind();
	program->SetUniform("uSpheres[" + std::to_string(Index) + "].color", color);
	program->SetUniform("uSpheres[" + std::to_string(Index) + "].origin", origin);
	program->SetUniform("uSpheres[" + std::to_string(Index) + "].radius", radius);
	program->SetUniform("uSpheres[" + std::to_string(Index) + "].subtract", (int)subtract);
	program->SetUniform("uSphereNumber", ++Index);
	program->UnBind();
}

Sphere* Sphere::RandomSphere()
{
	Sphere* sphere = new Sphere();
	sphere->radius = 1 + Shape::RandomFloat();
	sphere->color = glm::vec3(Shape::RandomFloat(), Shape::RandomFloat(), Shape::RandomFloat());
	sphere->origin = glm::vec3(15 * cosf(Shape::RandomFloat() * 2 * M_PI), sphere->radius, 15 * sinf(Shape::RandomFloat() * 2 * M_PI));
	return sphere;
}