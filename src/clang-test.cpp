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


void glfw_error_callback(int error, const char* description)
{
    std::cerr << "GLFW: " << error << " - " << description << std::endl;
}

GrDirectContext* grContext = nullptr;
SkSurface* skSurface = nullptr;

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
                    nullptr).release();

    if(skSurface == nullptr)
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

    if(!glfwInit())
    {
        std::cerr << "failed" << std::endl;
    }

    glfwSetErrorCallback(glfw_error_callback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//(uncomment to enable correct color spaces) glfwWindowHint(GLFW_SRGB_CAPABLE, GL_TRUE);
	glfwWindowHint(GLFW_STENCIL_BITS, 0);
	//glfwWindowHint(GLFW_ALPHA_BITS, 0);
	glfwWindowHint(GLFW_DEPTH_BITS, 0);

    GLFWwindow* window = glfwCreateWindow(640, 480, "GLFW Test", NULL, NULL);

    if(window)
    {
        // https://www.glfw.org/docs/latest/quick.html
        glfwMakeContextCurrent(window);
        // f.e. gladLoadGL(glfwGetProcAddress);
        
        // vsync?
        //glfwSwapInterval(1);
        
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        //glViewport(0, 0, width, height);

        initSkia(width, height);

        glfwSwapInterval(1);

        SkCanvas* canvas = skSurface->getCanvas();

        while(!glfwWindowShouldClose(window))
        {
            glfwWaitEvents();

            SkPaint paint;
            paint.setColor(SK_ColorYELLOW);

            canvas->drawPaint(paint);
            
            grContext->flush();

            glfwSwapBuffers(window);

            // glfwWaitEvents is an alternative
            //glfwPollEvents();
//            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        cleanup_skia();

        glfwDestroyWindow(window);
    }
    else
    {
        std::cerr << "failed to create window" << std::endl;
    }

    glfwTerminate();

    return 0;
}
