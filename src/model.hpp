#pragma once

#include <tuple>
#include <vector>
#include <memory>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Mesh;
class Shader;
class Texture;

struct Body // model parts
{
    std::shared_ptr<Mesh> mesh;
    std::shared_ptr<Shader> shader;
    std::shared_ptr<Texture> texture;
};

class Model
{
friend class Renderer;

private:
    GLuint vao;

    std::vector<Body> bodies; // TODO: remove mesh, shader, texture pointers

    std::shared_ptr<Mesh> mesh;
    std::shared_ptr<Shader> shader;
    std::shared_ptr<Texture> texture;

public:
    GLenum topology;
    GLenum index_type;
    GLsizei index_count;

public:
    Model(std::shared_ptr<Mesh>& mesh, std::shared_ptr<Shader>& shader);
    Model(std::shared_ptr<Mesh>& mesh, std::shared_ptr<Shader>& shader, std::shared_ptr<Texture>& texture);

    Model(std::vector<Body>& bodies);
    Model(std::vector<Body>& bodies, std::shared_ptr<Shader>& shader); // one shader for all bodies

    operator GLuint() { return vao; }
};
