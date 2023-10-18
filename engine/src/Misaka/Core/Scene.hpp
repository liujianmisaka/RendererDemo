#pragma once

#include "Misaka/Core/LayerStack.hpp"

namespace RendererDemo {

class Scene {
public:

	void Update();
	
private:
	RendererDemo::LayerStack m_LayerStack;
};

} // namespace RendererDemo
