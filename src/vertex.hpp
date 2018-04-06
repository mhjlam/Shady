#pragma once

#include <array>
#include <vector>
#include <iterator>
#include <algorithm>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Shader;

enum Vertex_Type
{
    VERTEX_TYPE_UNDEFINED,

    VERTEX_TYPE_POSITION2,
    VERTEX_TYPE_POSITION2_COLOR,
    VERTEX_TYPE_POSITION2_TEXCOORD,
    VERTEX_TYPE_POSITION2_TEXCOORD_COLOR,

    VERTEX_TYPE_POSITION,
    VERTEX_TYPE_POSITION_COLOR,
    VERTEX_TYPE_POSITION_TEXCOORD,
    VERTEX_TYPE_POSITION_NORMAL,
    VERTEX_TYPE_POSITION_NORMAL_TEXCOORD
};

struct Vertex_Attrib
{
    GLuint index;
    GLint size;             // 1, 2, 3, 4 or GL_BGRA
    GLenum type;            // e.g. GL_BYTE, GL_SHORT, GL_INT, GL_FLOAT, GL_DOUBLE
    GLboolean normalized;   // GL_TRUE or GL_FALSE
    GLsizei stride;
    GLsizei offset;         // offset to the first component of this vertex attribute
};

struct Vertex
{
    Vertex_Type type = VERTEX_TYPE_UNDEFINED;
    std::vector<GLfloat> data = std::vector<GLfloat>();
    std::vector<Vertex_Attrib> attribs = std::vector<Vertex_Attrib>();

    static std::vector<GLfloat> assemble(const std::vector<Vertex>& vertices)
    {
        if (vertices.size() < 2)
        {
            throw std::runtime_error("Need at least two vertices for assembly");
        }

        Vertex_Type type = vertices.front().type;
        if (type == VERTEX_TYPE_UNDEFINED)
        {
            throw std::runtime_error("Cannot assemble vertices with unknown type");
        }

        std::vector<GLfloat> data;
        for (const Vertex& vertex : vertices)
        {
            if (vertex.type != type)
            {
                throw std::runtime_error("All vertex types must correspond");
            }

            data.insert(data.end(), vertex.data.begin(), vertex.data.end());
        }

        return data;
    }
};

// 2D
struct Vertex_Position2 : public Vertex
{
    Vertex_Position2(std::array<GLfloat, 2> position,
                     GLuint position_index = 0)
    {
        type = VERTEX_TYPE_POSITION2;

        data = std::vector<GLfloat>();
        data.insert(data.end(), position.begin(), position.end());

        // position
        Vertex_Attrib attrib_position;
        attrib_position.index = position_index;
        attrib_position.size = 2;
        attrib_position.type = GL_FLOAT;
        attrib_position.normalized = GL_FALSE;
        attrib_position.stride = data.size() * sizeof(GLfloat);
        attrib_position.offset = 0;

        attribs.push_back(attrib_position);
    }

    Vertex_Position2(std::array<GLfloat, 2> position, 
                     GLuint shader_program, 
                     const char* position_name = "vs_position") : Vertex_Position2(position)
    {
        attribs[0].index = glGetAttribLocation(shader_program, position_name);
    }
};

struct Vertex_Position2_Color : public Vertex
{
    Vertex_Position2_Color(std::array<GLfloat, 2> position, 
                           std::array<GLfloat, 3> color, 
                           GLuint position_index = 0, 
                           GLuint color_index = 1)
    {
        type = VERTEX_TYPE_POSITION2_COLOR;

        data = std::vector<GLfloat>();
        data.insert(data.end(), position.begin(), position.end());
        data.insert(data.end(), color.begin(), color.end());

        Vertex_Attrib attrib_position;
        attrib_position.index = position_index;
        attrib_position.size = 2;
        attrib_position.type = GL_FLOAT;
        attrib_position.normalized = GL_FALSE;
        attrib_position.stride = data.size() * sizeof(GLfloat);
        attrib_position.offset = 0;

        Vertex_Attrib attrib_color;
        attrib_color.index = color_index;
        attrib_color.size = 3;
        attrib_color.type = GL_FLOAT;
        attrib_color.normalized = GL_FALSE;
        attrib_color.stride = data.size() * sizeof(GLfloat);
        attrib_color.offset = 2; // skip position elements

        attribs.push_back(attrib_position);
        attribs.push_back(attrib_color);
    }

