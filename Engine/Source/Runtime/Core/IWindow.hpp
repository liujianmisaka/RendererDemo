#pragma once

namespace RendererDemo {

class IWindow {
public:
    virtual ~IWindow() = 0;

    virtual void Create() = 0;  // 创建窗口
    virtual void Destroy() = 0; // 销毁窗口

    virtual bool ShouldClose() const = 0; // 窗口是否应该关闭
    virtual void SetEventCallback() = 0;  // 处理窗口事件
    virtual void OnUpdate() = 0;          // 处理窗口事件，交换缓冲区

    // 可以添加其他窗口相关的抽象函数
};

} // namespace RendererDemo
