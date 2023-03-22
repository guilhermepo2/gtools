#include "GLFW/glfw3.h"
#include <stdlib.h>
#include <stdio.h>

void error_callback(int error, const char* description) {
    fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main(void) {
    glfwSetErrorCallback(error_callback);
    if(!glfwInit()) {
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    GLFWwindow* window = glfwCreateWindow(640, 480, "glfwTest", nullptr, nullptr);

    if(window) {
        glfwSetKeyCallback(window, key_callback);
        glfwMakeContextCurrent(window);
        // gladLoadGL
        glfwSwapInterval(1);

        while(!glfwWindowShouldClose(window)) {
            // processing events
            glfwPollEvents();
            // swapping buffers
            glfwSwapBuffers(window);
        }
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}