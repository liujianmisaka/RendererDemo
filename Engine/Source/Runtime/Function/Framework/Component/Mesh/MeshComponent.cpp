#include "Runtime/Function/Framework/Component/Mesh/MeshComponent.hpp"
#include <assimp/postprocess.h>
#include <cstdint>
#include <iostream>
#include "Runtime/Function/Framework/Component/Mesh/RawMesh.hpp"
#include "Runtime/Function/Framework/Component/Render/IndexDrawBufferComponent.hpp"
#include "Runtime/Function/Framework/Component/State/StateComponent.hpp"

namespace RendererDemo {

void MeshComponent::Tick(float ts) {
    auto state_component = ObjectGetComponent<StateComponent>();
    if (!ObjectHasComponent<IndexDrawBufferComponent>() && ObjectGetComponent<StateComponent>().IsRendereable()) {
        auto& draw_component = ObjectAddComponent<IndexDrawBufferComponent>();
        auto& mesh_component = ObjectGetComponent<MeshComponent>();
        draw_component.GenerateIndexDrawBuffer(mesh_component.MeshData());
    }
}

void MeshComponent::LoadModel(std::string path) { LoadMesh(path); }

void MeshComponent::LoadMesh(std::string path) {
    Assimp::Importer importer;

    // load FBX model
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cerr << "Failed to load model: " << importer.GetErrorString() << std::endl;
    }

    processNode(scene->mRootNode, scene);
}

void MeshComponent::processNode(aiNode* node, const aiScene* scene) {
    for (uint32_t i = 0; i < node->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        processMesh(mesh, scene);
    }

    for (uint32_t i = 0; i < node->mNumChildren; i++) {
        processNode(node->mChildren[i], scene);
    }
}

void MeshComponent::processMesh(aiMesh* mesh, const aiScene* scene) {
    RawVertexBuffer& vertex_buffes = m_mesh_data.vertex_buffer;
    RawIndexBuffer& index_buffers = m_mesh_data.index_buffer;
    MaterialTexture& material_texture = m_mesh_data.material_texture;

    uint32_t vertex_data_size = vertex_buffes.vertex_count;

    for (uint32_t i = 0; i < mesh->mNumVertices; i++) {
        vertex_buffes.positions.insert(vertex_buffes.positions.end(),
                                       {mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z});
        vertex_buffes.normals.insert(vertex_buffes.normals.end(),
                                     {mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z});

        if (mesh->mTextureCoords[0]) {
            vertex_buffes.uvs.insert(vertex_buffes.uvs.end(),
                                     {mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y});
        } else {
            vertex_buffes.uvs.insert(vertex_buffes.uvs.end(), {0.0f, 0.0f});
        }

        if (mesh->HasTangentsAndBitangents()) {
            vertex_buffes.tangents.insert(vertex_buffes.tangents.end(),
                                          {mesh->mTangents[i].x, mesh->mTangents[i].y, mesh->mTangents[i].z});
            vertex_buffes.bitangents.insert(vertex_buffes.bitangents.end(),
                                            {mesh->mBitangents[i].x, mesh->mBitangents[i].y, mesh->mBitangents[i].z});
        } else {
            vertex_buffes.tangents.insert(vertex_buffes.tangents.end(), {0.0f, 0.0f, 0.0f});
            vertex_buffes.bitangents.insert(vertex_buffes.bitangents.end(), {0.0f, 0.0f, 0.0f});
        }

        vertex_buffes.vertex_count++;
    }

    for (uint32_t i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];

        for (uint32_t j = 0; j < face.mNumIndices; j++) {
            index_buffers.indices.emplace_back(face.mIndices[j] + vertex_data_size);
        }
        index_buffers.primitive_count++;
    }

    if (mesh->mMaterialIndex >= 0) {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

        aiString texture_path;
        if (material->GetTexture(aiTextureType_DIFFUSE, 0, &texture_path) == AI_SUCCESS) {
            material_texture.base_color = texture_path.C_Str();
        }

        if (material->GetTexture(aiTextureType_NORMALS, 0, &texture_path) == AI_SUCCESS) {
            material_texture.normal = texture_path.C_Str();
        }

        if (material->GetTexture(aiTextureType_METALNESS, 0, &texture_path) == AI_SUCCESS) {
            material_texture.metallic_roughness = texture_path.C_Str();
        }
    }
}

} // namespace RendererDemo