    Vertex_Position2_Color(std::array<GLfloat, 2> position, 
                           std::array<GLfloat, 3> color, 
                           GLuint shader_program, 
                           const char* position_name = "vs_position", 
                           const char* color_name = "vs_color") : Vertex_Position2_Color(position, color)
    {
        attribs[0].index = glGetAttribLocation(shader_program, position_name);
        attribs[1].index = glGetAttribLocation(shader_program, color_name);
    }
};

struct Vertex_Position2_Texcoord : public Vertex
{
    Vertex_Position2_Texcoord(std::array<GLfloat, 2> position, 
                              std::array<GLfloat, 2> texcoord, 
                              GLuint position_index = 0, 
                              GLuint texcoord_index = 1)
    {
        type = VERTEX_TYPE_POSITION2_TEXCOORD;

        data = std::vector<GLfloat>();
        data.insert(data.end(), position.begin(), position.end());
        data.insert(data.end(), texcoord.begin(), texcoord.end());

        Vertex_Attrib attrib_position;
        attrib_position.index = position_index;
        attrib_position.size = 2;
        attrib_position.type = GL_FLOAT;
        attrib_position.normalized = GL_FALSE;
        attrib_position.stride = data.size() * sizeof(GLfloat);
        attrib_position.offset = 0;

        Vertex_Attrib attrib_texcoord;
        attrib_texcoord.index = texcoord_index;
        attrib_texcoord.size = 2;
        attrib_texcoord.type = GL_FLOAT;
        attrib_texcoord.normalized = GL_FALSE;
        attrib_texcoord.stride = 2 * sizeof(GLfloat);
        attrib_texcoord.offset = 2;

        attribs.push_back(attrib_position);
        attribs.push_back(attrib_texcoord);
    }

    Vertex_Position2_Texcoord(std::array<GLfloat, 2> position, 
                              std::array<GLfloat, 2> texcoord,
                              GLuint shader_program, 
                              const char* position_name = "vs_position", 
                              const char* texcoord_name = "vs_texcoord") : Vertex_Position2_Texcoord(position, texcoord)
    {
        attribs[0].index = glGetAttribLocation(shader_program, position_name);
        attribs[1].index = glGetAttribLocation(shader_program, texcoord_name);
    }
};

struct Vertex_Position2_Texcoord_Color : public Vertex
{
    Vertex_Position2_Texcoord_Color(std::array<GLfloat, 2> position, 
                                    std::array<GLfloat, 2> texcoord, 
                                    std::array<GLfloat, 3> color, 
                                    GLuint position_index = 0, 
                                    GLuint texcoord_index = 1, 
                                    GLuint color_index = 2)
    {
        type = VERTEX_TYPE_POSITION2_TEXCOORD_COLOR;

        data = std::vector<GLfloat>();
        data.insert(data.end(), position.begin(), position.end());
        data.insert(data.end(), texcoord.begin(), texcoord.end());
        data.insert(data.end(), color.begin(), color.end());

        Vertex_Attrib attrib_position;
        attrib_position.index = position_index;
        attrib_position.size = 2;
        attrib_position.type = GL_FLOAT;
        attrib_position.normalized = GL_FALSE;
        attrib_position.stride = data.size() * sizeof(GLfloat);
        attrib_position.offset = 0;

        Vertex_Attrib attrib_texcoord;
        attrib_texcoord.index = texcoord_index;
        attrib_texcoord.size = 2;
        attrib_texcoord.type = GL_FLOAT;
        attrib_texcoord.normalized = GL_FALSE;
        attrib_texcoord.stride = data.size() * sizeof(GLfloat);
        attrib_texcoord.offset = 2;
        
        Vertex_Attrib attrib_color;
        attrib_color.index = color_index;
        attrib_color.size = 3;
        attrib_color.type = GL_FLOAT;
        attrib_color.normalized = GL_FALSE;
        attrib_color.stride = data.size() * sizeof(GLfloat);
        attrib_color.offset = 4; // skip position and texcoord

        attribs.push_back(attrib_position);
        attribs.push_back(attrib_texcoord);
        attribs.push_back(attrib_color);
    }
    
    Vertex_Position2_Texcoord_Color(std::array<GLfloat, 2> position, 
                                    std::array<GLfloat, 2> texcoord, 
                                    std::array<GLfloat, 3> color, 
                                    GLuint shader_program, 
                                    const char* position_name = "vs_position", 
                                    const char* texcoord_name = "vs_texcoord", 
                                    const char* color_name = "vs_color") : Vertex_Position2_Texcoord_Color(position, texcoord, color)
    {
        attribs[0].index = glGetAttribLocation(shader_program, position_name);
        attribs[1].index = glGetAttribLocation(shader_program, texcoord_name);
        attribs[2].index = glGetAttribLocation(shader_program, color_name);
    }
};

