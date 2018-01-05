#include "shader.h"

#include <fstream>
#include <sstream>
#include <iostream>

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

Vertex_Shader::Vertex_Shader(const std::string& vs_file)
{
    std::string contents = file_as_string(vs_file);
    const char* c_contents = contents.c_str();

    shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(shader, 1, &c_contents, NULL);
    glCompileShader(shader);

    GLint shader_status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &shader_status);

    if (shader_status == GL_FALSE)
    {
        GLint len;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);

        char* log = new char[len];
        glGetShaderInfoLog(shader, len, NULL, log);

        std::stringstream ss;
        ss << "Vertex shader compilation error in \"" << vs_file << "\":" << log << std::endl;
        delete[] log;

        throw std::runtime_error(ss.str());
    }
}

Fragment_Shader::Fragment_Shader(const std::string& fs_file)
{
    std::string contents = file_as_string(fs_file);
    const char* c_contents = contents.c_str();

    shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(shader, 1, &c_contents, NULL);
    glCompileShader(shader);

    GLint shader_status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &shader_status);

    if (shader_status == GL_FALSE)
    {
        GLint len;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);

        char* log = new char[len];
        glGetShaderInfoLog(shader, len, NULL, log);

        std::stringstream ss;
        ss << "Fragment shader compilation error in \"" << fs_file << "\":" << log << std::endl;
        delete[] log;

        throw std::runtime_error(ss.str());
    }
}

Shader::Shader(Vertex_Shader& vs, Fragment_Shader& fs)
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

        std::stringstream ss;
        ss << "Shader program linker error: " << log << std::endl;
        delete[] log;

        throw std::runtime_error(ss.str());
    }

    glDetachShader(program, vs);
    glDetachShader(program, fs);
}

Shader::Shader(const std::string& vs_file, const std::string& fs_file)
{
    Vertex_Shader vs(vs_file);
    Fragment_Shader fs(fs_file);

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
