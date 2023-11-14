#include "Runtime/Function/Framework/Object/Object.hpp"
#include <memory>

namespace RendererDemo {

void Object::Tick(float ts) {
    for (std::shared_ptr<Component> component : m_components) {
        component->Tick(ts);
    }
}

} // namespace RendererDemo
