#pragma once

namespace RendererDemo {

enum class RHIBufferType {
    // Buffer Type
    VertexBuffer,
    IndexBuffer,
    UniformBuffer,

    Vertex = VertexBuffer,
    V = VertexBuffer,
    Index = IndexBuffer,
    I = IndexBuffer,
    ElementBuffer = IndexBuffer,
    Element = IndexBuffer,
    E = IndexBuffer,
    Uniform = UniformBuffer,
    U = UniformBuffer,
};

enum class RHIDataType {
    UnsignedIntChar, // GL_UNSIGNED_BYTE
    Boolean,         // GLboolean
    Char,            // GLchar
    Int,             // GLint
    UnsignedInt,     // GLuint
    Float,           // GLfloat
    Double,          // GLdouble
    String,          // GLstring
    Int8,            // GLbyte
    UnsignedInt8,    // GLubyte
    Int16,           // GLshort
    UnsignedInt16,   // GLushort

    // Additional name
    Bool = Boolean,
    UInt = UnsignedInt,
    UInt8 = UnsignedInt8,
    UInt16 = UnsignedInt16,
    UChar = UnsignedIntChar
};

enum class RHIElementType {
    Position,
    Normal,
    Color,
};

enum class RHITargetType {
    Boolean, // GLboolean
    Char,    // GLchar
    Int,     // GLint
    UInt,    // GLuint
    Float,   // GLfloat
    Double,  // GLdouble
    String,  // GLstring
    Int8,    // GLbyte
    UInt8,   // GLubyte
    Int16,   // GLshort
    UInt16,  // GLushort
    UChar,   // GL_UNSIGNED_BYTE
};

} // namespace RendererDemo
