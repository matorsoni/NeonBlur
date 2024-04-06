#include "texture.hpp"

#include <iostream>

// Create stb_image implementation. Only define it once in this project.
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

GLuint read_texture(const std::string& filename)
{
    int width, height, channels;
    //stbi_set_flip_vertically_on_load(1);
    unsigned char* data = stbi_load(filename.c_str(), &width, &height, &channels, 0);
    if (data == NULL) {
        std::cout << "Could not load image data from file " << filename << std::endl;
        return 0;
    }

    // Determine the correct texture format.
    GLenum format;
    if (channels == 1)
        format = GL_RED;
    else if (channels == 2)
        format = GL_RG;
    else if (channels == 3)
        format = GL_RGB;
    else {
        assert(channels == 4);
        format = GL_RGBA;
    }

    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, format, GL_UNSIGNED_BYTE, data);

    // Set texture parameters. These parameters MUST BE SET, or else we get a black texture.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);

    glBindTexture(GL_TEXTURE_2D, 0);

    return tex;
}
