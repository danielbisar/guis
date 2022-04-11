#pragma once

#include <core/SkCanvas.h>

namespace guis
{
    class Control
    {
    private:
        int _x;
        int _y;
        int _width;
        int _height;
        bool _isMouseOver;

    public:
        void draw(SkCanvas &canvas) const;

        int getX();
        int getY();
        int getWidth();
        int getHeight();

        void setX(int x);
        void setY(int y);
        void setWidth(int width);
        void setHeight(int height);

        void setIsMouseOver(bool value);
    };
}
