#include "scene_manager.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

Scene_Manager::Scene_Manager()
{
    active_scene = nullptr;
	active_scene_id = SCENE_ID_NONE;
}

void Scene_Manager::load_scene(Scene_ID id)
{
    switch (id)
    {
        default:
        case SCENE_ID_NONE:
            active_scene = nullptr;
        break;

        case SCENE_ID_RANDOM_COLOR:
            active_scene = std::make_shared<Scene_Random_Color>();
        break;

        case SCENE_ID_CURSOR_COLOR:
            active_scene = std::make_shared<Scene_Cursor_Color>();
        break;

        case SCENE_ID_QUADRILATERAL:
            active_scene = std::make_shared<Scene_Quadrilateral>();
        break;
    }
}

void Scene_Manager::frame(GLFWwindow* window)
{
    if (active_scene)
    {
        active_scene->update(window);
        active_scene->render();
    }
    else
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }
}

void Scene_Manager::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS)
    {
        switch(key)
        {
            case GLFW_KEY_ESCAPE:
                glfwSetWindowShouldClose(window, GLFW_TRUE);
            break;

            case GLFW_KEY_SPACE:
                int id = active_scene_id;
                if (++id == int(SCENE_ID_COUNT)) id = 0;
                active_scene_id = (Scene_ID)id;
                Scene_Manager::load_scene(active_scene_id);
            break;
        }
    }

    if (active_scene)
    {
        active_scene->key_callback(window, key, scancode, action, mods);
    }
}

void Scene_Manager::cursor_pos_callback(GLFWwindow* window, double x, double y)
{
    if (active_scene)
    {
        active_scene->cursor_pos_callback(window, x, y);
    }
}

void Scene_Manager::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (active_scene)
    {
        active_scene->mouse_button_callback(window, button, action, mods);
    }
}