// 3D
struct Vertex_Position : public Vertex
{
    Vertex_Position(std::array<GLfloat, 3> position, 
                    GLuint position_index = 0)
    {
        type = VERTEX_TYPE_POSITION;

        data = std::vector<GLfloat>();
        data.insert(data.end(), position.begin(), position.end());

        Vertex_Attrib attrib_position;
        attrib_position.index = position_index;
        attrib_position.size = 3;
        attrib_position.type = GL_FLOAT;
        attrib_position.normalized = GL_FALSE;
        attrib_position.stride = data.size() * sizeof(GLfloat);
        attrib_position.offset = 0;

        attribs.push_back(attrib_position);
    }

    Vertex_Position(std::array<GLfloat, 3> position, 
                    GLuint shader_program, 
                    const char* position_name = "vs_position") : Vertex_Position(position)
    {
        attribs[0].index = glGetAttribLocation(shader_program, position_name);
    }
};

struct Vertex_Position_Color : public Vertex
{
    Vertex_Position_Color(std::array<GLfloat, 3> position, 
                          std::array<GLfloat, 3> color, 
                          GLuint position_index = 0, 
                          GLuint color_index = 1)
    {
        type = VERTEX_TYPE_POSITION_COLOR;

        data = std::vector<GLfloat>();
        data.insert(data.end(), position.begin(), position.end());
        data.insert(data.end(), color.begin(), color.end());

        Vertex_Attrib attrib_position;
        attrib_position.index = position_index;
        attrib_position.size = 3;
        attrib_position.type = GL_FLOAT;
        attrib_position.normalized = GL_FALSE;
        attrib_position.stride = data.size() * sizeof(GLfloat);
        attrib_position.offset = 0;

        Vertex_Attrib attrib_color;
        attrib_color.index = color_index;
        attrib_color.size = 3;
        attrib_color.type = GL_FLOAT;
        attrib_color.normalized = GL_FALSE;
        attrib_color.stride = data.size() * sizeof(GLfloat);
        attrib_color.offset = 3;

        attribs.push_back(attrib_position);
        attribs.push_back(attrib_color);
    }

    Vertex_Position_Color(std::array<GLfloat, 3> position, 
                          std::array<GLfloat, 3> color, 
                          GLuint shader_program, 
                          const char* position_name = "vs_position", 
                          const char* color_name = "vs_color") : Vertex_Position_Color(position, color)
    {
        attribs[0].index = glGetAttribLocation(shader_program, position_name);
        attribs[1].index = glGetAttribLocation(shader_program, color_name);
    }
};

struct Vertex_Position_Texcoord : public Vertex
{
    Vertex_Position_Texcoord(std::array<GLfloat, 3> position, 
                             std::array<GLfloat, 2> texcoord, 
                             GLuint position_index = 0, 
                             GLuint texcoord_index = 1)
    {
        type = VERTEX_TYPE_POSITION_TEXCOORD;

        data = std::vector<GLfloat>();
        data.insert(data.end(), position.begin(), position.end());
        data.insert(data.end(), texcoord.begin(), texcoord.end());

        Vertex_Attrib attrib_position;
        attrib_position.index = position_index;
        attrib_position.size = 3;
        attrib_position.type = GL_FLOAT;
        attrib_position.normalized = GL_FALSE;
        attrib_position.stride = data.size() * sizeof(GLfloat);
        attrib_position.offset = 0;

        Vertex_Attrib attrib_texcoord;
        attrib_texcoord.index = texcoord_index;
        attrib_texcoord.size = 2;
        attrib_texcoord.type = GL_FLOAT;
        attrib_texcoord.normalized = GL_FALSE;
        attrib_texcoord.stride = data.size() * sizeof(GLfloat);
        attrib_texcoord.offset = 3;

        attribs.push_back(attrib_position);
        attribs.push_back(attrib_texcoord);
    }

    Vertex_Position_Texcoord(std::array<GLfloat, 3> position, 
                             std::array<GLfloat, 2> texcoord,
                             GLuint shader_program, 
                             const char* position_name = "vs_position", 
                             const char* texcoord_name = "vs_texcoord") : Vertex_Position_Texcoord(position, texcoord)
    {
        attribs[0].index = glGetAttribLocation(shader_program, position_name);
        attribs[1].index = glGetAttribLocation(shader_program, texcoord_name);
    }
};

