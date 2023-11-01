#include "Runtime/Function/Framework/Object/Object.hpp"
#include "Runtime/Function/Framework/Component/Component.hpp"

namespace RendererDemo {

void Object::Tick(float ts) {
    for (auto component : m_components) {
        component->Tick(ts);
    }
}

} // namespace RendererDemo
