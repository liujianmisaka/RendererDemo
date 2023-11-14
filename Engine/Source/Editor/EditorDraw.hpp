#pragma once

#include <memory>

namespace RendererDemo {

class RHI;

class EditorDraw {
public:
    EditorDraw() = default;
    ~EditorDraw() = default;

    void Initialize();
    void Clear();

	void Tick();

    void InitDraw();
    void RuntimeDraw();

private:
    std::shared_ptr<RHI> m_rhi;
};

} // namespace RendererDemo
