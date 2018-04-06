#include "scene.hpp"

#include <chrono>
#include <random>
#include <vector>
#include <iostream>

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "mesh.hpp"
#include "model.hpp"
#include "shader.hpp"
#include "vertex.hpp"
#include "renderer.hpp"

Scene_Random_Color::Scene_Random_Color() : Scene()
{
    timer = 0;
    random_clear_color();
}

void Scene_Random_Color::random_clear_color()
{
    static std::mt19937 mt(time(0)); // mersenne twister generator engine seeded with time
    static std::uniform_real_distribution<float> distr(0.0f, 1.0f); // random distribution

    glClearColor(distr(mt), distr(mt), distr(mt), 1.0f);
}

void Scene_Random_Color::update(Renderer* renderer)
{
    if ((timer += renderer->time_delta()) >= 1.0)
    {
        timer = 0;
        random_clear_color();
    }
}

void Scene_Random_Color::render()
{
    glClear(GL_COLOR_BUFFER_BIT);
}


Scene_Cursor_Color::Scene_Cursor_Color() : Scene()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    std::vector<Vertex> vertices =
    {
        Vertex_Position2({-1.0f,  1.0f}),
        Vertex_Position2({ 1.0f,  1.0f}),
        Vertex_Position2({-1.0f, -1.0f}),

        Vertex_Position2({ 1.0f,  1.0f}),
        Vertex_Position2({ 1.0f, -1.0f}),
        Vertex_Position2({-1.0f, -1.0f})
    };

    mesh = std::make_shared<Mesh>(vertices, GL_TRIANGLES, GL_STATIC_DRAW);
    shader = std::make_shared<Shader>("shaders/scene_cursor_color.vs.glsl", "shaders/scene_cursor_color.fs.glsl");
    model = std::make_shared<Model>(mesh, shader);

    uniloc_mouse = glGetUniformLocation(*shader, "mouse");
    uniloc_resolution = glGetUniformLocation(*shader, "resolution");
}

void Scene_Cursor_Color::update(Renderer* renderer)
{
    width = renderer->buffer_width();
    height = renderer->buffer_height();
    glfwGetCursorPos(renderer->window(), &mouse_x, &mouse_y);
}

void Scene_Cursor_Color::render()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(*shader);
    glBindVertexArray(*model);

    glUniform2f(uniloc_mouse, float(mouse_x), float(mouse_y));
    glUniform2f(uniloc_resolution, float(width), float(height));

    glDrawArrays(model->topology, 0, model->index_count);

    glBindVertexArray(0);
    glUseProgram(0);
}


Scene_Quadrilateral::Scene_Quadrilateral() : Scene()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    std::vector<Vertex> vertices =
    {
        Vertex_Position2_Texcoord_Color({-0.5f,  0.5f}, {0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}),
        Vertex_Position2_Texcoord_Color({ 0.5f,  0.5f}, {1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}),
        Vertex_Position2_Texcoord_Color({ 0.5f, -0.5f}, {1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}),
        Vertex_Position2_Texcoord_Color({-0.5f, -0.5f}, {0.0f, 1.0f}, {1.0f, 1.0f, 1.0f})
    };

    std::vector<GLuint> indices =
    {
        0, 1, 2,
        2, 3, 0
    };

    mesh = std::make_shared<Mesh>(vertices, indices, GL_TRIANGLES, GL_STATIC_DRAW);
    shader = std::make_shared<Shader>("shaders/scene_quadrilateral.vs.glsl", "shaders/scene_quadrilateral.fs.glsl");
    model = std::make_shared<Model>(mesh, shader);

    uniloc_model = glGetUniformLocation(*shader, "model");
    uniloc_view = glGetUniformLocation(*shader, "view");
    uniloc_projection = glGetUniformLocation(*shader, "projection");
}

void Scene_Quadrilateral::update(Renderer* renderer)
{
    scale += renderer->time_delta() * 0.2f;
    angle += renderer->time_delta() * 0.5f * glm::radians(180.0f);
    aspect_ratio = renderer->aspect_ratio();
}

void Scene_Quadrilateral::render()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(*shader);
    glBindVertexArray(*model);

    glm::mat4 mat_model = glm::scale(glm::rotate(glm::mat4(1.0f), -angle, glm::vec3(0.0f, 0.0f, 1.0f)), glm::vec3(scale));
    glUniformMatrix4fv(uniloc_model, 1, GL_FALSE, glm::value_ptr(mat_model));

    glm::mat4 mat_view = glm::lookAt(glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glUniformMatrix4fv(uniloc_view, 1, GL_FALSE, glm::value_ptr(mat_view));

    glm::mat4 mat_projection = glm::perspective(glm::radians(45.0f), aspect_ratio, 0.1f, 10.0f);
    glUniformMatrix4fv(uniloc_projection, 1, GL_FALSE, glm::value_ptr(mat_projection));

    glDrawElements(model->topology, model->index_count, model->index_type, 0);

    glBindVertexArray(0);
    glUseProgram(0);
}

void Scene_Quadrilateral::reset()
{
    scale = 0;
    angle = 0;
}
