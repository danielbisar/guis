#pragma once

#include <core/SkCanvas.h>

namespace guis
{
    class Button
    {
    private:
        int _x;
        int _y;
        int _width;
        int _height;

    public:
        void draw(SkCanvas &canvas);

        int getX();
        int getY();
        int getWidth();
        int getHeight();

        void setX(int x);
        void setY(int y);
        void setWidth(int width);
        void setHeight(int height);
    };
}
