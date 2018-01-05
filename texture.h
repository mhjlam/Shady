#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Texture
{
private:
	GLuint texture;

public:
	Texture();

	operator GLuint()
	{
		return texture;
	}
};
