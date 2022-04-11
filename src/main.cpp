#include "window.hpp"

#include <cstdlib>
#include <iostream>
#include <thread>
#include <chrono>

#include <GLFW/glfw3.h>

#include <core/SkCanvas.h>
#include <core/SkPaint.h>
#include <core/SkSurface.h>
#include <gpu/gl/GrGLInterface.h>
#include <gpu/GrDirectContext.h>

void glfw_error_callback(int error, const char *description)
{
    std::cerr << "GLFW: " << error << " - " << description << std::endl;
}

GrDirectContext *grContext = nullptr;
SkSurface *skSurface = nullptr;

void initSkia(int w, int h)
{
    GrContextOptions options;
    grContext = GrDirectContext::MakeGL(nullptr, options).release();

    GrGLFramebufferInfo fbInfo;
    fbInfo.fFBOID = 0;
    fbInfo.fFormat = GL_RGBA8;

    SkColorType colorType = kBGRA_8888_SkColorType;

    GrBackendRenderTarget grBackendRenderTarget(w, h, 0, 0, fbInfo);

    skSurface = SkSurface::MakeFromBackendRenderTarget(grContext, grBackendRenderTarget,
                                                       kTopLeft_GrSurfaceOrigin,
                                                       colorType,
                                                       nullptr,
                                                       nullptr)
                    .release();

    if (skSurface == nullptr)
        abort();
}

void cleanup_skia()
{
    delete skSurface;
    delete grContext;
}

int main()
{
    std::cout << "init glfw" << std::endl;

    if (!glfwInit())
    {
        std::cerr << "failed" << std::endl;
    }

    glfwSetErrorCallback(glfw_error_callback);

    {
        guiserver::Window window;
        window.show();

        initSkia(window.getWidth(), window.getHeight());

        SkCanvas *canvas = skSurface->getCanvas();
        float f = 10;

        while (!glfwWindowShouldClose(window.getBackendWindow()))
        {
            glfwWaitEvents();
            // glfwPollEvents();

            SkPaint paint;
            paint.setColor(SK_ColorYELLOW);

            canvas->drawPaint(paint);

            paint.setColor(SK_ColorBLUE);
            SkPoint p;
            p.set(f, 10);

            f += 1;

            if (f > window.getWidth())
                f = 0;

            canvas->drawCircle(p, 10, paint);

            grContext->flush();
            glfwSwapBuffers(window.getBackendWindow());
        }

        cleanup_skia();
    }

    glfwTerminate();

    return 0;
}
