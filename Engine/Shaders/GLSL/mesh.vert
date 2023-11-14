#version 450 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

layout(binding = 0) uniform MVP {
    mat4 model;
    mat4 view;
    mat4 proj;
}
u_mvp;

layout(location = 0) out vec4 o_color;

void main() {
    o_color = vec4(normal, 1.0);
    vec4 position = vec4(position, 1.0);
    // position = u_mvp.proj * u_mvp.view * u_mvp.model * position;
    gl_Position = vec4(position.x, position.y, position.z, 1.);
}
