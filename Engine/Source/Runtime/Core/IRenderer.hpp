#pragma once

namespace RendererDemo {

class IRenderer {
public:
    virtual ~IRenderer() = 0;

    virtual void Initialize() = 0; // 渲染器的初始化
    virtual void Destroy() = 0;    // 渲染器的清理

    virtual void BeginFrame() = 0; // 开始渲染帧
    virtual void EndFrame() = 0;   // 结束渲染帧
};

} // namespace RendererDemo
