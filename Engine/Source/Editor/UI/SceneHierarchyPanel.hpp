#pragma once

#include <memory>
#include "Runtime/Function/Framework/Object/Object.hpp"
#include "Runtime/Function/Framework/Scene/Scene.hpp"
namespace RendererDemo {

class SceneHierarchyPanel {
public:
    SceneHierarchyPanel() = default;
    explicit SceneHierarchyPanel(const std::shared_ptr<Scene>& context);
    virtual ~SceneHierarchyPanel() = default;

    void SetContext(const std::shared_ptr<Scene>& context);

    void OnImGuiRender();

private:
    void DrawComponentsofObject(Object object);

private:
    std::shared_ptr<Scene> m_scene = nullptr;
};
} // namespace RendererDemo
