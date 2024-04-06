#version 330 core

layout (location = 0) in vec2 pos;
layout (location = 1) in vec2 tex_uv;

out vec2 tex_coords;
void main()
{
    gl_Position = vec4(pos, 0.0, 1.0);
    tex_coords = tex_uv;
}
