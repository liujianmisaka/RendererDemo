#include "Misaka/Core/Renderer.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace RendererDemo {

class OpenGLRendererAPI : public Renderer {
public:
    virtual ~OpenGLRendererAPI() override{};

    virtual void Init() override;

    virtual void Close() override;

    virtual void Render(RendererDemo::Scene* scene = nullptr) override;

    virtual void drawExample() override;

private:
    GLuint VBO, VAO;
    GLuint shaderProgram;

    // 顶点着色器代码
    const char* vertexShaderSource = R"(
        #version 330 core
        layout (location = 0) in vec3 aPos;
        void main() {
            gl_Position = vec4(aPos, 1.0);
        }
    )";

    // 片段着色器代码
    const char* fragmentShaderSource = R"(
        #version 330 core
        out vec4 FragColor;
        void main() {
            FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
        }
    )";
};
} // namespace RendererDemo
