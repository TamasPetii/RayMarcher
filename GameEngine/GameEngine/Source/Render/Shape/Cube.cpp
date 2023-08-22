#include "Cube.h"

int Cube::Index = 0;

void Cube::AttachToShader(Program* program)
{
	program->Bind();
	program->SetUniform("uCubes[" + std::to_string(Index) + "].color", color);
	program->SetUniform("uCubes[" + std::to_string(Index) + "].origin", origin);
	program->SetUniform("uCubes[" + std::to_string(Index) + "].parameters", parameters);
	program->SetUniform("uCubeNumber", ++Index);
	program->UnBind();

}