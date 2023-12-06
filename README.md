# dev log

[ 2023-12-02 ] Add panels and advance `DrawVec3Control` function.

[ 2023-12-01 ] Advance the editor ui panel and add yaml-cpp.

[ 2023-11-28 ] (1) Delete unless component now. (2) Update ECS framework.

[ 2023-11-27 ] Create imgui texture in function.

[ 2023-11-24 ] Add default editor camera in the scene and move it in the editor.

[ 2023-11-23 ] Now use editor context in editor and delete `g_runtime_context`.

[ 2023-11-20 ] Fix glsl bug, clear framebuffer before write and add a rotation controller in editor ui..

[ 2023-11-18 ] Add component in object and avoid #include loop.

[ 2023-11-15 ] (1) Clean up Renderer files. (2) Use entt to manage object and component. (3) Use imgui docking space in EditorUI.

[ 2023-11-14 ] Use imgui docking space in EditorUI.

[ 2023-11-13 ] Merge current work and think about the next plan. 

[ 2023-10-31 ] Add basic abstract RHI and OpenGL RHI.

[ 2023-10-29 ] Add a simple GLFW event delegater.

[ 2023-10-25 ] New engine framework.

[ 2023-10-10 ] 使用 GLFW 显示一个窗口.

# 命名规范


1. 文件命名

- C++头文件: `MyFile.hpp`
- C++源文件: `MyFile.cpp`

1. 类型(class/struct/enum/typedef/using)

- `class MyEngine;`

3. 变量

- 普通变量: `int table_name`
- 类成员变量: `m_table_name`
- 结构体成员变量: `table_name`

4. 常量

- `const kMaxPoolSize = 10;`

5. 函数命名

- `void MyFunction();`

6. 枚举值

```
enum MyEnum {
	None = 0,
	Windows,
	Linux
};
```

7. 宏

- `#define MY_DEBUG_FLAG`

