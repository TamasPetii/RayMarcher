#include "Sphere.h"

int Sphere::Index = 0;

void Sphere::AttachToShader(Program* program)
{
	program->Bind();
	program->SetUniform("uSpheres[" + std::to_string(Index) + "].color", color);
	program->SetUniform("uSpheres[" + std::to_string(Index) + "].origin", origin);
	program->SetUniform("uSpheres[" + std::to_string(Index) + "].radius", radius);
	program->SetUniform("uSphereNumber", ++Index);
	program->UnBind();
}