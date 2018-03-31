#include <string>
#include <memory>
#include <sstream>
#include <iostream>
#include <stdexcept>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "renderer.hpp"

int main(int argc, char* argv[])
{
    glfwSetErrorCallback([](int error, const char* description)
    {
        std::stringstream ss;
        ss << error << ": " << description << "." << std::endl;
        throw std::runtime_error(ss.str());
    });

    try
    {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);

        GLFWwindow* window = glfwCreateWindow(1280, 720, "shady", nullptr, nullptr);

        if (!window)
        {
            throw std::runtime_error("Window creation failed.");
        }

        glfwMakeContextCurrent(window);
        gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

        Renderer renderer(window);
        glfwSetWindowUserPointer(window, &renderer);

        auto key_callback = [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            Renderer* r = (Renderer*)(glfwGetWindowUserPointer(window));
            if (r) r->key_callback(window, key, scancode, action, mods);
        };

        auto cursor_pos_callback = [](GLFWwindow* window, double x, double y)
        {
            Renderer* r = (Renderer*)(glfwGetWindowUserPointer(window));
            if (r) r->cursor_pos_callback(window, x, y);
        };

        auto mouse_button_callback = [](GLFWwindow* window, int button, int action, int mods)
        {
            Renderer* r = (Renderer*)(glfwGetWindowUserPointer(window));
            if (r) r->mouse_button_callback(window, button, action, mods);
        };

        glfwSetKeyCallback(window, key_callback);
        glfwSetCursorPosCallback(window, cursor_pos_callback);
        glfwSetMouseButtonCallback(window, mouse_button_callback);

        glfwSwapInterval(1);

        while (!glfwWindowShouldClose(window))
        {
            glfwPollEvents();         
            renderer.update();
            renderer.render();
        }

        glfwDestroyWindow(window);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    glfwTerminate();
    return 0;
}
