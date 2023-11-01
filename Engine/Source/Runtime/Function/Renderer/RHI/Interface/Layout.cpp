#include "runtime/function/renderer/rhi/interface/layout.hpp"

namespace RendererDemo {

RawVertexLayout&& RawVertexLayout::AddElementInfo(ElementInfo element_info) {
    // Calculate the offset of the new element
    if (!m_element_info_vector.empty()) {
        const ElementInfo& lastElement = m_element_info_vector.back();
        element_info.offset = lastElement.offset + lastElement.size * SizeofType(lastElement.type);
    }

    // Add the new element to the vector
    m_element_info_vector.push_back(element_info);

    return std::move(*this);
}

RawVertexLayout&& RawVertexLayout::SetVertexByteSize(uint32_t vertex_byte_size) {
    m_vertex_byte_size = vertex_byte_size;
    return std::move(*this);
}

std::vector<ElementInfo> RawVertexLayout::GetElementInfoVector() {
    return m_element_info_vector;
}

uint32_t RawVertexLayout::GetVertexByteSize() {
    return m_vertex_byte_size;
}

uint32_t RawVertexLayout::SizeofType(MisakaTargetType type) {
    switch (type) {
        case MisakaTargetType::Float: return sizeof(GLfloat);
        case MisakaTargetType::Int: return sizeof(GLint);
        case MisakaTargetType::UInt: return sizeof(GLuint);
        case MisakaTargetType::Boolean: return sizeof(GLboolean);
        case MisakaTargetType::Double: return sizeof(GLdouble);
        case MisakaTargetType::Int8: return sizeof(GLbyte);
        case MisakaTargetType::UInt8: return sizeof(GLubyte);
        case MisakaTargetType::Int16: return sizeof(GLshort);
        case MisakaTargetType::UInt16: return sizeof(GLushort);
        default: return 0;
    }
}

} // namespace RendererDemo
