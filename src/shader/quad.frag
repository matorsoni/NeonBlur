#version 330 core

in vec2 tex_coords;

out vec4 frag_color;

uniform sampler2D tex;

void main()
{
    vec4 color = texture(tex, tex_coords);
    frag_color = vec4(color.xyz, 1.0);
}
