#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

int g_width = 1280, g_height = 720;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    g_width = width;
    g_height = height;
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
}

int main() {
    if (!glfwInit()) return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    GLFWwindow* window = glfwCreateWindow(g_width, g_height, "OpenGL Triangle Example", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        return -1;
    }

    glViewport(0, 0, g_width, g_height);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");

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
        FragColor = vec4(1.0, 0.5, 0.2, 1.0);
    }
)";

    // 编译顶点着色器
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    // 检查顶点着色器是否编译成功
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        return -1;
    }

    // 编译片段着色器
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    // 检查片段着色器是否编译成功
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        return -1;
    }

    // 创建着色器程序
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // 检查着色器程序是否链接成功
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        return -1;
    }

    // 删除着色器对象，它们已经链接到程序中不再需要
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // 顶点数据
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // 左下角
        0.5f,  -0.5f, 0.0f, // 右下角
        0.0f,  0.5f,  0.0f  // 顶部
    };

    // 顶点缓冲对象，顶点数组对象
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // 绑定顶点数组对象
    glBindVertexArray(VAO);

    // 绑定顶点缓冲对象
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 设置顶点属性指针
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // 解绑顶点数组对象
    glBindVertexArray(0);

    // 创建一个帧缓冲对象（FBO）和一个纹理
    GLuint fbo;
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    GLuint texture;
    glGenTextures(1, &texture);

    glBindTexture(GL_TEXTURE_2D, texture);

    // unsigned char data[] = {255, 0, 0, 255}; // 红色
    // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, g_width, g_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

    glBindTexture(GL_TEXTURE_2D, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // 渲染循环
    while (!glfwWindowShouldClose(window)) {
        // 输入处理
        processInput(window);

        // glClearColor(0.6f, 0.4f, 0.2f, 1.0f);
        // glClear(GL_COLOR_BUFFER_BIT);

        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		// glClearColor(0.6f, 0.4f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        // 开始 ImGui 帧
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // 创建一个 ImGui Viewport
        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
        ImGui::Begin("Viewport");
        // ImGui::Begin("Viewport", nullptr, ImGuiWindowFlags_NoTitleBar);
        ImGui::Image((void*)(intptr_t)texture, ImVec2(g_width, g_height), ImVec2(0, 1), ImVec2(1, 0));
        ImGui::End();

        // 结束 ImGui 帧
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // 交换缓冲并检查事件
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // 清理 ImGui
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    // 清理 OpenGL 对象
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    // glDeleteFramebuffers(1, &fbo);
    glDeleteTextures(1, &texture);
    glDeleteProgram(shaderProgram);

    // 终止 GLFW
    glfwTerminate();

    return 0;
}
