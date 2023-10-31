#pragma once

#include <vector>
#include <glm/glm.hpp>

namespace RendererDemo {

class MisakaEngine;

class MisakaEditor {
public:
    void Initialize(RendererDemo::MisakaEngine* runtime_engine);

    void Run();

    void Clear();

private:
    void Process();

private:
    RendererDemo::MisakaEngine* m_runtime_engine = nullptr;

    // // 顶点数据
    // std::vector<float> vertices = {
    //     0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // 右上角
    //     0.5f,  -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // 右下角
    //     -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // 左下角
    //     -0.5f, 0.5f,  0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f  // 左上角
    // };

    // 顶点数据
    std::vector<float> vertices = {
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // 左下角
        0.5f,  -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // 右下角
        0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f, // 右上角
        -0.5f, 0.5f,  0.0f, 1.0f, 1.0f, 1.0f, // 左上角
    };

    // 索引数据
    std::vector<unsigned int> indices = {
        0, 1, 3, // 第一个三角形
        0, 1, 2  // 第二个三角形
    };
};

} // namespace RendererDemo
