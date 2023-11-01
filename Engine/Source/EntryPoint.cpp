#include "Runtime/Engine.hpp"
#include "Editor/Editor.hpp"
#include <iostream>

enum class Type { 
	type1,
	type2
};

template <Type T, typename q>
void print() {
    // std::cout << "type1" << std::endl;
}

int main() {
    // RendererDemoTest::HandlerTest();

	print<Type::type1, int>();
	print<Type::type2, double>();

    RendererDemo::MisakaEngine* engine = new RendererDemo::MisakaEngine();

    engine->StartEngine();

    RendererDemo::MisakaEditor* editor = new RendererDemo::MisakaEditor();
    editor->Initialize(engine);
    editor->Run();
    editor->Clear();

    engine->ShutdownEngine();

    delete engine;
}
