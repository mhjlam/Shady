#pragma once

#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Base_Shader
{
protected:
	GLuint shader;

public:
	virtual operator GLuint()
	{
		return shader;
	}
};

class Vertex_Shader : public Base_Shader
{
public:
	Vertex_Shader(const std::string& vs_file);
};

class Fragment_Shader : public Base_Shader
{
public:
	Fragment_Shader(const std::string& fs_file);
};

class Shader
{
private:
	GLuint program;

public:
	Shader(Vertex_Shader& vs, Fragment_Shader& fs);
	Shader(const std::string& vs_file, const std::string& fs_file);

	operator GLuint()
	{
		return program;
	}
};
