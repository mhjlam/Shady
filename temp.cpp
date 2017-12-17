#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
    	glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

static char* fopenstr(const char *path)
{
	FILE *fp = fopen(path, "rb");
	if (!fp) exit(1);

	fseek(fp , 0L , SEEK_END);
	long sz = ftell(fp);
	rewind(fp);

	/* allocate memory for entire content */
	char *buffer = (char*)calloc(1, sz + 1);
	if (!buffer) fclose(fp), exit(1);

	/* copy the file into the buffer */
	if (fread(buffer, sz, 1, fp) != 1) fclose(fp), free(buffer), exit(1);

	fclose(fp);

	return buffer;
}

static GLuint init_shader(const char *file, GLuint type)
{
	char *contents = fopenstr(file);

	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &contents, NULL);
	glCompileShader(shader);

	free(contents);

	GLint shader_status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &shader_status);

	if (shader_status == GL_FALSE)
	{
		GLint info_log_len;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_log_len);

		GLchar *info_log_str = (GLchar*) malloc(info_log_len + 1);
		glGetShaderInfoLog(shader, info_log_len, NULL, info_log_str);

		fprintf(stderr, "Compile failure in shader \"%s\":\n%s\n", file, info_log_str);
		free(info_log_str);
	}

	return shader;
}

static GLuint init_shader_program()
{
	GLuint vertex_shader = init_shader("shader.vert", GL_VERTEX_SHADER);
	GLuint fragment_shader = init_shader("shader.frag", GL_FRAGMENT_SHADER);

	// shader program
	GLuint program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	glLinkProgram(program);

	GLint shader_program_status;
	glGetProgramiv(program, GL_LINK_STATUS, &shader_program_status);

	if (shader_program_status == GL_FALSE)
	{
		GLint info_log_len;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_log_len);

		GLchar *info_log_str = (GLchar*) malloc(info_log_len + 1);
		glGetProgramInfoLog(program, info_log_len, NULL, info_log_str);
		fprintf(stderr, "Linker failure: %s\n", info_log_str);
		free(info_log_str);
	}

	glDetachShader(program, vertex_shader);
	glDetachShader(program, fragment_shader);

	return program;
}

static GLuint init_vertex_buffer()
{
	const float positions[] =
	{
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

static GLuint init_vertex_array()
{
	GLuint vertex_array;
	glGenVertexArrays(1, &vertex_array);
	return vertex_array;
}

GLFWwindow *window;
GLuint shader_program;
GLuint vertex_buffer;
GLuint vertex_array;

static int initialize()
{
    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
    {
    	return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    window = glfwCreateWindow(1280, 720, "shady", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return false;
    }

    // initialize glfw and glad
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    glfwSwapInterval(1);

	// initialize shader program
	shader_program = init_shader_program();
	vertex_buffer = init_vertex_buffer();
	vertex_array = init_vertex_array();

	return true;
}

static void render()
{
	// update viewport
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);

    float ratio = width / (float) height;
    glViewport(0, 0, width, height);

    // draw frame
	glUseProgram(shader_program);

	glBindVertexArray(vertex_array);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

    glClear(GL_COLOR_BUFFER_BIT);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glDisableVertexAttribArray(0);
	glUseProgram(0);
}

int main()
{
    if (!initialize())
	{
		return 1;
	}

	// main loop
    while (!glfwWindowShouldClose(window))
    {
    	render();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // terminate
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
