#pragma once

#include "Misaka/Core/IRenderer.hpp"

namespace RendererDemo {

class IWorld {
public:
    virtual ~IWorld() = 0;

    virtual void Initialize() = 0;                  // 场景加载时的初始化
    virtual void Destroy() = 0;                     // 场景卸载时的清理

    virtual void OnUpdate(float deltaTime) = 0;     // 场景的更新逻辑
    virtual void OnRender(IRenderer* renderer) = 0; // 渲染整个world
};

} // namespace RendererDemo
