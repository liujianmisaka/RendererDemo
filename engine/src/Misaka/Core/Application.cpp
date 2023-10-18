#include "Misaka/Core/Application.hpp"
#include <GLFW/glfw3.h>
#include "Misaka/Utils/Timestep.hpp"

// #include "platform/OpenGL/OpenGLRendererAPI.hpp"

namespace RendererDemo {

void Application::Initialize() {
	m_Window->Create();
	m_MainWorld->Initialize();
	m_Renderer->Initialize();
}

void Application::Destroy() {
	m_Renderer->Destroy();
	m_MainWorld->Destroy();
	m_Window->Destroy();
}

void Application::Run() {
	float time = (float)glfwGetTime();
	Timestep ts = time - m_LastTime;
	m_LastTime = time;

    while (!m_Window->ShouldClose()) {
        m_MainWorld->OnUpdate(ts);

		m_Renderer->BeginFrame();
        m_MainWorld->OnRender(m_Renderer);
		m_Renderer->EndFrame();

        m_Window->OnUpdate();
    }
}

} // namespace RendererDemo
