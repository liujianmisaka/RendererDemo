#pragma once

#include <string>

#include "Misaka/Event/Event.hpp"


namespace RendererDemo {
	class Layer {
	public:
		Layer(const std::string& name = "Layer");
        virtual ~Layer() = default;

		virtual void OnUpdate() {}
		virtual void Render() {}
		virtual void OnEvent(Event& event) {}

	    const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;

	};
}
