#pragma once

#include "Runtime/RuntimeContext.hpp"

namespace RendererDemo {

class MisakaEngine {
public:
    MisakaEngine() = default;
    ~MisakaEngine() = default;

    void StartEngine();
    void ShutdownEngine();

    bool Run();

    RuntimeContext& GetRuntimeContext() { return m_runtime_context; }

private:
    RuntimeContext m_runtime_context{};
};

} // namespace RendererDemo
