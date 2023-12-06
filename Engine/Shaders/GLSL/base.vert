#version 450 core

layout(location = 0) in vec3 pos;
// layout(location = 1) in vec3 color;
// layout(location = 2) in vec2 texCoord;

uniform float u_time;

layout(location = 0) out vec4 o_color;

void main() {
    o_color = vec4(pos, 1.);                   // 直接输出颜色数据
    gl_Position = vec4(pos.x, pos.y, pos.z, 1.); // 直接输出位置数据
}
