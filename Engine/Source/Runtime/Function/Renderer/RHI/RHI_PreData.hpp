#pragma once

#include <glm/glm.hpp>
#include <unordered_map>
#include "Runtime/Function/Renderer/RHI/RHI_Struct.hpp"
#include "Runtime/Function/Renderer/RHI/RHI_Types.hpp"

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
    {RHIElementType::Position, KPositionAttribute}, 
	{RHIElementType::Color, KColorAttribute}
};

struct MVP{
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;
};

} // namespace RendererDemo
