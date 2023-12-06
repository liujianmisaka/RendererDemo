#pragma once

namespace RendererDemo {

class RHIBuffer {
public:
    RHIBuffer() = default;
    virtual ~RHIBuffer() = default;
};

class RHIBufferView {};
class RHICommandBuffer {};
class RHICommandPool {};
class RHIDescriptorPool {};
class RHIDescriptorSet {};
class RHIDescriptorSetLayout {};
class RHIDevice {};
class RHIDeviceMemory {};
class RHIEvent {};
class RHIFence {};

class RHIFramebuffer {
public:
    RHIFramebuffer() = default;
    virtual ~RHIFramebuffer() = default;
};

class RHIImage {
public:
    RHIImage() = default;
    virtual ~RHIImage() = default;
};

class RHIImageView {};
class RHIInstance {};
class RHIQueue {};
class RHIPhysicalDevice {};
class RHIPipeline {};
class RHIPipelineCache {};
class RHIPipelineLayout {};
class RHIRenderPass {};
class RHISampler {};
class RHISemaphore {};

class RHIShader {
public:
    RHIShader() = default;
    virtual ~RHIShader() = default;
};

class RHIUniformBuffer {
public:
    RHIUniformBuffer() = default;
    virtual ~RHIUniformBuffer() = default;
};

} // namespace RendererDemo
