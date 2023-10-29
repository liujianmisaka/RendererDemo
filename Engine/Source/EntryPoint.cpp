#include "Runtime/Engine.hpp"
#include "Editor/Editor.hpp"

int main() {

	// RendererDemoTest::HandlerTest();

    RendererDemo::MisakaEngine* engine = new  RendererDemo::MisakaEngine();

	engine->StartEngine();

	RendererDemo::MisakaEditor* editor = new RendererDemo::MisakaEditor();
	editor->Initialize(engine);
	editor->Run();
	editor->Clear();

	engine->ShutdownEngine();

	delete engine;

}
