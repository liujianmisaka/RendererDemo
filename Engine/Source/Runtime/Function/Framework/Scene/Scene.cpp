#include "Runtime/Function/Framework/Scene/Scene.hpp"
#include "Runtime/Function/Framework/Object/Object.hpp"

namespace RendererDemo {

void Scene::Tick(float ts) {
    for (auto object : m_objects) {
        object.second->Tick(ts);
    }
}

} // namespace RendererDemo
