#version 450 core

out vec4 FragColor;

layout(location = 0) in vec4 i_color;

void main() {
    vec4 color = i_color;

    FragColor = color;
}
