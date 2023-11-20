#pragma once

#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>

#include "Runtime/Function/Framework/Component/Component.hpp"
#include "Runtime/Function/Framework/Component/Mesh/RawMesh.hpp"

namespace RendererDemo {

class MeshComponent : public Component {
public:
    MeshComponent() = default;
    virtual ~MeshComponent() = default;

    void LoadModel(std::string path);

    const std::vector<MeshData>& MeshData() { return m_mesh_data; }

private:
    void LoadMesh(std::string path);
    void processNode(aiNode* node, const aiScene* scene);
    void processMesh(aiMesh* mesh, const aiScene* scene);

private:
    std::vector<RendererDemo::MeshData> m_mesh_data{};
};

} // namespace RendererDemo
