#version 450 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec3 tangents;
layout(location = 3) in vec3 bitangents;
layout(location = 4) in vec2 uvs;

layout(std140, binding = 0) uniform MVP {
    mat4 model;
    mat4 view;
    mat4 projection;
}
mvp;

layout(location = 0) out vec4 o_color;

void main() {
    o_color = vec4(0.2, 0.3, 0.5, 1.);
    vec4 position = vec4(position, 1.);
    position = mvp.model * position;
    position = mvp.view * position;
    position = mvp.projection * position;
    gl_Position = vec4(position.x, position.y, position.z, 1.);
}
