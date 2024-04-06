#include <iostream>

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "glad/gl.h"

#include "shader.hpp"
#include "texture.hpp"

static void error_callback(int error, const char* description) {
    std::cerr << "GLFW Error: " << description << std::endl;
}

int main()
{
    // Setup GLFW + OpenGL 3.3 Core context ======================================================
    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) {
        std::cerr << "GLFW init failed!" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(640, 480, "NeonBlur v0.1", NULL, NULL);
    if (!window) {
        std::cerr << "GLFW windows creation failed!" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    gladLoadGL(glfwGetProcAddress);
    glClearColor(0.36, 0.0, 0.4, 1.0);
    // ===========================================================================================

    float quad[24] = {
        -0.5f, 0.5f, 0.0f, 0.0f,   -0.5f, -0.5f, 0.0f, 1.0f,   0.5f, -0.5f, 1.0f, 1.0f,
         0.5f, 0.5f, 1.0f, 0.0f,   -0.5f,  0.5f, 0.0f, 0.0f,   0.5f, -0.5f, 1.0f, 1.0f
    };

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quad), quad, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));


    GLuint shader = create_shader_program(
        "../src/shader/quad.vert",
        "../src/shader/quad.frag"
    );

    GLuint tex = read_texture("../nhe.png");

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, tex);
        glUseProgram(shader);
        glBindVertexArray(vao);

        glDrawArrays(GL_TRIANGLES, 0, 6);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}
