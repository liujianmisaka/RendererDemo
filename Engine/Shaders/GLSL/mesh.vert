#version 450 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec3 tangents;
layout(location = 3) in vec3 bitangents;
layout(location = 4) in vec2 uvs;

uniform mat4 u_view;
uniform mat4 u_projection;
uniform mat4 u_model;

layout(location = 0) out vec4 o_color;

void main() {
    o_color = vec4(0.2, 0.3, 0.5, 1.);
    vec4 position = vec4(position, 1.);
    position = u_projection * u_view * u_model * position;
    gl_Position = vec4(position.x, position.y, position.z, 1.);
}
