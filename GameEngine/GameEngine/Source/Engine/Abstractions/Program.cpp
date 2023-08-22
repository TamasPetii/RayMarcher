#include "Program.h"

Program::Program(const std::vector<Shader>& shaders, const std::vector<ShaderLayout>& attribs)
{
	mProgramId = glCreateProgram();

	//Attach shader to prgoram
	for (auto s : shaders)
	{
		glAttachShader(mProgramId, s.GetShaderId());
	}

	//Assigning VAO attributes to shader variables (Must do before linking the program!)
	for (auto a : attribs)
	{
		glBindAttribLocation(mProgramId, a.GetLayoutLocation(), a.GetLayoutName().c_str());
	}

	//Linking the program and validating it -> information about the validation in info log
	glLinkProgram(mProgramId);
	glValidateProgram(mProgramId);

	//Check possible linking errors
	int result, info_length;
	glGetProgramiv(mProgramId, GL_LINK_STATUS, &result);
	glGetProgramiv(mProgramId, GL_INFO_LOG_LENGTH, &info_length);

	if (result == GL_FALSE)
	{
		char* message = (char*)_malloca(info_length * sizeof(char));

		glGetProgramInfoLog(mProgramId, info_length, &info_length, message);

		throw std::runtime_error("Error occurred while linking the program.\nId: " + std::to_string(mProgramId) + "\nMessage: " + message);
		free(message);
	}

	glUseProgram(0);
}

Program::~Program()
{
	glDeleteProgram(mProgramId);
}

void Program::Bind() const
{
	glUseProgram(mProgramId);
}
void Program::UnBind() const
{
	glUseProgram(0);
}