struct Vertex_Position_Normal : public Vertex
{
    Vertex_Position_Normal(std::array<GLfloat, 3> position, 
                           std::array<GLfloat, 3> normal, 
                           GLuint position_index = 0,
                           GLuint normal_index = 1)
    {
        type = VERTEX_TYPE_POSITION_NORMAL;

        data = std::vector<GLfloat>();
        data.insert(data.end(), position.begin(), position.end());
        data.insert(data.end(), normal.begin(), normal.end());

        Vertex_Attrib attrib_position;
        attrib_position.index = position_index;
        attrib_position.size = 3;
        attrib_position.type = GL_FLOAT;
        attrib_position.normalized = GL_FALSE;
        attrib_position.stride = data.size() * sizeof(GLfloat);
        attrib_position.offset = 0;

        Vertex_Attrib attrib_normal;
        attrib_normal.index = normal_index;
        attrib_normal.size = 3;
        attrib_normal.type = GL_FLOAT;
        attrib_normal.normalized = GL_FALSE;
        attrib_normal.stride = data.size() * sizeof(GLfloat);
        attrib_normal.offset = 3;

        attribs.push_back(attrib_position);
        attribs.push_back(attrib_normal);
    }

    Vertex_Position_Normal(std::array<GLfloat, 3> position, 
                           std::array<GLfloat, 3> normal, 
                           GLuint shader_program, 
                           const char* position_name = "vs_position", 
                           const char* normal_name = "vs_normal") : Vertex_Position_Normal(position, normal)
    {
        attribs[0].index = glGetAttribLocation(shader_program, position_name);
        attribs[1].index = glGetAttribLocation(shader_program, normal_name);
    }
};

struct Vertex_Position_Normal_Texcoord : public Vertex
{
    Vertex_Position_Normal_Texcoord(std::array<GLfloat, 3> position, 
                                    std::array<GLfloat, 3> normal,
                                    std::array<GLfloat, 2> texcoord,
                                    GLuint position_index = 0,
                                    GLuint normal_index = 1,
                                    GLuint texcoord_index = 2)
    {
        type = VERTEX_TYPE_POSITION_NORMAL_TEXCOORD;

        data = std::vector<GLfloat>();
        data.insert(data.end(), position.begin(), position.end());
        data.insert(data.end(), normal.begin(), normal.end());
        data.insert(data.end(), texcoord.begin(), texcoord.end());

        Vertex_Attrib attrib_position;
        attrib_position.index = position_index;
        attrib_position.size = 3;
        attrib_position.type = GL_FLOAT;
        attrib_position.normalized = GL_FALSE;
        attrib_position.stride = data.size() * sizeof(GLfloat);
        attrib_position.offset = 0;

        Vertex_Attrib attrib_normal;
        attrib_normal.index = normal_index;
        attrib_normal.size = 3;
        attrib_normal.type = GL_FLOAT;
        attrib_normal.normalized = GL_FALSE;
        attrib_normal.stride = data.size() * sizeof(GLfloat);
        attrib_normal.offset = 3; // skip position

        Vertex_Attrib attrib_texcoord;
        attrib_texcoord.index = texcoord_index;
        attrib_texcoord.size = 2;
        attrib_texcoord.type = GL_FLOAT;
        attrib_texcoord.normalized = GL_FALSE;
        attrib_texcoord.stride = data.size() * sizeof(GLfloat);
        attrib_texcoord.offset = 6; // skip position and normal
        
        attribs.push_back(attrib_position);
        attribs.push_back(attrib_normal);
        attribs.push_back(attrib_texcoord);
    }

    Vertex_Position_Normal_Texcoord(std::array<GLfloat, 3> position, 
                                    std::array<GLfloat, 3> normal,
                                    std::array<GLfloat, 2> texcoord,
                                    GLuint shader_program, 
                                    const char* position_name = "vs_position", 
                                    const char* normal_name = "vs_normal", 
                                    const char* texcoord_name = "vs_texcoord") : Vertex_Position_Normal_Texcoord(position, normal, texcoord)
    {
        attribs[0].index = glGetAttribLocation(shader_program, position_name);
        attribs[1].index = glGetAttribLocation(shader_program, normal_name);
        attribs[2].index = glGetAttribLocation(shader_program, texcoord_name);
    }
};
