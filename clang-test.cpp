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

    //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    GLFWwindow* window = glfwCreateWindow(640, 480, "GLFW Test", NULL, NULL);

    if(window)
    {
        // https://www.glfw.org/docs/latest/quick.html
        glfwMakeContextCurrent(window);
        // f.e. gladLoadGL(glfwGetProcAddress);
        
        while(!glfwWindowShouldClose(window))
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
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
