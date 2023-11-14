#pragma once

#include "Runtime/Function/Renderer/RHI/RHI_Struct.hpp"

namespace RendererDemo {

const RHIVertexLayout KOpenGLMeshVertexLayout = {
    .attributes =
        {
            {
                // position
                .location = 0,
                .offset = 0,
                .count = 3,
                .data_type = RHIDataType::Float,
                .normalized = false,
            },
            {
                // normal
                .location = 1,
                .offset = 3 * sizeof(float),
                .count = 3,
                .data_type = RHIDataType::Float,
                .normalized = false,
            },
        },
    .stride = 6 * sizeof(float),
};

} // namespace RendererDemo
