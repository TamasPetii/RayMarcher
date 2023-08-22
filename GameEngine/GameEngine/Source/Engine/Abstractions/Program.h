#pragma once
#include <GLEW/glew.h>
#include <GLM/glm.hpp>
#include "Shader.h"
#include "Texture.h"

class Program
{
public:
	Program(const std::vector<Shader>& shaders, const std::vector<ShaderLayout>& attribs);
	~Program();

	void Bind() const;
	void UnBind() const;

	template<typename T>
	inline void SetUniform(const std::string& name, const T& value);

	inline void SetUniformTexture(const std::string& name, const int sampler, const Texture* texture);
	inline void SetUniformTexture(const std::string& name, const int sampler, unsigned int textureId);
private:
	unsigned int mProgramId = 0;
};

#include "Program.inl"