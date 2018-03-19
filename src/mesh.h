#pragma once

#include <memory>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Mesh
{
private:
	std::vector<GLfloat> vertices;
	std::vector<GLuint> indices;

public:
	Mesh();

	static std::shared_ptr<Mesh> load_obj();
	static std::shared_ptr<Mesh> load_fbx();
	static std::shared_ptr<Mesh> load_gltf();
};
