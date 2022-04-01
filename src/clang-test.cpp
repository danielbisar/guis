
#include "window.hpp"

#include "include/core/SkColor.h"
#include "include/core/SkImageInfo.h"
#include "include/gpu/GrBackendSurface.h"
#include "include/gpu/GrTypes.h"
#include "include/gpu/gl/GrGLTypes.h"
#include <cstdlib>
#include <iostream>
#include <thread>
#include <chrono>

#include <GLFW/glfw3.h>

#include <include/gpu/gl/GrGLInterface.h>
#include <include/gpu/GrDirectContext.h>
#include <include/gpu/GrContextOptions.h>
#include <include/core/SkData.h>
#include <include/core/SkStream.h>
#include <include/core/SkCanvas.h>
#include <include/core/SkSurface.h>
#include <tools/gpu/GrContextFactory.h>

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

        while (!glfwWindowShouldClose(window.getBackendWindow()))
        {
            glfwWaitEvents();

            SkPaint paint;
            paint.setColor(SK_ColorYELLOW);

            canvas->drawPaint(paint);

            grContext->flush();
            glfwSwapBuffers(window.getBackendWindow());

            // glfwWaitEvents is an alternative
            // glfwPollEvents();
            //            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        cleanup_skia();
    }

    glfwTerminate();

    return 0;
}
