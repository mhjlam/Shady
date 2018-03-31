#include "renderer.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "constants.hpp"

Renderer::Renderer(GLFWwindow* glfwWindow)
{
    m_window = glfwWindow;

    m_active_scene = nullptr;
	m_active_scene_id = SCENE_ID_NONE;

    m_buffer_width = constants::window_width;
    m_buffer_height = constants::window_height;
    m_aspect_ratio = float(m_buffer_width) / float(m_buffer_height);

    m_time_elapsed = 0;
    m_time_delta = 0;
    m_time_prev = glfwGetTime();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void Renderer::update()
{
    m_time_elapsed = glfwGetTime();
    m_time_delta = m_time_elapsed - m_time_prev;
    m_time_prev = m_time_elapsed;

    int width, height;
    glfwGetFramebufferSize(m_window, &width, &height);

    m_buffer_width = constants::window_width;
    m_buffer_height = constants::window_height;
    m_aspect_ratio = float(m_buffer_width) / float(m_buffer_height);

    if (m_active_scene)
    {
        m_active_scene->update(this);
    }
}

void Renderer::render()
{
    if (m_active_scene)
    {
        m_active_scene->render();
    }
    else
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    glfwSwapBuffers(m_window);
}

void Renderer::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS)
    {
        switch(key)
        {
            case GLFW_KEY_ESCAPE:
                glfwSetWindowShouldClose(window, GLFW_TRUE);
            break;

            case GLFW_KEY_SPACE:
                Renderer::switch_scene();
            break;

            case GLFW_KEY_R:
                Renderer::reset_scene();
            break;
        }
    }

    if (m_active_scene)
    {
        m_active_scene->key_callback(window, key, scancode, action, mods);
    }
}

void Renderer::cursor_pos_callback(GLFWwindow* window, double x, double y)
{
    if (m_active_scene)
    {
        m_active_scene->cursor_pos_callback(window, x, y);
    }
}

void Renderer::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (m_active_scene)
    {
        m_active_scene->mouse_button_callback(window, button, action, mods);
    }
}

void Renderer::switch_scene()
{
    int id = m_active_scene_id;
    if (++id == int(SCENE_ID_COUNT)) id = 0;
    m_active_scene_id = (Scene_ID)id;
    Renderer::load_scene(m_active_scene_id);
}

void Renderer::load_scene(Scene_ID id)
{
    switch (id)
    {
        default:
        case SCENE_ID_NONE:
            m_active_scene = nullptr;
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        break;

        case SCENE_ID_RANDOM_COLOR:
            m_active_scene = std::make_shared<Scene_Random_Color>();
        break;

        case SCENE_ID_CURSOR_COLOR:
            m_active_scene = std::make_shared<Scene_Cursor_Color>();
        break;

        case SCENE_ID_QUADRILATERAL:
            m_active_scene = std::make_shared<Scene_Quadrilateral>();
        break;
    }
}

void Renderer::reset_scene()
{
    if (m_active_scene)
    {
        m_active_scene->reset();
    }
}
