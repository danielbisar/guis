#include <iostream>
#include <GLFW/glfw3.h>

int main()
{
    std::cout << "init glfw" << std::endl;

    if(!glfwInit())
    {
        std::cerr << "failed" << std::endl;
    }

    glfwTerminate();

    return 0;
}
