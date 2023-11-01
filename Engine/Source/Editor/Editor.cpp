#include "Editor/Editor.hpp"
#include "Runtime/Engine.hpp"

namespace RendererDemo {

void MisakaEditor::Initialize(RendererDemo::MisakaEngine* runtime_engine) {
	m_runtime_engine = runtime_engine;
}

void MisakaEditor::Clear() {

}
void MisakaEditor::Run() {
	m_runtime_engine->Run();
}

}
