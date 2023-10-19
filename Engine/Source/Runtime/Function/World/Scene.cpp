#include "Runtime/Function/World/Scene.hpp"


namespace RendererDemo {

void Scene::OnUpdate() {
	m_LayerStack.OnUpdate();
}

void Scene::OnRender() {
	m_LayerStack.OnRender();
}

}
