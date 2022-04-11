#include "window.hpp"
#include <functional>
#include <GLFW/glfw3.h>

namespace guiserver
{
    // only works as long as we just have one window...
    Window *window;

    void GLFWcursorPositionCallback(GLFWwindow *glfwWindow, double x, double y)
    {
        if (window)
            window->cursorPositionCallback(x, y);
    }

    Window::Window()
        : _width(800), _height(600), _window(nullptr), _controls()
    {
        window = this;
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

        glfwSetCursorPosCallback(_window, GLFWcursorPositionCallback);
    }

    void Window::addControl(guis::Control &control)
    {
        _controls.push_back(control);
    }

    void Window::drawContent(SkCanvas &canvas)
    {
        canvas.clear(SK_ColorWHITE);

        for (guis::Control &control : _controls)
        {
            control.draw(canvas);
        }
    }

    void Window::cursorPositionCallback(double x, double y)
    {
        for (guis::Control &control : _controls)
        {
            auto wx = control.getX();
            auto wrx = wx + control.getWidth();
            auto wy = control.getY();
            auto wry = wy + control.getHeight();

            control.setIsMouseOver(x >= wx && x <= wrx && y >= wy && y <= wry);
        }
    }
}
