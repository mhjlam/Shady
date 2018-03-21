#pragma once

struct Vertex_Attrib
{
    GLuint index;
    GLint size;             // 1, 2, 3, 4 or GL_BGRA
    GLenum type;            // e.g. GL_BYTE, GL_SHORT, GL_INT, GL_FLOAT, GL_DOUBLE
    GLboolean normalized;   // GL_TRUE or GL_FALSE
    GLsizei stride;
    GLsizei offset;         // offset to the first component of this vertex attribute
};
