#pragma once

#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Shader;

struct Vertex_Attrib
{
    GLfloat* data;

    GLuint index;
    GLint size;             // 1, 2, 3, 4 or GL_BGRA
    GLenum type;            // e.g. GL_BYTE, GL_SHORT, GL_INT, GL_FLOAT, GL_DOUBLE
    GLboolean normalized;   // GL_TRUE or GL_FALSE
    GLsizei stride;
    GLsizei offset;         // offset to the first component of this vertex attribute
};

struct Vertex
{
    Vertex_Attrib* attribs;
};

// 2D
struct Vertex2_Position : public Vertex
{
    Vertex2_Position(GLfloat position[2], 
                     GLuint position_index = 0)
    {
        attribs = new Vertex_Attrib[1];

        // position
        attribs[0].data = position;
        attribs[0].index = position_index;
        attribs[0].size = 2;
        attribs[0].type = GL_FLOAT;
        attribs[0].normalized = GL_FALSE;
        attribs[0].stride = 2 * sizeof(GLfloat);
        attribs[0].offset = 0;
    }

    Vertex2_Position(GLfloat position[2], GLuint shader_program, const char* position_name = "vs_position")
    {
        attribs = new Vertex_Attrib[1];

        // position
        attribs[0].data = position;
        attribs[0].index = glGetAttribLocation(shader_program, position_name);
        attribs[0].size = 2;
        attribs[0].type = GL_FLOAT;
        attribs[0].normalized = GL_FALSE;
        attribs[0].stride = 2 * sizeof(GLfloat);
        attribs[0].offset = 0;
    }

    ~Vertex2_Position()
    {
        delete[] attribs;
    }
};

struct Vertex2_Position_Color : public Vertex
{
    Vertex2_Position_Color(GLfloat position[2], GLfloat color[3], 
                           GLuint position_index = 0, GLuint color_index = 1)
    {
        attribs = new Vertex_Attrib[2];

        attribs[0].data = position;
        attribs[0].index = position_index;
        attribs[0].size = 2;
        attribs[0].type = GL_FLOAT;
        attribs[0].normalized = GL_FALSE;
        attribs[0].stride = 2 * sizeof(GLfloat);
        attribs[0].offset = 0;

        attribs[1].data = color;
        attribs[1].index = color_index;
        attribs[1].size = 3;
        attribs[1].type = GL_FLOAT;
        attribs[1].normalized = GL_FALSE;
        attribs[1].stride = 3 * sizeof(GLfloat);
        attribs[1].offset = 2; // skip position elements
    }

    Vertex2_Position_Color(GLfloat position[2], GLfloat color[3], 
        GLuint shader_program, const char* position_name = "vs_position", const char* color_name = "vs_color")
    {
        attribs = new Vertex_Attrib[2];

        attribs[0].data = position;
        attribs[0].index = glGetAttribLocation(shader_program, position_name);
        attribs[0].size = 2;
        attribs[0].type = GL_FLOAT;
        attribs[0].normalized = GL_FALSE;
        attribs[0].stride = 2 * sizeof(GLfloat);
        attribs[0].offset = 0;

        attribs[1].data = color;
        attribs[1].index = glGetAttribLocation(shader_program, color_name);
        attribs[1].size = 3;
        attribs[1].type = GL_FLOAT;
        attribs[1].normalized = GL_FALSE;
        attribs[1].stride = 3 * sizeof(GLfloat);
        attribs[1].offset = 2;
    }

    ~Vertex2_Position_Color()
    {
        delete[] attribs;
    }
};

struct Vertex2_Position_Texcoord : public Vertex
{
    Vertex2_Position_Texcoord(GLfloat position[2], GLfloat texcoord[2], 
                              GLuint position_index = 0, GLuint texcoord_index = 1)
    {
        attribs = new Vertex_Attrib[2];

        attribs[0].data = position;
        attribs[0].index = position_index;
        attribs[0].size = 2;
        attribs[0].type = GL_FLOAT;
        attribs[0].normalized = GL_FALSE;
        attribs[0].stride = 2 * sizeof(GLfloat);
        attribs[0].offset = 0;

        attribs[1].data = texcoord;
        attribs[1].index = texcoord_index;
        attribs[1].size = 2;
        attribs[1].type = GL_FLOAT;
        attribs[1].normalized = GL_FALSE;
        attribs[1].stride = 2 * sizeof(GLfloat);
        attribs[1].offset = 2;
    }

