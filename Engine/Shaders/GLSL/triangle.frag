#version 450 core

out vec4 FragColor; // 输出的颜色向量

layout(location = 0) in vec4 i_color; // 输入的颜色向量

void main() {
    // 使用顶点着色器传递过来的颜色
    vec4 color = i_color;

    // 输出最终的像素颜色
    FragColor = color;
}
