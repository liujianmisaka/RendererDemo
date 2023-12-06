#pragma once

namespace RendererDemo {

class AssetPanel {
public:
    AssetPanel() = default;
    virtual ~AssetPanel() = default;

    void OnImGuiRender();
};

} // namespace RendererDemo
