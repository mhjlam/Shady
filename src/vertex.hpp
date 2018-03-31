#pragma once

#include "glad/glad.h"
#include <GLFW/glfw3.h>

struct Vertex_Attrib
{
    GLuint index;
    GLint size;             // 1, 2, 3, 4 or GL_BGRA
    GLenum type;            // e.g. GL_BYTE, GL_SHORT, GL_INT, GL_FLOAT, GL_DOUBLE
    GLboolean normalized;   // GL_TRUE or GL_FALSE
    GLsizei stride;
    GLsizei offset;         // offset to the first component of this vertex attribute
};

struct Vertex { };

// 2D
struct Vertex2_Position : public Vertex
{
    GLfloat positions[2];
};

struct Vertex2_Position_Color : public Vertex
{
    GLfloat positions[2];
    GLfloat color[3];
};

struct Vertex2_Position_Texcoord : public Vertex
{
    GLfloat positions[2];
    GLfloat texcoord[2];
};

struct Vertex2_Position_Texcoord_Color : public Vertex
{
    GLfloat positions[2];
    GLfloat texcoord[2];
    GLfloat color[3];
};

// 3D
struct Vertex_Position : public Vertex
{
    GLfloat positions[3];
};

struct Vertex_Position_Color : public Vertex
{
    GLfloat positions[3];
    GLfloat color[3];
};

struct Vertex_Position_Texcoord : public Vertex
{
    GLfloat positions[3];
    GLfloat texcoord[2];
};

struct Vertex_Position_Normal : public Vertex
{
    GLfloat positions[3];
    GLfloat normal[3];
};

struct Vertex_Position_Normal_Texcoord : public Vertex
{
    GLfloat positions[3];
    GLfloat normal[3];
    GLfloat texcoord[2];
};
