#pragma once

#include <glm/glm.hpp>
#include "Editor/EditorContext.hpp"

namespace RendererDemo {

class MisakaEditor {
public:
    void Initialize(RendererDemo::MisakaEngine* runtime_engine);
    void Clear();

    void Run();

private:
    EditorContext m_editor_context;
};

} // namespace RendererDemo
