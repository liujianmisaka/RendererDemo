#include "Misaka/Core/LayerStack.hpp"

namespace RendererDemo {

LayerStack::~LayerStack() {
    for (Layer* layer : m_Layers) {
        layer->OnDetach();
        delete layer;
    }
}

void LayerStack::OnUpdate() {
    for (Layer* layer : m_Layers)
        layer->OnUpdate();
}

void LayerStack::OnEvent(Event& event) {
    for (Layer* layer : m_Layers)
        layer->OnEvent(event);
}

void LayerStack::PushLayer(Layer* layer) {
    m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
    m_LayerInsertIndex++;
}

void LayerStack::PushOverlay(Layer* overlay) {
    m_Layers.emplace_back(overlay);
}

void LayerStack::PopLayer(Layer* layer) {
    auto it = std::find(m_Layers.begin(), m_Layers.begin() + m_LayerInsertIndex, layer);
    if (it != m_Layers.begin() + m_LayerInsertIndex) {
        layer->OnDetach();
        m_Layers.erase(it);
        m_LayerInsertIndex--;
    }
}

void LayerStack::PopOverlay(Layer* overlay) {
    auto it = std::find(m_Layers.begin() + m_LayerInsertIndex, m_Layers.end(), overlay);
    if (it != m_Layers.end()) {
        overlay->OnDetach();
        m_Layers.erase(it);
    }
}

}