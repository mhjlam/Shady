#pragma once

#include <memory>
#include "scene.h"

struct GLFWwindow;

class Scene_Manager
{
private:
    Scene_ID active_scene_id;
    std::shared_ptr<Scene> active_scene;

    void load_scene(Scene_ID id);

public:
    Scene_Manager();
    
    void frame(GLFWwindow* window);

    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    void cursor_pos_callback(GLFWwindow* window, double x, double y);
    void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
};
