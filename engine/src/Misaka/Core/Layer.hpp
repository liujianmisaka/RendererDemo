#pragma once

#include <string>

#include "Misaka/Event/Event.hpp"


namespace RendererDemo {
	class Layer {
	public:
		Layer();
        virtual ~Layer() = default;

		virtual void OnUpdate() {}
		virtual void Render() {}
		virtual void OnEvent(Event& event) {}

	    virtual const std::string GetClassName() { return m_ClassName; }

	private:
		std::string m_ClassName = "Layer";

	};
}
