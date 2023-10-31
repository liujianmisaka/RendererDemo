#include "Runtime/Function/Renderer/RHI/OpenGL/OpenGLRHI.hpp"
#include <iostream>
#include "Runtime/Function/Renderer/RHI/Interface/Shader.hpp"
#include "Runtime/Function/Renderer/RHI/OpenGL/OpenGL_Resource.hpp"
#include "Runtime/Function/Renderer/System/WindowSystem.hpp"

namespace RendererDemo {

void OpenGLRHI::Initialize(RHIInitInfo rhi_init_info) {
    m_window = rhi_init_info.window_system->GetNativeWindow();

    // 初始化 glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize glad" << std::endl;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glDisable(GL_CULL_FACE);
}

void OpenGLRHI::CreateBuffer(BufferInfo buffer_info) {
    OpenGLBuffer buffer = OpenGLAPI::CreateBuffer(buffer_info);
    switch (buffer_info.buffer_type) {
        case BufferType::VertexBuffer: {
            m_vertex_buffer = buffer;
            glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer.buffer_id);
            break;
        }
        case BufferType::IndexBuffer: {
            m_index_buffer = buffer;
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index_buffer.buffer_id);
            break;
        }
        case BufferType::UniformBuffer: {
            m_uniform_buffer = buffer;
            glBindBuffer(GL_UNIFORM_BUFFER, m_uniform_buffer.buffer_id);
            break;
        }
        default: {
            std::cerr << "Unhandled buffer type in switch statement" << std::endl;
            break;
        }
    }
}

void OpenGLRHI::CreateVertexLayout(RawVertexLayout raw_vertex_buffer_layout) {
    m_vertex_buffer_layout = OpenGLAPI::CreateVertexLayout(raw_vertex_buffer_layout);
}

void OpenGLRHI::CreateVertexArray() {
    glGenVertexArrays(1, &m_vertex_array);
	glBindVertexArray(m_vertex_array);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer.buffer_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index_buffer.buffer_id);
    for (auto& element_info : m_vertex_buffer_layout.element_info_vector) {
        glEnableVertexAttribArray(element_info.index);
        glVertexAttribPointer(element_info.index, element_info.size, element_info.type, element_info.normalized,
                              element_info.stride, (void*)element_info.offset);
    }
}

void OpenGLRHI::CreateShader(ShaderInfo shader_info) {
    RawShader raw_shader{shader_info};
    OpenGLShader shader = OpenGLAPI::CreateShader(raw_shader);
    m_shaders.emplace_back(shader);
}

void OpenGLRHI::CreateProgram() {
    m_program = OpenGLAPI::CreateProgram(m_shaders);
    glUseProgram(m_program.program_id);
}

void OpenGLRHI::Tick() {
    // 清空颜色缓冲
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(m_program.program_id);
    glBindVertexArray(m_vertex_array);

    // 绘制三角形
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void OpenGLRHI::DrawExample() {
    // // 顶点数据
    // float vertices[] = {
    //     -0.5f, -0.5f, 0.0f, // 左下角
    //     0.5f,  -0.5f, 0.0f, // 右下角
    //     0.0f,  0.5f,  0.0f, // 中上
    //     0.0f,  -0.5f, 0.0f  // 中下
    // };

    // // 索引数据
    // unsigned int indices[] = {
    //     0, 1, 2, // 第一个三角形
    //     1, 3, 2  // 第二个三角形
    // };

    // 顶点着色器源代码
    const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
)";

    // 片段着色器源代码
    const char* fragmentShaderSource = R"(
#version 330 core
out vec4 FragColor;

void main()
{
    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}
)";

    // 创建并编译顶点着色器
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // 创建并编译片段着色器
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // 创建程序对象
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    m_program.program_id = shaderProgram;

    // 删除着色器
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // 创建顶点数组对象、顶点缓冲对象和索引缓冲对象
    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    // glGenBuffers(1, &VBO);
    // glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    m_vertex_array = VAO;

    // glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer.buffer_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index_buffer.buffer_id);

    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

} // namespace RendererDemo
