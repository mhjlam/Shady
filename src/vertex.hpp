#pragma once

#include <vector>
#include <algorithm>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Shader;

enum Vertex_Type
{
    VERTEX_TYPE_UNDEFINED,

    VERTEX_TYPE_POSITION_2D,
    VERTEX_TYPE_POSITION_COLOR_2D,
    VERTEX_TYPE_POSITION_TEXCOORD_2D,
    VERTEX_TYPE_POSITION_TEXCOORD_COLOR_2D,

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

    GLint data_size = 0;
    GLfloat* data = nullptr;

    GLint attribs_size = 0;
    Vertex_Attrib* attribs = nullptr;

    virtual ~Vertex()
    {
        delete[] data;
        delete[] attribs;
    }
};

// 2D
struct Vertex2_Position : public Vertex
{
    Vertex2_Position(GLfloat position[2], 
                     GLuint position_index = 0)
    {
        type = VERTEX_TYPE_POSITION_2D;

        data_size = 2;
        data = new GLfloat[data_size];
        std::copy(position, position + 2, data);

        attribs_size = 1;
        attribs = new Vertex_Attrib[attribs_size];

        // position
        attribs[0].index = position_index;
        attribs[0].size = 2;
        attribs[0].type = GL_FLOAT;
        attribs[0].normalized = GL_FALSE;
        attribs[0].stride = 2 * sizeof(GLfloat);
        attribs[0].offset = 0;
    }

    Vertex2_Position(GLfloat position[2], 
                     GLuint shader_program, 
                     const char* position_name = "vs_position") : Vertex2_Position(position)
    {
        attribs[0].index = glGetAttribLocation(shader_program, position_name);
    }
};

struct Vertex2_Position_Color : public Vertex
{
    Vertex2_Position_Color(GLfloat position[2], GLfloat color[3], 
                           GLuint position_index = 0, GLuint color_index = 1)
    {
        type = VERTEX_TYPE_POSITION_COLOR_2D;
        
        data_size = 5;
        data = new GLfloat[data_size];
        std::copy(position, position + 2, data);
        std::copy(color, color + 3, data + 2);

        attribs_size = 2;
        attribs = new Vertex_Attrib[attribs_size];

        attribs[0].index = position_index;
        attribs[0].size = 2;
        attribs[0].type = GL_FLOAT;
        attribs[0].normalized = GL_FALSE;
        attribs[0].stride = 2 * sizeof(GLfloat);
        attribs[0].offset = 0;

        attribs[1].index = color_index;
        attribs[1].size = 3;
        attribs[1].type = GL_FLOAT;
        attribs[1].normalized = GL_FALSE;
        attribs[1].stride = 3 * sizeof(GLfloat);
        attribs[1].offset = 2; // skip position elements
    }

    Vertex2_Position_Color(GLfloat position[2], GLfloat color[3], 
                           GLuint shader_program, 
                           const char* position_name = "vs_position", 
                           const char* color_name = "vs_color") : Vertex2_Position_Color(position, color)
    {
        attribs[0].index = glGetAttribLocation(shader_program, position_name);
        attribs[1].index = glGetAttribLocation(shader_program, color_name);
    }
};

struct Vertex2_Position_Texcoord : public Vertex
{
    Vertex2_Position_Texcoord(GLfloat position[2], GLfloat texcoord[2], 
                              GLuint position_index = 0, GLuint texcoord_index = 1)
    {
        type = VERTEX_TYPE_POSITION_TEXCOORD_2D;

        data_size = 4;
        data = new GLfloat[data_size];
        std::copy(position, position + 2, data);
        std::copy(texcoord, texcoord + 2, data + 2);

        attribs_size = 2;
        attribs = new Vertex_Attrib[attribs_size];

        attribs[0].index = position_index;
        attribs[0].size = 2;
        attribs[0].type = GL_FLOAT;
        attribs[0].normalized = GL_FALSE;
        attribs[0].stride = 2 * sizeof(GLfloat);
        attribs[0].offset = 0;

        attribs[1].index = texcoord_index;
        attribs[1].size = 2;
        attribs[1].type = GL_FLOAT;
        attribs[1].normalized = GL_FALSE;
        attribs[1].stride = 2 * sizeof(GLfloat);
        attribs[1].offset = 2;
    }

