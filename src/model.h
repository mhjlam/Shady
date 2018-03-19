#pragma once

#include <vector>
#include <memory>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Mesh;
class Shader;
class Texture;

class Model
{
friend class Renderer;

private:
    GLuint vao;

    // std::shared_ptr<Mesh> mesh;
    // std::shared_ptr<Shader> shader;
    // std::shared_ptr<Texture> texture;

public:
    GLenum topology;        // GL_POINTS,
                            // GL_LINE_STRIP, GL_LINE_LOOP, GL_LINES,
                            // GL_LINE_STRIP_ADJACENCY, GL_LINES_ADJACENCY,
                            // GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN, GL_TRIANGLES,
                            // GL_TRIANGLE_STRIP_ADJACENCY, GL_TRIANGLES_ADJACENCY,
                            // GL_PATCHES
    GLenum index_type;      // UNSIGNED_BYTE, GL_UNSIGNED_SHORT, GL_UNSIGNED_INT
    GLsizei index_count;

public:
    Model(std::vector<GLfloat> vertices, int index_count, GLuint shader_program, GLenum mode = GL_TRIANGLES, GLenum type = GL_UNSIGNED_INT);
    Model(std::vector<GLfloat> vertices, std::vector<GLuint> indices, GLuint shader_program, GLenum mode = GL_TRIANGLES, GLenum type = GL_UNSIGNED_INT);
    Model(std::shared_ptr<Mesh> mesh, GLuint shader_program); // TODO: accept model that knows about vertex attributes (type, size, offsets) and textures, etc

    operator GLuint()
    {
        return vao;
    }
};
