#pragma once

#include <memory>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "vertex.h"

class Model;
class Renderer;

class Mesh
{
friend class Model;
friend class Renderer;

private:
    GLuint vao;

	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

	GLenum topology;        // GL_POINTS,
                            // GL_LINE_STRIP, GL_LINE_LOOP, GL_LINES,
                            // GL_LINE_STRIP_ADJACENCY, GL_LINES_ADJACENCY,
                            // GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN, GL_TRIANGLES,
                            // GL_TRIANGLE_STRIP_ADJACENCY, GL_TRIANGLES_ADJACENCY,
                            // GL_PATCHES
    GLenum index_type;      // UNSIGNED_BYTE, GL_UNSIGNED_SHORT, GL_UNSIGNED_INT

public:
    Mesh();
    Mesh(const std::vector<Vertex>& vertices, GLenum mode = GL_TRIANGLES, GLenum type = GL_UNSIGNED_INT);
    Mesh(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices, GLenum mode = GL_TRIANGLES, GLenum type = GL_UNSIGNED_INT);

	static std::shared_ptr<Mesh> load_obj();
	static std::shared_ptr<Mesh> load_fbx();
	static std::shared_ptr<Mesh> load_gltf();
};
