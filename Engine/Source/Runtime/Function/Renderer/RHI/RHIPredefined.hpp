#pragma once

#include <glm/glm.hpp>
#include <unordered_map>
#include "Runtime/Function/Renderer/RHI/RHIStruct.hpp"
#include "Runtime/Function/Renderer/RHI/RHITypes.hpp"

namespace RendererDemo {

constexpr RHIElementInfo KPositionAttribute = {
    .count = 3,
    .unit_size = sizeof(float),
    .data_type = RHIDataType::Float,
    .normalized = false,
};

constexpr RHIElementInfo KColorAttribute = {
    .count = 4,
    .unit_size = sizeof(float),
    .data_type = RHIDataType::Float,
    .normalized = false,
};

const std::unordered_map<RHIElementType, RHIElementInfo> KPredefinedVertexAttributeMap = {
    {RHIElementType::Position, KPositionAttribute}, {RHIElementType::Color, KColorAttribute}};

const RHIVertexLayout KSampleVertexLayout = {
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
            {
                // tangents
                .location = 2,
                .offset = 6 * sizeof(float),
                .count = 3,
                .data_type = RHIDataType::Float,
                .normalized = false,
            },
            {
                // bitangents
                .location = 3,
                .offset = 9 * sizeof(float),
                .count = 3,
                .data_type = RHIDataType::Float,
                .normalized = false,
            },
            {
                // uvs
                .location = 4,
                .offset = 12 * sizeof(float),
                .count = 2,
                .data_type = RHIDataType::Float,
                .normalized = false,
            },
        },
    .stride = 14 * sizeof(float),
};

struct MVP {
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;
};

} // namespace RendererDemo
