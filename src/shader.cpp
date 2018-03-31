#include "shader.hpp"

#include "fmt/format.h"
#include "util.hpp"

Vertex_Shader::Vertex_Shader(const std::string& vs_file)
{
    std::string contents = util::file_as_string(vs_file);
    const char* c_contents = contents.c_str();

    shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(shader, 1, &c_contents, NULL);
    glCompileShader(shader);

    GLint shader_status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &shader_status);

    if (shader_status == GL_FALSE)
    {
        GLint info_log_len;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_log_len);

        std::string info_log_str;
        glGetShaderInfoLog(shader, info_log_len, nullptr, &info_log_str[0]);

        std::string msg = fmt::format("Vertex shader compilation error in \"{}\": {}", vs_file, info_log_str);
        throw std::runtime_error(msg.c_str());
    }
}

Fragment_Shader::Fragment_Shader(const std::string& fs_file)
{
    std::string contents = util::file_as_string(fs_file);
    const char* c_contents = contents.c_str();

    shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(shader, 1, &c_contents, NULL);
    glCompileShader(shader);

    GLint shader_status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &shader_status);

    if (shader_status == GL_FALSE)
    {
        GLint info_log_len;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_log_len);

        std::string info_log_str;
        glGetShaderInfoLog(shader, info_log_len, nullptr, &info_log_str[0]);

        std::string msg = fmt::format("Fragment shader compilation error in \"{}\": {}", fs_file, info_log_str);
        throw std::runtime_error(msg.c_str());
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
        GLint info_log_len;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_log_len);

        std::string info_log_str;
        glGetShaderInfoLog(program, info_log_len, nullptr, &info_log_str[0]);

        std::string msg = fmt::format("Shader program linker error: {}", info_log_str);
        throw std::runtime_error(msg.c_str());
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
        glGetProgramInfoLog(program, info_log_len, nullptr, &info_log_str[0]);

        std::string msg = fmt::format("Shader program linker failure: {}", info_log_str);
        throw std::runtime_error(info_log_str.c_str());
    }

    glDetachShader(program, vs);
    glDetachShader(program, fs);
}