    Vertex2_Position_Texcoord(GLfloat position[2], GLfloat texcoord[2],
        GLuint shader_program, const char* position_name = "vs_position", const char* texcoord_name = "vs_texcoord")
    {
        attribs = new Vertex_Attrib[2];

        attribs[0].data = position;
        attribs[0].index = glGetAttribLocation(shader_program, position_name);
        attribs[0].size = 2;
        attribs[0].type = GL_FLOAT;
        attribs[0].normalized = GL_FALSE;
        attribs[0].stride = 2 * sizeof(GLfloat);
        attribs[0].offset = 0;

        attribs[1].data = texcoord;
        attribs[1].index = glGetAttribLocation(shader_program, texcoord_name);
        attribs[1].size = 2;
        attribs[1].type = GL_FLOAT;
        attribs[1].normalized = GL_FALSE;
        attribs[1].stride = 2 * sizeof(GLfloat);
        attribs[1].offset = 2;
    }

    ~Vertex2_Position_Texcoord()
    {
        delete[] attribs;
    }
};

struct Vertex2_Position_Texcoord_Color : public Vertex
{
    Vertex2_Position_Texcoord_Color(GLfloat position[2], GLfloat texcoord[2], GLfloat color[3], 
                                    GLuint position_index = 0, GLuint texcoord_index = 1, GLuint color_index = 2)
    {
        attribs = new Vertex_Attrib[3];

        attribs[0].data = position;
        attribs[0].index = position_index;
        attribs[0].size = 2;
        attribs[0].type = GL_FLOAT;
        attribs[0].normalized = GL_FALSE;
        attribs[0].stride = 2 * sizeof(GLfloat);
        attribs[0].offset = 0;

        attribs[1].data = texcoord;
        attribs[1].index = texcoord_index;
        attribs[1].size = 2;
        attribs[1].type = GL_FLOAT;
        attribs[1].normalized = GL_FALSE;
        attribs[1].stride = 2 * sizeof(GLfloat);
        attribs[1].offset = 2;

        attribs[2].data = color;
        attribs[2].index = color_index;
        attribs[2].size = 3;
        attribs[2].type = GL_FLOAT;
        attribs[2].normalized = GL_FALSE;
        attribs[2].stride = 3 * sizeof(GLfloat);
        attribs[2].offset = 4; // skip position and texcoord
    }
    
    Vertex2_Position_Texcoord_Color(GLfloat position[2], GLfloat texcoord[2], GLfloat color[3], 
        GLuint shader_program, const char* position_name = "vs_position", const char* texcoord_name = "vs_texcoord", const char* color_name = "vs_color")
    {
        attribs = new Vertex_Attrib[3];

        attribs[0].data = position;
        attribs[0].index = glGetAttribLocation(shader_program, position_name);
        attribs[0].size = 2;
        attribs[0].type = GL_FLOAT;
        attribs[0].normalized = GL_FALSE;
        attribs[0].stride = 2 * sizeof(GLfloat);
        attribs[0].offset = 0;

        attribs[1].data = texcoord;
        attribs[1].index = glGetAttribLocation(shader_program, texcoord_name);
        attribs[1].size = 2;
        attribs[1].type = GL_FLOAT;
        attribs[1].normalized = GL_FALSE;
        attribs[1].stride = 2 * sizeof(GLfloat);
        attribs[1].offset = 2;

        attribs[2].data = color;
        attribs[2].index = glGetAttribLocation(shader_program, color_name);
        attribs[2].size = 3;
        attribs[2].type = GL_FLOAT;
        attribs[2].normalized = GL_FALSE;
        attribs[2].stride = 3 * sizeof(GLfloat);
        attribs[2].offset = 4;
    }

    ~Vertex2_Position_Texcoord_Color()
    {
        delete[] attribs;
    }
};

// 3D
struct Vertex_Position : public Vertex
{
    Vertex_Position(GLfloat position[3], 
                     GLuint position_index = 0)
    {
        attribs = new Vertex_Attrib[1];

        // position
        attribs[0].data = position;
        attribs[0].index = position_index;
        attribs[0].size = 3;
        attribs[0].type = GL_FLOAT;
        attribs[0].normalized = GL_FALSE;
        attribs[0].stride = 3 * sizeof(GLfloat);
        attribs[0].offset = 0;
    }

