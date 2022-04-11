#pragma once

#include <GLFW/glfw3.h>
#include <vector>

#include <control.hpp>

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

        void cursorPositionCallback(double x, double y);

        void addControl(guis::Control &control);
        void drawContent(SkCanvas &canvas);

    private:
        int _width,
            _height;

        std::vector<guis::Control> _controls;

        GLFWwindow *_window;
    };
}
