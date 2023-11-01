#pragma once

namespace RendererDemo {

class RendererSystem {
public:
    ~RendererSystem() = default;

    void Initialize();
    void Clear();

	void Tick(float ts);

private:
};

} // namespace RendererDemo
