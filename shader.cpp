#include "shader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <fmt/format.h>

const std::string file_as_string(const std::string& filename)
{
	std::ifstream file(filename);

	if (!file.good())
	{
		std::stringstream ss;
		ss << "Cannot open or read file \"" << filename << "\"" << std::endl;
		throw std::runtime_error(ss.str());
	}

	file.seekg(0, std::ios::end);
	std::size_t size = file.tellg();
	std::string buffer(size, ' ');
	file.seekg(0);
	file.read(&buffer[0], size);
	return buffer;
}

Shader::~Shader() {}

VertexShader::VertexShader(const std::string& filename)
{
	const char* contents = file_as_string(filename).c_str();

	shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(shader, 1, &contents, NULL);
	glCompileShader(shader);

	GLint shader_status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &shader_status);

	if (shader_status == GL_FALSE)
	{
		GLint info_log_len;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_log_len);

		std::string info_log_str;
		glGetShaderInfoLog(shader, info_log_len, NULL, &info_log_str[0]);

		std::stringstream ss;
		ss << "Compile failure in vertex shader \"" << filename << "\":" << std::endl << info_log_str << std::endl;
		throw std::runtime_error(ss.str());
	}
}

FragmentShader::FragmentShader(const std::string& filename)
{
	const char* contents = file_as_string(filename).c_str();

	shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(shader, 1, &contents, NULL);
	glCompileShader(shader);

	GLint shader_status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &shader_status);

	if (shader_status == GL_FALSE)
	{
		GLint info_log_len;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_log_len);

		std::string info_log_str;
		glGetShaderInfoLog(shader, info_log_len, NULL, &info_log_str[0]);

		std::stringstream ss;
		ss << "Compile failure in fragment shader \"" << filename << "\":" << std::endl << info_log_str << std::endl;
		throw std::runtime_error(ss.str());
	}
}

ShaderProgram::ShaderProgram(VertexShader& vs, FragmentShader& fs)
{
	program = glCreateProgram();

	glAttachShader(program, vs);
	glAttachShader(program, fs);

	glLinkProgram(program);

	GLint success;
	glGetProgramiv(program, GL_LINK_STATUS, &success);

	if (!success)
	{
		GLint len;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &len);

		char* log = new char[len];
    	glGetShaderInfoLog(program, len, nullptr, log);

    	std::string msg = fmt::format("Shader program linker failure: {}", log);
    	delete[] log;
    	throw std::runtime_error(msg);
	}

	glDetachShader(program, vs);
	glDetachShader(program, fs);
}

ShaderProgram::ShaderProgram(const std::string& vsfile, const std::string& fsfile)
{
	VertexShader vs(vsfile);
	FragmentShader fs(fsfile);

	program = glCreateProgram();

	glAttachShader(program, vs);
	glAttachShader(program, fs);

	glLinkProgram(program);

	GLint shader_program_status;
	glGetProgramiv(program, GL_LINK_STATUS, &shader_program_status);

	if (shader_program_status == GL_FALSE)
	{
		GLint info_log_len;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_log_len);

		std::string info_log_str;
		glGetProgramInfoLog(program, info_log_len, NULL, &info_log_str[0]);

		std::stringstream ss;
		ss << "Shader program linker failure:" << info_log_str << std::endl;
		throw std::runtime_error(ss.str());
	}

	glDetachShader(program, vs);
	glDetachShader(program, fs);
}
