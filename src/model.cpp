#include "model.hpp"

#include "mesh.hpp"
#include "shader.hpp"
//#include "texture.hpp"

Model::Model(std::shared_ptr<Mesh>& mesh, std::shared_ptr<Shader>& shader)
: mesh(mesh), shader(shader), texture(nullptr)
{
    vao = mesh->vao;
    topology = mesh->topology;
    index_count = (mesh->indices.size() > 0) ? mesh->indices.size() : mesh->vertices.size();
    index_type = GL_UNSIGNED_INT;
}

Model::Model(std::shared_ptr<Mesh>& mesh, std::shared_ptr<Shader>& shader, std::shared_ptr<Texture>& texture)
: mesh(mesh), shader(shader), texture(texture)
{
    vao = mesh->vao;
    topology = mesh->topology;
    index_count = (mesh->indices.size() > 0) ? mesh->indices.size() : mesh->vertices.size();
    index_type = GL_UNSIGNED_INT;
}

Model::Model(std::vector<Body>& bodies)
: bodies(bodies)
{
    
}

Model::Model(std::vector<Body>& bodies, std::shared_ptr<Shader>& shader)
: bodies(bodies), shader(shader)
{

}
