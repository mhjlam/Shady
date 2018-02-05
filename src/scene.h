#pragma once

#include <memory>

class Model;
class Shader;
struct GLFWwindow;

class Scene
{
protected:
    int width = 1280;
    int height = 720;
    float aspect_ratio;

    double time_elapsed;
    double time_delta;
    double time_prev;

public:
    Scene();
    virtual ~Scene() = default;

    virtual void update(GLFWwindow* window);
    virtual void render();

    virtual void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {}
    virtual void cursor_pos_callback(GLFWwindow* window, double x, double y) {}
    virtual void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {}
};

class Scene_Random_Color : public Scene
{
private:
    double timer;

    void random_clear_color();

public:
    Scene_Random_Color();
    virtual void update(GLFWwindow* window) override;
    virtual void render() override;
};

class Scene_Cursor_Color : public Scene
{
private:
    double mouse_x;
    double mouse_y;

    std::shared_ptr<Model> model;
    std::shared_ptr<Shader> shader;

public:
    Scene_Cursor_Color();
    virtual void update(GLFWwindow* window) override;
    virtual void render() override;
};

class Scene_Quadrilateral : public Scene
{
private:
    float scale;

    std::shared_ptr<Model> model;
    std::shared_ptr<Shader> shader;

public:
    Scene_Quadrilateral();
    virtual void update(GLFWwindow* window) override;
    virtual void render() override;
};

enum Scene_ID
{
    SCENE_ID_NONE,
    SCENE_ID_RANDOM_COLOR,
    SCENE_ID_CURSOR_COLOR,
    SCENE_ID_QUADRILATERAL,
    SCENE_ID_COUNT
};