    Vertex_Position(GLfloat position[2], GLuint shader_program, const char* position_name = "vs_position")
    {
        attribs = new Vertex_Attrib[1];

        // position
        attribs[0].data = position;
        attribs[0].index = glGetAttribLocation(shader_program, position_name);
        attribs[0].size = 3;
        attribs[0].type = GL_FLOAT;
        attribs[0].normalized = GL_FALSE;
        attribs[0].stride = 3 * sizeof(GLfloat);
        attribs[0].offset = 0;
    }

    ~Vertex_Position()
    {
        delete[] attribs;
    }
};

struct Vertex_Position_Color : public Vertex
{
    Vertex_Position_Color(GLfloat position[3], GLfloat color[3], 
                           GLuint position_index = 0, GLuint color_index = 1)
    {
        attribs = new Vertex_Attrib[2];

        attribs[0].data = position;
        attribs[0].index = position_index;
        attribs[0].size = 3;
        attribs[0].type = GL_FLOAT;
        attribs[0].normalized = GL_FALSE;
        attribs[0].stride = 3 * sizeof(GLfloat);
        attribs[0].offset = 0;

        attribs[1].data = color;
        attribs[1].index = color_index;
        attribs[1].size = 3;
        attribs[1].type = GL_FLOAT;
        attribs[1].normalized = GL_FALSE;
        attribs[1].stride = 3 * sizeof(GLfloat);
        attribs[1].offset = 3;
    }

    Vertex_Position_Color(GLfloat position[3], GLfloat color[3], 
        GLuint shader_program, const char* position_name = "vs_position", const char* color_name = "vs_color")
    {
        attribs = new Vertex_Attrib[2];

        attribs[0].data = position;
        attribs[0].index = glGetAttribLocation(shader_program, position_name);
        attribs[0].size = 3;
        attribs[0].type = GL_FLOAT;
        attribs[0].normalized = GL_FALSE;
        attribs[0].stride = 3 * sizeof(GLfloat);
        attribs[0].offset = 0;

        attribs[1].data = color;
        attribs[1].index = glGetAttribLocation(shader_program, color_name);
        attribs[1].size = 3;
        attribs[1].type = GL_FLOAT;
        attribs[1].normalized = GL_FALSE;
        attribs[1].stride = 3 * sizeof(GLfloat);
        attribs[1].offset = 3;
    }

    ~Vertex_Position_Color()
    {
        delete[] attribs;
    }
};

struct Vertex_Position_Texcoord : public Vertex
{
    Vertex_Position_Texcoord(GLfloat position[3], GLfloat texcoord[2], 
                              GLuint position_index = 0, GLuint texcoord_index = 1)
    {
        attribs = new Vertex_Attrib[2];

        attribs[0].data = position;
        attribs[0].index = position_index;
        attribs[0].size = 3;
        attribs[0].type = GL_FLOAT;
        attribs[0].normalized = GL_FALSE;
        attribs[0].stride = 3 * sizeof(GLfloat);
        attribs[0].offset = 0;

        attribs[1].data = texcoord;
        attribs[1].index = texcoord_index;
        attribs[1].size = 2;
        attribs[1].type = GL_FLOAT;
        attribs[1].normalized = GL_FALSE;
        attribs[1].stride = 2 * sizeof(GLfloat);
        attribs[1].offset = 3;
    }

    Vertex_Position_Texcoord(GLfloat position[3], GLfloat texcoord[2],
        GLuint shader_program, const char* position_name = "vs_position", const char* texcoord_name = "vs_texcoord")
    {
        attribs = new Vertex_Attrib[2];

        attribs[0].data = position;
        attribs[0].index = glGetAttribLocation(shader_program, position_name);
        attribs[0].size = 3;
        attribs[0].type = GL_FLOAT;
        attribs[0].normalized = GL_FALSE;
        attribs[0].stride = 3 * sizeof(GLfloat);
        attribs[0].offset = 0;

        attribs[1].data = texcoord;
        attribs[1].index = glGetAttribLocation(shader_program, texcoord_name);
        attribs[1].size = 2;
        attribs[1].type = GL_FLOAT;
        attribs[1].normalized = GL_FALSE;
        attribs[1].stride = 2 * sizeof(GLfloat);
        attribs[1].offset = 3;
    }

    ~Vertex_Position_Texcoord()
    {
        delete[] attribs;
    }
};

