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
    virtual void Tick(float ts) override;

    const std::vector<MeshData>& GetMeshData() {
        return m_meshs_data;
    }

    void SetFlag(bool flag) {
        this->flag = flag;
    }

    bool Flag() {
        return flag;
    }

private:
    void LoadMesh(std::string path);
    void processNode(aiNode* node, const aiScene* scene);
    void processMesh(aiMesh* mesh, const aiScene* scene);

private:
    std::vector<MeshData> m_meshs_data{};
    bool flag = false;
};

} // namespace RendererDemo
