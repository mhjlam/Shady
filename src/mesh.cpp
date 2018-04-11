#include "mesh.hpp"

#include <fstream>
#include <exception>
#include <experimental/filesystem>

#include <fmt/format.h>
#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

namespace fs = std::experimental::filesystem;

Mesh::Mesh(const std::vector<Vertex>& vertices, GLenum mode, GLenum usage)
: vertices(vertices), indices(std::vector<GLuint>()), topology(mode), vertex_usage(usage)
{
	// assemble vertex data
	std::vector<GLfloat> data = Vertex::assemble(vertices);

	// generate vertex array object
	glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

	// create vertex buffer
    GLuint vertex_buffer;
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(GLfloat), &data.front(), vertex_usage);

	// configure vertex attributes
	for (Vertex_Attrib attrib : vertices.front().attribs)
	{
		glEnableVertexAttribArray(attrib.index);
    	glVertexAttribPointer(attrib.index, attrib.size, attrib.type, attrib.normalized, attrib.stride, (void*)(attrib.offset * sizeof(GLfloat)));
	}

    glBindVertexArray(0);
}

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices, GLenum mode, GLenum usage)
: vertices(vertices), indices(indices), topology(mode), vertex_usage(usage)
{
	// assemble vertex data
	std::vector<GLfloat> data = Vertex::assemble(vertices);

	// generate vertex array object
	glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

	// create vertex buffer
    GLuint vertex_buffer;
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(GLfloat), &data.front(), vertex_usage);

	// create index buffer
    GLuint index_buffer;
    glGenBuffers(1, &index_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices.front(), GL_STATIC_DRAW);

	// configure vertex attributes
	for (Vertex_Attrib attrib : vertices.front().attribs)
	{
		glEnableVertexAttribArray(attrib.index);
    	glVertexAttribPointer(attrib.index, attrib.size, attrib.type, attrib.normalized, attrib.stride, (void*)(attrib.offset * sizeof(GLfloat)));
	}

    glBindVertexArray(0);	
}

std::shared_ptr<Mesh> load_obj(const std::string& obj_file_path)
{
	if (!fs::exists(obj_file_path))
	{
		throw std::runtime_error(fmt::format("Failed to load mesh file \"obj_file_path\"; path does not exist"));
	}

	std::ifstream file(obj_file_path, std::ios::in);
	if (!file.is_open())
	{
		throw std::runtime_error(fmt::format("Failed to read mesh file \"obj_file_path\"; permission denied or file is corrupt"));
	}


}

std::shared_ptr<Mesh> load_fbx(const std::string& fbx_file_path)
{
	if (!fs::exists(fbx_file_path))
	{
		throw std::runtime_error(fmt::format("Failed to load mesh file \"obj_file_path\"; path does not exist"));
	}

	std::ifstream file(fbx_file_path, std::ios::in);
	if (!file.is_open())
	{
		throw std::runtime_error(fmt::format("Failed to read mesh file \"obj_file_path\"; permission denied or file is corrupt"));
	}


}

std::shared_ptr<Mesh> load_gltf(const std::string& gltf_file_path)
{
	if (!fs::exists(gltf_file_path))
	{
		throw std::runtime_error(fmt::format("Failed to load mesh file \"obj_file_path\"; path does not exist"));
	}

	std::ifstream file(gltf_file_path, std::ios::in);
	if (!file.is_open())
	{
		throw std::runtime_error(fmt::format("Failed to read mesh file \"obj_file_path\"; permission denied or file is corrupt"));
	}

	
}
