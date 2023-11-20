#version 450 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

uniform mat4 u_View;
uniform mat4 u_Projection;
uniform mat4 u_Model;

layout(location = 0) out vec4 o_color;

void main() {
    o_color = vec4(normal, 1.);
    vec4 position = vec4(position, 1.);
    // position = u_Projection * u_View * u_Model * position;
    gl_Position = vec4(position.x, position.y, position.z, 1.);
}
