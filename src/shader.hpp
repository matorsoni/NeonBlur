#include <string>

#include "glad/gl.h"

GLuint create_shader_program(const std::string& vert_file,
                             const std::string& frag_file);