struct Vertex_Position_Normal : public Vertex
{
    Vertex_Position_Normal(GLfloat position[3], GLfloat normal[3], 
                           GLuint position_index = 0, GLuint normal_index = 1)
    {
        attribs = new Vertex_Attrib[2];

        attribs[0].data = position;
        attribs[0].index = position_index;
        attribs[0].size = 3;
        attribs[0].type = GL_FLOAT;
        attribs[0].normalized = GL_FALSE;
        attribs[0].stride = 3 * sizeof(GLfloat);
        attribs[0].offset = 0;

        attribs[1].data = normal;
        attribs[1].index = normal_index;
        attribs[1].size = 3;
        attribs[1].type = GL_FLOAT;
        attribs[1].normalized = GL_FALSE;
        attribs[1].stride = 3 * sizeof(GLfloat);
        attribs[1].offset = 3;
    }

    Vertex_Position_Normal(GLfloat position[3], GLfloat normal[3], 
        GLuint shader_program, const char* position_name = "vs_position", const char* normal_name = "vs_normal")
    {
        attribs = new Vertex_Attrib[2];

        attribs[0].data = position;
        attribs[0].index = glGetAttribLocation(shader_program, position_name);
        attribs[0].size = 3;
        attribs[0].type = GL_FLOAT;
        attribs[0].normalized = GL_FALSE;
        attribs[0].stride = 3 * sizeof(GLfloat);
        attribs[0].offset = 0;

        attribs[1].data = normal;
        attribs[1].index = glGetAttribLocation(shader_program, normal_name);
        attribs[1].size = 3;
        attribs[1].type = GL_FLOAT;
        attribs[1].normalized = GL_FALSE;
        attribs[1].stride = 3 * sizeof(GLfloat);
        attribs[1].offset = 3;
    }

    ~Vertex_Position_Normal()
    {
        delete[] attribs;
    }
};

struct Vertex_Position_Normal_Texcoord : public Vertex
{
    Vertex_Position_Normal_Texcoord(GLfloat position[3], GLfloat normal[3], GLfloat texcoord[2] ,
                           GLuint position_index = 0, GLuint normal_index = 1, GLuint texcoord_index = 2)
    {
        attribs = new Vertex_Attrib[3];

        attribs[0].data = position;
        attribs[0].index = position_index;
        attribs[0].size = 3;
        attribs[0].type = GL_FLOAT;
        attribs[0].normalized = GL_FALSE;
        attribs[0].stride = 3 * sizeof(GLfloat);
        attribs[0].offset = 0;

        attribs[1].data = normal;
        attribs[1].index = normal_index;
        attribs[1].size = 3;
        attribs[1].type = GL_FLOAT;
        attribs[1].normalized = GL_FALSE;
        attribs[1].stride = 3 * sizeof(GLfloat);
        attribs[1].offset = 3; // skip position

        attribs[2].data = texcoord;
        attribs[2].index = texcoord_index;
        attribs[2].size = 2;
        attribs[2].type = GL_FLOAT;
        attribs[2].normalized = GL_FALSE;
        attribs[2].stride = 2 * sizeof(GLfloat);
        attribs[2].offset = 6; // skip position and normal
    }

    Vertex_Position_Normal_Texcoord(GLfloat position[3], GLfloat normal[3], GLfloat texcoord[2],
        GLuint shader_program, const char* position_name = "vs_position", const char* normal_name = "vs_normal", const char* texcoord_name = "vs_texcoord")
    {
        attribs = new Vertex_Attrib[3];

        attribs[0].data = position;
        attribs[0].index = glGetAttribLocation(shader_program, position_name);
        attribs[0].size = 3;
        attribs[0].type = GL_FLOAT;
        attribs[0].normalized = GL_FALSE;
        attribs[0].stride = 3 * sizeof(GLfloat);
        attribs[0].offset = 0;

        attribs[1].data = normal;
        attribs[0].index = glGetAttribLocation(shader_program, normal_name);
        attribs[1].size = 3;
        attribs[1].type = GL_FLOAT;
        attribs[1].normalized = GL_FALSE;
        attribs[1].stride = 3 * sizeof(GLfloat);
        attribs[1].offset = 3;

        attribs[2].data = texcoord;
        attribs[0].index = glGetAttribLocation(shader_program, texcoord_name);
        attribs[2].size = 2;
        attribs[2].type = GL_FLOAT;
        attribs[2].normalized = GL_FALSE;
        attribs[2].stride = 2 * sizeof(GLfloat);
        attribs[2].offset = 6;
    }

    ~Vertex_Position_Normal_Texcoord()
    {
        delete[] attribs;
    }
};
