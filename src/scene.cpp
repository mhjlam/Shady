#include "scene.h"

#include <chrono>
#include <random>
#include <vector>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "model.h"
#include "shader.h"

Scene::Scene()
{
    time_elapsed = 0;
    time_delta = 0;
    time_prev = glfwGetTime();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    aspect_ratio = width / float(height);
}

void Scene::update(GLFWwindow* window)
{
    time_elapsed = glfwGetTime();
    time_delta = time_elapsed - time_prev;
    time_prev = time_elapsed;

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    aspect_ratio = width / float(height);
};

void Scene::render()
{
    glViewport(0, 0, width, height);
}


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

void Scene_Random_Color::update(GLFWwindow* window)
{
    Scene::update(window);

    if ((timer += time_delta) >= 1.0)
    {
        timer = 0;
        random_clear_color();
    }
}

void Scene_Random_Color::render()
{
    Scene::render();
    glClear(GL_COLOR_BUFFER_BIT);
}


Scene_Cursor_Color::Scene_Cursor_Color() : Scene()
{
    std::vector<GLfloat> vertices =
    {
        // top-left
        -1.0f,  1.0f, 0.0f, 1.0f,
         1.0f,  1.0f, 0.0f, 1.0f,
        -1.0f, -1.0f, 0.0f, 1.0f,

        // bottom-right
         1.0f,  1.0f, 0.0f, 1.0f,
         1.0f, -1.0f, 0.0f, 1.0f,
        -1.0f, -1.0f, 0.0f, 1.0f
    };

    shader = std::make_shared<Shader>("shaders/scene_cursor_color.vs.glsl", "shaders/scene_cursor_color.fs.glsl");
    model = std::make_shared<Model>(vertices, vertices.size() / 4, *shader);
}

void Scene_Cursor_Color::update(GLFWwindow* window)
{
    Scene::update(window);
    glfwGetCursorPos(window, &mouse_x, &mouse_y);
}

void Scene_Cursor_Color::render()
{
    Scene::render();

    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(*shader);
    glBindVertexArray(*model);

    glUniform2f(glGetUniformLocation(*shader, "mouse"), float(mouse_x), float(mouse_y));
    glUniform2f(glGetUniformLocation(*shader, "resolution"), float(width), float(height));

    glDrawArrays(model->topology, 0, model->index_count);

    glBindVertexArray(0);
    glUseProgram(0);
}


Scene_Quadrilateral::Scene_Quadrilateral() : Scene()
{
    scale = 0;

    std::vector<GLfloat> vertices =
    {
        //position    //color           //texcoord
        -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // top-left
         0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // top-right
         0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // bottom-right
        -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f  // Bottom-left
    };

    std::vector<GLuint> indices =
    {
        0, 1, 2,
        2, 3, 0
    };

    shader = std::make_shared<Shader>("shaders/scene_quadrilateral.vs.glsl", "shaders/scene_quadrilateral.fs.glsl");
    model = std::make_shared<Model>(vertices, indices, *shader);
}

void Scene_Quadrilateral::update(GLFWwindow* window)
{
    Scene::update(window);

    scale += time_delta * 0.2f;
}

void Scene_Quadrilateral::render()
{
    Scene::render();

    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(*shader);
    glBindVertexArray(*model);

    glm::mat4 mat_model = glm::scale(glm::rotate(glm::mat4(1.0f), float(time_elapsed) * glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f)), glm::vec3(scale));
    //glm::mat4 mat_model = glm::rotate(glm::mat4(1.0f), float(time_elapsed) * glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    GLint uniform_model = glGetUniformLocation(*shader, "model");
    glUniformMatrix4fv(uniform_model, 1, GL_FALSE, glm::value_ptr(mat_model));

    glm::mat4 mat_view = glm::lookAt(glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    GLint uniform_view = glGetUniformLocation(*shader, "view");
    glUniformMatrix4fv(uniform_view, 1, GL_FALSE, glm::value_ptr(mat_view));

    glm::mat4 mat_projection = glm::perspective(glm::radians(45.0f), aspect_ratio, 0.1f, 10.0f);
    GLint uniform_projection = glGetUniformLocation(*shader, "projection");
    glUniformMatrix4fv(uniform_projection, 1, GL_FALSE, glm::value_ptr(mat_projection));

    glDrawElements(model->topology, model->index_count, model->index_type, 0);

    glBindVertexArray(0);
    glUseProgram(0);
}
