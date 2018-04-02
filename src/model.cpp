#include "model.hpp"

Model::Model(std::vector<GLfloat> vertices, int index_count, GLuint shader_program, GLenum mode, GLenum type)
: topology(mode), index_count(index_count), index_type(type)
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vertex_buffer;
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices.front(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, vertices.size() / index_count, GL_FLOAT, GL_FALSE, 0, 0);

    glBindVertexArray(0);
}

Model::Model(std::vector<GLfloat> vertices, std::vector<GLuint> indices, GLuint shader_program, GLenum mode, GLenum type)
: topology(mode), index_count(indices.size()), index_type(type)
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vertex_buffer;
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices.front(), GL_STATIC_DRAW);

    GLuint index_buffer;
    glGenBuffers(1, &index_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices.front(), GL_STATIC_DRAW);

    // TODO: vertex attributes should be set based on description of input vertex array

    GLint position_attrib = glGetAttribLocation(shader_program, "position");
    glEnableVertexAttribArray(position_attrib);
    glVertexAttribPointer(position_attrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), 0);

    GLint color_attrib = glGetAttribLocation(shader_program, "color");
    glEnableVertexAttribArray(color_attrib);
    glVertexAttribPointer(color_attrib, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));

    GLint texcoord_attrib = glGetAttribLocation(shader_program, "texcoord");
    glEnableVertexAttribArray(texcoord_attrib);
    glVertexAttribPointer(texcoord_attrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void*)(5 * sizeof(GLfloat)));

    glBindVertexArray(0);
}
