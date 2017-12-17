#pragma once

#include <memory>

class Mesh;
class Shader;
class Texture;

class Model
{
friend class Renderer;

private:
	GLuint vertex_array; // vertex array object

	std::shared_ptr<Mesh> mesh;
	std::shared_ptr<Shader> shader;
	std::shared_ptr<Texture> texture;

public:
	Model(std::shared_ptr<Mesh> mesh, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture);
};
