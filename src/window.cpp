#include "window.hpp"

#include <GLFW/glfw3.h>

namespace guiserver
{
    Window::Window()
        : _width(800), _height(600), _window(nullptr)
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        //(uncomment to enable correct color spaces) glfwWindowHint(GLFW_SRGB_CAPABLE, GL_TRUE);
        glfwWindowHint(GLFW_STENCIL_BITS, 0);
        // glfwWindowHint(GLFW_ALPHA_BITS, 0);
        glfwWindowHint(GLFW_DEPTH_BITS, 0);
    }

    Window::~Window()
    {
        if (_window == nullptr)
            return;

        glfwDestroyWindow(_window);
        _window = nullptr;
    }

    void Window::show()
    {
        if (_window != nullptr)
            return;

        _window = glfwCreateWindow(_width, _height, "GLFW Test", nullptr, nullptr);

        if (!_window)
            return;

        glfwMakeContextCurrent(_window);

        // https://www.glfw.org/docs/latest/quick.html
        glfwMakeContextCurrent(_window);
        // f.e. gladLoadGL(glfwGetProcAddress);

        // vsync?
        glfwSwapInterval(0);

        // int width, height;
        // glfwGetFramebufferSize(window, &width, &height);
        // //glViewport(0, 0, width, height);
    }
}
