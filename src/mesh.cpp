#include "mesh.hpp"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#include <fstream>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

Mesh::Mesh()
{
	vertices = std::vector<Vertex>();
	indices = std::vector<GLuint>();
}

Mesh::Mesh(const std::vector<Vertex>& vertices, GLenum mode, GLenum type)
{

}

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices, GLenum mode, GLenum type)
{

}

std::shared_ptr<Mesh> load_obj(const std::string& obj_file_path)
{
	if (!fs::exists(obj_file_path)) return nullptr;

	std::ifstream file(obj_file_path, std::ios::in);
	if (!file.is_open()) return nullptr;
}

std::shared_ptr<Mesh> load_fbx(const std::string& fbx_file_path)
{
	if (!fs::exists(fbx_file_path)) return nullptr;

	std::ifstream file(fbx_file_path, std::ios::in);
	if (!file.is_open()) return nullptr;
}

std::shared_ptr<Mesh> load_gltf(const std::string& gltf_file_path)
{
	if (!fs::exists(gltf_file_path)) return nullptr;

	std::ifstream file(gltf_file_path, std::ios::in);
	if (!file.is_open()) return nullptr;
}
