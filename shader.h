#pragma once

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Shader
{
protected:
	GLuint shader;

public:
	virtual ~Shader() = 0;
	operator GLuint() { return shader; }
};

class VertexShader : public Shader
{
public:
	VertexShader(const std::string& filename);
	~VertexShader() {};
};

class FragmentShader : public Shader
{
public:
	FragmentShader(const std::string& filename);
	~FragmentShader() {};
};

class ShaderProgram
{
private:
	GLuint program;

public:
	ShaderProgram(VertexShader& vs, FragmentShader& fs);
	ShaderProgram(const std::string& vsfile, const std::string& fsfile);
	operator GLuint() { return program; }
};
