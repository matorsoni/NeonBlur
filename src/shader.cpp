#include "shader.hpp"

#include <fstream>
#include <iostream>

static std::string load_text_file(const std::string& filename)
{
    std::string text, line;
    std::ifstream file(filename);
    if (!file) {
        std::cout << "Unable to read file " << filename << "\n";
        return {};
    }

    while (getline(file, line)) {
        text.append(line + "\n");
    }

    //std::move(text);
    return text;
}

GLuint create_shader_program(const std::string& vert_file, const std::string& frag_file)
{
    // Load vertex shader source and compile it.
    std::string vert_shader = load_text_file(vert_file);
    const char* vert_shader_src = vert_shader.c_str();
    GLuint vert_shader_id = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vert_shader_id, 1, &vert_shader_src, NULL);
    glCompileShader(vert_shader_id);

    // Load fragment shader source and compile it.
    std::string frag_shader = load_text_file(frag_file);
    const char* frag_shader_src = frag_shader.c_str();
    unsigned int frag_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(frag_shader_id, 1, &frag_shader_src, NULL);
    glCompileShader(frag_shader_id);

    // Check if shaders compiled correctly.
    {
        int success;
        char info_log[512];

        glGetShaderiv(vert_shader_id, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(vert_shader_id, 512, NULL, info_log);
            std::cout << "Vertex shader compilation failed: \n" << info_log << "\n";
        }

        glGetShaderiv(frag_shader_id, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(frag_shader_id, 512, NULL, info_log);
            std::cout << "Fragment shader compilation failed: \n" << info_log << "\n";
        }
    }

    // Link shader program.
    GLuint program = glCreateProgram();
    glAttachShader(program, vert_shader_id);
    glAttachShader(program, frag_shader_id);
    glLinkProgram(program);

    // Check if linking went well.
    {
        int success;
        char info_log[512];
        glGetProgramiv(program, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(program, 512, NULL, info_log);
            std::cout << "Shader program linking failed: \n" << info_log << "\n";
        }
    }

    // Delete intermediate shader objects.
    glDeleteShader(vert_shader_id);
    glDeleteShader(frag_shader_id);

    return program;
}
