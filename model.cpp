#include "model.h"

Model::Model(std::shared_ptr<Mesh> mesh, 
             std::shared_ptr<Shader> shader, 
             std::shared_ptr<Texture> texture) :
	mesh(mesh), shader(shader), texture(texture)
{
	
}
