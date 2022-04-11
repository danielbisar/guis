#include "window.hpp"
#include "button.hpp"

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

    // even though we set the origin to kBottomLeft_GrSurfaceOrigin, this makes
    // sets the origin to the top left corner...
    skSurface = SkSurface::MakeFromBackendRenderTarget(grContext, grBackendRenderTarget,
                                                       kBottomLeft_GrSurfaceOrigin,
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

        SkCanvas *pCanvas = skSurface->getCanvas();
        float f = 10;

        guis::Button b;
        b.setX(10);
        b.setY(10);
        b.setWidth(100);
        b.setHeight(45);

        SkCanvas &canvas = *pCanvas;

        while (!glfwWindowShouldClose(window.getBackendWindow()))
        {
            glfwWaitEvents();
            // glfwPollEvents();

            pCanvas->clear(SK_ColorWHITE);

            b.draw(canvas);

            grContext->flush();
            glfwSwapBuffers(window.getBackendWindow());
        }

        cleanup_skia();
    }

    glfwTerminate();

    return 0;
}
