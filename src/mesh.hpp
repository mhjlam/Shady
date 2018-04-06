#pragma once

#include <memory>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "vertex.hpp"

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

	GLenum topology;        // GL_POINTS, GL_LINE_STRIP, GL_LINE_LOOP, GL_LINES, GL_LINE_STRIP_ADJACENCY, GL_LINES_ADJACENCY,
                            // GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN, GL_TRIANGLES, GL_TRIANGLE_STRIP_ADJACENCY, GL_TRIANGLES_ADJACENCY, GL_PATCHES
    GLenum vertex_usage;    // GL_STREAM_DRAW, GL_STREAM_READ, GL_STREAM_COPY, GL_STATIC_DRAW, GL_STATIC_READ, GL_STATIC_COPY, GL_DYNAMIC_DRAW, GL_DYNAMIC_READ, GL_DYNAMIC_COPY

public:
    Mesh(const std::vector<Vertex>& vertices, 
         GLenum mode  = GL_TRIANGLES, 
         GLenum usage = GL_STATIC_DRAW);

    Mesh(const std::vector<Vertex>& vertices, 
         const std::vector<GLuint>& indices, 
         GLenum mode  = GL_TRIANGLES, 
         GLenum usage = GL_STATIC_DRAW);

	static std::shared_ptr<Mesh> load_obj();
	static std::shared_ptr<Mesh> load_fbx();
	static std::shared_ptr<Mesh> load_gltf();
};
