#include "Torus.h"

int Torus::Index = 0;

void Torus::AttachToShader(Program* program)
{
	program->Bind();
	program->SetUniform("uToruses[" + std::to_string(Index) + "].color", color);
	program->SetUniform("uToruses[" + std::to_string(Index) + "].origin", origin);
	program->SetUniform("uToruses[" + std::to_string(Index) + "].radiusPrimary", radiusPrimary);
	program->SetUniform("uToruses[" + std::to_string(Index) + "].radiusSecondary", radiusSecondary);
	program->SetUniform("uTorusNumber", ++Index);
	program->UnBind();
}

Torus* Torus::RandomTorus()
{
	glm::vec3 color = glm::vec3(Shape::RandomFloat(), Shape::RandomFloat(), Shape::RandomFloat());
	float radiusPrimary = 0.5 + RandomFloat() / 2;
	float radiusSecondary = 0.2 + RandomFloat() / 5;
	glm::vec3 origin = glm::vec3(15 * Shape::RandomFloat(), radiusSecondary, 15 * Shape::RandomFloat());

	return new Torus(color, origin, radiusPrimary, radiusSecondary);
}