#include "mesh.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

#include <fstream>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

Mesh::Mesh()
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
