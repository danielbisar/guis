#include "window.hpp"
#include "control.hpp"

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

#include <yaml-cpp/yaml.h>
#include <yamlconverter.hpp>

#include <simpleREPL.h>

using namespace std;

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

// TODO move into class, this is just a quick test
SkCanvas *gcanvas;
string line(string name)
{
    SkPaint paint;
    gcanvas->drawLine(0, 0, 100, 100, paint);
    return "Hi " + name + ".";
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
        SkCanvas &canvas = *pCanvas;

        YAML::Node n = YAML::LoadFile("../yamls/test.yaml");

        vector<guis::Control> controls;

        for (YAML::const_iterator it = n.begin(); it != n.end(); it++)
        {
            guis::Control control = (*it)["control"].as<guis::Control>();
            window.addControl(control);
        }

        bool shouldClose = false;
        // TODO move to class
        gcanvas = pCanvas;

        while (shouldClose || !glfwWindowShouldClose(window.getBackendWindow()))
        {
            glfwWaitEvents();
            // glfwPollEvents();

            shouldClose = interface(func(line, "line", "Draw a line."));

            window.drawContent(canvas);

            grContext->flush();
            glfwSwapBuffers(window.getBackendWindow());
        }

        cleanup_skia();
    }

    glfwTerminate();

    return 0;
}
