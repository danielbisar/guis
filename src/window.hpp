#pragma once

#include <GLFW/glfw3.h>

namespace guiserver
{
    class Window
    {
    public:
        Window();
        ~Window();

        // copy
        Window(const Window &other) = default;
        Window &operator=(const Window &rhs) = default;

        // move
        Window(Window &&other) = default;
        Window &operator=(Window &&rhs) = default;

        void show();

        int getWidth() { return _width; }
        int getHeight() { return _height; }

        GLFWwindow *getBackendWindow() { return _window; }

    private:
        int _width, _height;
        GLFWwindow *_window;
    };
}
