#pragma once

#include <string>
#include <unordered_map>
#include "glm/glm.hpp"

struct ShaderProgramSource
{
	std::string vertexSource;
	std::string framebuffSource;
};

class Shader
{
public:
	Shader(const std::string& filePath);
	~Shader();

	void Bind() const;
	void UnBind() const;
	void SetUniform4f(const std::string& name, float v1, float v2, float v3, float v4);
	void SetUniform1f(const std::string& name, float value);
	void SetUniform1i(const std::string& name, int value);
	void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);
private:
	unsigned int m_RendererID;
	std::string m_filePath;
	std::unordered_map<std::string, int> m_UniformLocationCache;

private:
	int GetUniformLocation(const std::string& name);
	unsigned int ComplileShader(unsigned int type, const std::string& source);
	ShaderProgramSource ParseShader();
	unsigned int CreateShader(const std::string& vertexSource, const std::string& frameSource);
};