    Vertex2_Position_Texcoord(GLfloat position[2], GLfloat texcoord[2],
                              GLuint shader_program, 
                              const char* position_name = "vs_position", 
                              const char* texcoord_name = "vs_texcoord") : Vertex2_Position_Texcoord(position, texcoord)
    {
        attribs[0].index = glGetAttribLocation(shader_program, position_name);
        attribs[1].index = glGetAttribLocation(shader_program, texcoord_name);
    }
};

struct Vertex2_Position_Texcoord_Color : public Vertex
{
    Vertex2_Position_Texcoord_Color(GLfloat position[2], GLfloat texcoord[2], GLfloat color[3], 
                                    GLuint position_index = 0, GLuint texcoord_index = 1, GLuint color_index = 2)
    {
        type = VERTEX_TYPE_POSITION_TEXCOORD_COLOR_2D;

        data_size = 7;
        data = new GLfloat[data_size];
        std::copy(position, position + 2, data);
        std::copy(texcoord, texcoord + 2, data + 2);
        std::copy(color, color + 3, data + 4);

        attribs_size = 3;
        attribs = new Vertex_Attrib[attribs_size];

        attribs[0].index = position_index;
        attribs[0].size = 2;
        attribs[0].type = GL_FLOAT;
        attribs[0].normalized = GL_FALSE;
        attribs[0].stride = 2 * sizeof(GLfloat);
        attribs[0].offset = 0;

        attribs[1].index = texcoord_index;
        attribs[1].size = 2;
        attribs[1].type = GL_FLOAT;
        attribs[1].normalized = GL_FALSE;
        attribs[1].stride = 2 * sizeof(GLfloat);
        attribs[1].offset = 2;

        attribs[2].index = color_index;
        attribs[2].size = 3;
        attribs[2].type = GL_FLOAT;
        attribs[2].normalized = GL_FALSE;
        attribs[2].stride = 3 * sizeof(GLfloat);
        attribs[2].offset = 4; // skip position and texcoord
    }
    
    Vertex2_Position_Texcoord_Color(GLfloat position[2], GLfloat texcoord[2], GLfloat color[3], 
                                    GLuint shader_program, 
                                    const char* position_name = "vs_position", 
                                    const char* texcoord_name = "vs_texcoord", 
                                    const char* color_name = "vs_color") : Vertex2_Position_Texcoord_Color(position, texcoord, color)
    {
        attribs[0].index = glGetAttribLocation(shader_program, position_name);
        attribs[1].index = glGetAttribLocation(shader_program, texcoord_name);
        attribs[2].index = glGetAttribLocation(shader_program, color_name);
    }
};

// 3D
struct Vertex_Position : public Vertex
{
    Vertex_Position(GLfloat position[3], 
                    GLuint position_index = 0)
    {
        type = VERTEX_TYPE_POSITION;

        data_size = 3;
        data = new GLfloat[data_size];
        std::copy(position, position + 3, data);

        attribs_size = 1;
        attribs = new Vertex_Attrib[attribs_size];

        // position
        attribs[0].index = position_index;
        attribs[0].size = 3;
        attribs[0].type = GL_FLOAT;
        attribs[0].normalized = GL_FALSE;
        attribs[0].stride = 3 * sizeof(GLfloat);
        attribs[0].offset = 0;
    }

    Vertex_Position(GLfloat position[2], 
                    GLuint shader_program, 
                    const char* position_name = "vs_position") : Vertex_Position(position)
    {
        attribs[0].index = glGetAttribLocation(shader_program, position_name);
    }
};

struct Vertex_Position_Color : public Vertex
{
    Vertex_Position_Color(GLfloat position[3], GLfloat color[3], 
                          GLuint position_index = 0, GLuint color_index = 1)
    {
        type = VERTEX_TYPE_POSITION_COLOR;

        data_size = 6;
        data = new GLfloat[data_size];
        std::copy(position, position + 3, data);
        std::copy(color, color + 3, data + 3);

        attribs_size = 2;
        attribs = new Vertex_Attrib[attribs_size];

        attribs[0].index = position_index;
        attribs[0].size = 3;
        attribs[0].type = GL_FLOAT;
        attribs[0].normalized = GL_FALSE;
        attribs[0].stride = 3 * sizeof(GLfloat);
        attribs[0].offset = 0;

        attribs[1].index = color_index;
        attribs[1].size = 3;
        attribs[1].type = GL_FLOAT;
        attribs[1].normalized = GL_FALSE;
        attribs[1].stride = 3 * sizeof(GLfloat);
        attribs[1].offset = 3;
    }

