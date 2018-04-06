#pragma once

#include <memory>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Mesh;
class Model;
class Shader;
class Renderer;
struct GLFWwindow;

class Scene
{
public:
    Scene() = default;
    virtual ~Scene() = default;

    virtual void update(Renderer* renderer) = 0;
    virtual void render() = 0;
    virtual void reset() {};

    virtual void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {};
    virtual void cursor_pos_callback(GLFWwindow* window, double x, double y) {};
    virtual void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {};
};

class Scene_Random_Color : public Scene
{
private:
    double timer;
    void random_clear_color();

public:
    Scene_Random_Color();
    virtual void update(Renderer* renderer) override;
    virtual void render() override;
};

class Scene_Cursor_Color : public Scene
{
private:
    int width, height;
    double mouse_x, mouse_y;

    GLint uniloc_mouse;
    GLint uniloc_resolution;
    
    std::shared_ptr<Mesh> mesh;
    std::shared_ptr<Model> model;
    std::shared_ptr<Shader> shader;

public:
    Scene_Cursor_Color();
    virtual void update(Renderer* renderer) override;
    virtual void render() override;
};

class Scene_Quadrilateral : public Scene
{
private:
    float scale, angle;
    float aspect_ratio;

    GLint uniloc_model;
    GLint uniloc_view;
    GLint uniloc_projection;

    std::shared_ptr<Mesh> mesh;
    std::shared_ptr<Model> model;
    std::shared_ptr<Shader> shader;

public:
    Scene_Quadrilateral();
    virtual void update(Renderer* renderer) override;
    virtual void render() override;
    virtual void reset() override;
};

enum Scene_ID
{
    SCENE_ID_NONE,
    SCENE_ID_RANDOM_COLOR,
    SCENE_ID_CURSOR_COLOR,
    SCENE_ID_QUADRILATERAL,
    SCENE_ID_COUNT
};
