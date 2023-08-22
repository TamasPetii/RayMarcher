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