#pragma once

#include <memory>

#include "scene.hpp"

struct GLFWwindow;

class Renderer
{
private: // fields
    GLFWwindow* m_window;

    Scene_ID m_active_scene_id;
    std::shared_ptr<Scene> m_active_scene;

    int m_buffer_width;
    int m_buffer_height;
    float m_aspect_ratio;

    double m_time_elapsed;
    double m_time_delta;
    double m_time_prev;

public: // accessors
    GLFWwindow* window() { return m_window; }

    const int buffer_width() { return m_buffer_width; }
    const int buffer_height() { return m_buffer_height; }
    const float aspect_ratio() { return m_aspect_ratio; }

    const double time_elapsed() { return m_time_elapsed; }
    const double time_delta() { return m_time_delta; }
    const double time_prev() { return m_time_prev; }

public: // functions
    Renderer(GLFWwindow*);

    void update();
    void render();

    void key_callback(GLFWwindow*, int key, int scancode, int action, int mods);
    void cursor_pos_callback(GLFWwindow*, double x, double y);
    void mouse_button_callback(GLFWwindow*, int button, int action, int mods);

private: // functions
    void switch_scene();
    void load_scene(Scene_ID id);
    void reset_scene();
};
