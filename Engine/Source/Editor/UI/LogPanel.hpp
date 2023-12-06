#pragma once

namespace RendererDemo {

class LogPanel {
public:
    LogPanel() = default;
    virtual ~LogPanel() = default;

    void OnImGuiRender();
};

} // namespace RendererDemo
