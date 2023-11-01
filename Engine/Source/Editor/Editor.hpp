#pragma once

namespace RendererDemo {

class MisakaEngine;

class MisakaEditor {
public:
    void Initialize(RendererDemo::MisakaEngine* runtime_engine);

    void Run();

    void Clear();

private:
    RendererDemo::MisakaEngine* m_runtime_engine = nullptr;
};

} // namespace RendererDemo
