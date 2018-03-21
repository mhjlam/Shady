#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct Vertex {};

// 2D
struct Vertex2_Position : Vertex
{
    GLfloat positions[2];
};

struct Vertex2_Position_Color : Vertex
{
    GLfloat positions[2];
    GLfloat color[3];
};

struct Vertex2_Position_Texcoord : Vertex
{
    GLfloat positions[2];
    GLfloat texcoord[2];
};

struct Vertex2_Position_Texcoord_Color : Vertex
{
    GLfloat positions[2];
    GLfloat texcoord[2];
    GLfloat color[3];
};

// 3D
struct Vertex_Position : Vertex
{
    GLfloat positions[3];
};

struct Vertex_Position_Color : Vertex
{
    GLfloat positions[3];
    GLfloat color[3];
};

struct Vertex_Position_Texcoord : Vertex
{
    GLfloat positions[3];
    GLfloat texcoord[2];
};

struct Vertex_Position_Normal : Vertex
{
    GLfloat positions[3];
    GLfloat normal[3];
};

struct Vertex_Position_Normal_Texcoord : Vertex
{
    GLfloat positions[3];
    GLfloat normal[3];
    GLfloat texcoord[2];
};
