#include "Sphere.h"

int Sphere::Index = 0;

void Sphere::AttachToShader(Program* program)
{
	program->Bind();
	program->SetUniform("uSpheres[" + std::to_string(Index) + "].color", color);
	program->SetUniform("uSpheres[" + std::to_string(Index) + "].origin", origin);
	program->SetUniform("uSpheres[" + std::to_string(Index) + "].radius", radius);
	program->SetUniform("uSpheres[" + std::to_string(Index) + "].subtract", (int)subtract);
	program->SetUniform("uSpheres[" + std::to_string(Index) + "].material", (int)material);
	program->SetUniform("uSphereNumber", ++Index);
	program->UnBind();
}

Sphere* Sphere::RandomSphere()
{
	float radius = 1 + Shape::RandomFloat();
	glm::vec3 color = glm::vec3(Shape::RandomFloat(), Shape::RandomFloat(), Shape::RandomFloat());
	glm::vec3 origin = glm::vec3(15 * cosf(Shape::RandomFloat() * 2 * M_PI), radius, 15 * sinf(Shape::RandomFloat() * 2 * M_PI));
	Material material = Shape::RandomFloat() > 0.9f ? REFLECTIVE : DIFFUSE;
	return new Sphere(color, origin, radius, material);
}