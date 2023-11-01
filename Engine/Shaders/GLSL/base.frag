#version 450 core

out vec4 FragColor;                   // 输出的颜色向量

layout(location = 0) in vec4 i_color; // 输入的颜色向量

void main() {
    FragColor = i_color; // 输出橙色
}