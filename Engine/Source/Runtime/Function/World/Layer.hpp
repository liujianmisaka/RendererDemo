#pragma once

#include <string>


namespace RendererDemo {
	class Layer {
	public:
		Layer();
        virtual ~Layer() = default;

		void OnAttach();
		void OnDetach();

		void OnUpdate();

		void OnRender();

	    const std::string GetClassName() { return m_ClassName; }

	private:
		std::string m_ClassName = "Layer";

		// entt::entt
	};
}
