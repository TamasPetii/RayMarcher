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