    Vertex_Position_Color(GLfloat position[3], GLfloat color[3], 
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
    Vertex_Position_Texcoord(GLfloat position[3], GLfloat texcoord[2], 
                             GLuint position_index = 0, GLuint texcoord_index = 1)
    {
        type = VERTEX_TYPE_POSITION_TEXCOORD;

        data_size = 5;
        data = new GLfloat[data_size];
        std::copy(position, position + 3, data);
        std::copy(texcoord, texcoord + 2, data + 3);

        attribs_size = 2;
        attribs = new Vertex_Attrib[attribs_size];

        attribs[0].index = position_index;
        attribs[0].size = 3;
        attribs[0].type = GL_FLOAT;
        attribs[0].normalized = GL_FALSE;
        attribs[0].stride = 3 * sizeof(GLfloat);
        attribs[0].offset = 0;

        attribs[1].index = texcoord_index;
        attribs[1].size = 2;
        attribs[1].type = GL_FLOAT;
        attribs[1].normalized = GL_FALSE;
        attribs[1].stride = 2 * sizeof(GLfloat);
        attribs[1].offset = 3;
    }

    Vertex_Position_Texcoord(GLfloat position[3], GLfloat texcoord[2],
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
    Vertex_Position_Normal(GLfloat position[3], GLfloat normal[3], 
                           GLuint position_index = 0, GLuint normal_index = 1)
    {
        type = VERTEX_TYPE_POSITION_NORMAL;

        data_size = 6;
        data = new GLfloat[data_size];
        std::copy(position, position + 3, data);
        std::copy(normal, normal + 3, data + 3);

        attribs_size = 2;
        attribs = new Vertex_Attrib[attribs_size];

        attribs[0].index = position_index;
        attribs[0].size = 3;
        attribs[0].type = GL_FLOAT;
        attribs[0].normalized = GL_FALSE;
        attribs[0].stride = 3 * sizeof(GLfloat);
        attribs[0].offset = 0;

        attribs[1].index = normal_index;
        attribs[1].size = 3;
        attribs[1].type = GL_FLOAT;
        attribs[1].normalized = GL_FALSE;
        attribs[1].stride = 3 * sizeof(GLfloat);
        attribs[1].offset = 3;
    }

    Vertex_Position_Normal(GLfloat position[3], GLfloat normal[3], 
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
    Vertex_Position_Normal_Texcoord(GLfloat position[3], GLfloat normal[3], GLfloat texcoord[2] ,
                                    GLuint position_index = 0, GLuint normal_index = 1, GLuint texcoord_index = 2)
    {
        type = VERTEX_TYPE_POSITION_NORMAL_TEXCOORD;

        data_size = 8;
        data = new GLfloat[data_size];
        std::copy(position, position + 3, data);
        std::copy(normal, normal + 3, data + 3);
        std::copy(texcoord, texcoord + 2, data + 6);

        attribs_size = 3;
        attribs = new Vertex_Attrib[attribs_size];

        attribs[0].index = position_index;
        attribs[0].size = 3;
        attribs[0].type = GL_FLOAT;
        attribs[0].normalized = GL_FALSE;
        attribs[0].stride = 3 * sizeof(GLfloat);
        attribs[0].offset = 0;

        attribs[1].index = normal_index;
        attribs[1].size = 3;
        attribs[1].type = GL_FLOAT;
        attribs[1].normalized = GL_FALSE;
        attribs[1].stride = 3 * sizeof(GLfloat);
        attribs[1].offset = 3; // skip position

        attribs[2].index = texcoord_index;
        attribs[2].size = 2;
        attribs[2].type = GL_FLOAT;
        attribs[2].normalized = GL_FALSE;
        attribs[2].stride = 2 * sizeof(GLfloat);
        attribs[2].offset = 6; // skip position and normal
    }

    Vertex_Position_Normal_Texcoord(GLfloat position[3], GLfloat normal[3], GLfloat texcoord[2],
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
