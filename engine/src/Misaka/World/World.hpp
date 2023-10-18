#pragma once

#include "Misaka/Core/IWorld.hpp"

namespace RendererDemo {

class World : IWorld {
public:
    virtual ~World() = default;

    virtual void Initialize(); // 场景加载时的初始化
    virtual void Destroy();    // 场景卸载时的清理

    virtual void OnUpdate(float deltaTime);     // 场景的更新逻辑
    virtual void OnRender(IRenderer* renderer); // 渲染整个world
};

} // namespace RendererDemo
