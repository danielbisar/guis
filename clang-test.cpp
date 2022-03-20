#include <iostream>
#include <thread>
#include <chrono>
#include <GLFW/glfw3.h>

void glfw_error_callback(int error, const char* description)
{
    std::cerr << "GLFW: " << error << " - " << description << std::endl;
}

int main()
{
    std::cout << "init glfw" << std::endl;

    if(!glfwInit())
    {
        std::cerr << "failed" << std::endl;
    }

    glfwSetErrorCallback(glfw_error_callback);

//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
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
        glViewport(0, 0, width, height);

        while(!glfwWindowShouldClose(window))
        {
            glClear(GL_COLOR_BUFFER_BIT);
            glClearColor(0, 1, 0, 0);

            glfwSwapBuffers(window);

            // glfwWaitEvents is an alternative
            glfwPollEvents();
//            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        glfwDestroyWindow(window);
    }
    else
    {
        std::cerr << "failed to create window" << std::endl;
    }

    glfwTerminate();

    return 0;
}
