#include "button.hpp"
#include <core/SkPaint.h>
#include <core/SkColor.h>

namespace guis
{
    void Button::draw(SkCanvas &canvas)
    {
        SkPaint paint;
        paint.setColor(SK_ColorBLUE);
        paint.setStyle(SkPaint::kFill_Style);

        SkRect rect;
        rect.setXYWH(_x, _y, _width, _height);

        canvas.drawRoundRect(rect, 2, 2, paint);
    }

    int Button::getX()
    {
        return _x;
    }

    int Button::getY()
    {
        return _y;
    }

    int Button::getWidth()
    {
        return _width;
    }

    int Button::getHeight()
    {
        return _height;
    }

    void Button::setX(int x)
    {
        _x = x;
    }

    void Button::setY(int y)
    {
        _y = y;
    }

    void Button::setWidth(int width)
    {
        _width = width;
    }

    void Button::setHeight(int height)
    {
        _height = height;
    }
}
