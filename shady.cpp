#include "shady.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <exception>
#include <fmt/format.h>

#include "shader.h"

Shady::Shady()
{
	// set error function
	glfwSetErrorCallback([](int error, const char* description)
	{
		throw std::runtime_error(fmt::format("{}: {}", error, description));
	});

    glfwInit();

    // initialize window
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    window = glfwCreateWindow(1280, 720, "shady", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        throw std::runtime_error("Window creation failed.");
    }

    // initialize glfw and glad
    glfwMakeContextCurrent(window);
    glfwSetWindowUserPointer(window, this);

    auto key_func = [](GLFWwindow* w, int key, int scancode, int action, int mods)
    {
    	Shady* shady = static_cast<Shady*>(glfwGetWindowUserPointer(w));
    	if (shady) shady->keyboard(w, key, scancode, action, mods);
    };

    auto mouse_func = [](GLFWwindow* w, int button, int action, int mods)
    {
    	Shady* shady = static_cast<Shady*>(glfwGetWindowUserPointer(w));
    	if (shady) shady->mouse(w, button, action, mods);
    };

    glfwSetKeyCallback(window, key_func);
    glfwSetMouseButtonCallback(window, mouse_func);

    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    glfwSwapInterval(1);

    // initialize geometry and shader
	vertex_array = init_vertex_array();
	shader_program = ShaderProgram("shaders/shader.vert", "shaders/shader.frag");
}

void Shady::run()
{
	// main loop
    while (!glfwWindowShouldClose(window))
    {
		glfwPollEvents();
    	update();
    	render();
        glfwSwapBuffers(window);
    }

    // terminate
    glfwDestroyWindow(window);
    glfwTerminate();
}

GLuint Shady::init_vertex_buffer()
{
	const float positions[] =
	{
		// top-left
		-1.0f,  1.0f, 0.0f, 1.0f,
		 1.0f,  1.0f, 0.0f, 1.0f,
		-1.0f, -1.0f, 0.0f, 1.0f,

		// bottom-right
		 1.0f,  1.0f, 0.0f, 1.0f,
		 1.0f, -1.0f, 0.0f, 1.0f,
		-1.0f, -1.0f, 0.0f, 1.0f,
	};

	GLuint buffer;
	glGenBuffers(1, &buffer);

	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return buffer;
}

GLuint Shady::init_vertex_array()
{
	GLuint vertex_array;
	glGenVertexArrays(1, &vertex_array);

	vertex_buffer = init_vertex_buffer();

	glBindVertexArray(vertex_array);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(0);

	return vertex_array;
}

void Shady::keyboard(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
    	glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

void Shady::mouse(GLFWwindow* window, int button, int action, int mods)
{

}

void Shady::update()
{
	
}

void Shady::render()
{
	// resolution
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);

    // mouse position
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	// update viewport
    float ratio = width / (float) height;
    glViewport(0, 0, width, height);

    // draw frame
	glUseProgram(shader_program);

	glBindVertexArray(vertex_array);

	glUniform2f(glGetUniformLocation(shader_program, "resolution"), (float)width, (float)height);
	glUniform2f(glGetUniformLocation(shader_program, "mouse"), (float)xpos, (float)ypos);

    glClear(GL_COLOR_BUFFER_BIT);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindVertexArray(0);
	glUseProgram(0);
}
