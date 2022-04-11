#include "control.hpp"
#include <core/SkPaint.h>
#include <core/SkColor.h>

namespace guis
{
    void Control::draw(SkCanvas &canvas) const
    {
        SkPaint paint;
        paint.setColor(SK_ColorBLUE);
        paint.setStyle(SkPaint::kFill_Style);

        SkRect rect;
        rect.setXYWH(_x, _y, _width, _height);

        canvas.drawRoundRect(rect, 2, 2, paint);
    }

    int Control::getX()
    {
        return _x;
    }

    int Control::getY()
    {
        return _y;
    }

    int Control::getWidth()
    {
        return _width;
    }

    int Control::getHeight()
    {
        return _height;
    }

    void Control::setX(int x)
    {
        _x = x;
    }

    void Control::setY(int y)
    {
        _y = y;
    }

    void Control::setWidth(int width)
    {
        _width = width;
    }

    void Control::setHeight(int height)
    {
        _height = height;
    }
}
