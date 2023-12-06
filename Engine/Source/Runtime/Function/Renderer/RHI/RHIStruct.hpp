#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <cstdint>

#include "Runtime/Function/Renderer/RHI/RHITypes.hpp"

namespace RendererDemo {

struct RHIBufferCreateInfo {
    const char* name;
    const void* data;          // 数据指针
    uint32_t byte_size;        // 数据大小（以字节为单位）
    RHIDataType data_type;     // 数据类型
    RHIBufferType buffer_type; // 缓冲区类型
};

struct RHIElementInfo {
    uint32_t count;        // 数据的个数
    uint32_t unit_size;    // 数据的大小（以字节为单位）
    RHIDataType data_type; // 数据类型
    bool normalized;       // 是否进行归一化
};

struct RHIVertexAttribute {
    uint32_t location;     // 在着色器中的位置, 在创建顶点布局时,依序从0开始分配
    uint64_t offset;       // 在顶点数据中的偏移, 在创建顶点布局时计算
    uint32_t count;        // 数据个数
    RHIDataType data_type; // 数据类型
    bool normalized;       // 是否进行归一化
};

struct RHIVertexLayout {
    std::vector<RHIVertexAttribute> attributes; // 顶点属性数组
    uint32_t stride;                            // 顶点数据的总大小（以字节为单位）
};

enum class RHIShaderType : uint32_t {
    KTriangle,
    KMesh,
};

struct RHIIndexDrawBuffer {
    GLenum draw_mode;      // GL_TRIANGLES, GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN, etc.
    uint32_t index_count;  // the number of indices
    GLenum index_type;     // GL_UNSIGNED_BYTE, GL_UNSIGNED_SHORT, GL_UNSIGNED_INT
    uint64_t index_offset; // the offset of the first index in the index buffer
    uint32_t vertex_array_id;
    RHIShaderType shader_type;
};

} // namespace RendererDemo
