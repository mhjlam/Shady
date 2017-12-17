#pragma once

#include <memory>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Shader;

class Shady
{
private:
	GLFWwindow* window;

	std::shared_ptr<Shader> shader;

	GLuint shader_program;
	GLuint vertex_buffer;
	GLuint vertex_array;

	GLuint init_shader_program();
	GLuint init_vertex_buffer();
	GLuint init_vertex_array();

	void keyboard(GLFWwindow* window, int key, int scancode, int action, int mods);
	void mouse(GLFWwindow* window, int button, int action, int mods);

	void update();
	void render();

public:
	Shady();
	void run();
};
