#include "Runtime/Function/Framework/Component/Mesh/MeshComponent.hpp"
#include <assimp/postprocess.h>
#include <iostream>
#include "Runtime/Function/Framework/Component/Mesh/RawMesh.hpp"

namespace RendererDemo {

void MeshComponent::LoadModel(std::string path) {
    LoadMesh(path);
}

void MeshComponent::Tick(float ts){};

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
    RawVertexBuffer vertex_buffes;
    RawIndexBuffer index_buffers;

    for (uint32_t i = 0; i < mesh->mNumVertices; i++) {
        vertex_buffes.positions.emplace_back(mesh->mVertices[i].x);
        vertex_buffes.positions.emplace_back(mesh->mVertices[i].y);
        vertex_buffes.positions.emplace_back(mesh->mVertices[i].z);
        vertex_buffes.normals.emplace_back(mesh->mNormals[i].x);
        vertex_buffes.normals.emplace_back(mesh->mNormals[i].y);
        vertex_buffes.normals.emplace_back(mesh->mNormals[i].z);

        if (mesh->mTextureCoords[0]) {
            vertex_buffes.texcoords.emplace_back(mesh->mTextureCoords[0][i].x);
            vertex_buffes.texcoords.emplace_back(mesh->mTextureCoords[0][i].y);
        } else {
            vertex_buffes.texcoords.emplace_back(0.0f);
            vertex_buffes.texcoords.emplace_back(0.0f);
        }

        if (mesh->HasTangentsAndBitangents()) {
            vertex_buffes.tangents.emplace_back(mesh->mTangents[i].x);
            vertex_buffes.tangents.emplace_back(mesh->mTangents[i].y);
            vertex_buffes.tangents.emplace_back(mesh->mTangents[i].z);
        } else {
            vertex_buffes.tangents.emplace_back(0.0f);
            vertex_buffes.tangents.emplace_back(0.0f);
            vertex_buffes.tangents.emplace_back(0.0f);
        }

        if (mesh->HasTangentsAndBitangents()) {
            vertex_buffes.uvs.emplace_back(mesh->mBitangents[i].x);
            vertex_buffes.uvs.emplace_back(mesh->mBitangents[i].y);
            vertex_buffes.uvs.emplace_back(mesh->mBitangents[i].z);
        } else {
            vertex_buffes.uvs.emplace_back(0.0f);
            vertex_buffes.uvs.emplace_back(0.0f);
            vertex_buffes.uvs.emplace_back(0.0f);
        }

        vertex_buffes.vertex_count++;
    }

    for (uint32_t i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];

        for (uint32_t j = 0; j < face.mNumIndices; j++) {
            index_buffers.indices.emplace_back(face.mIndices[j]);
        }
        index_buffers.primitive_count++;
    }

    m_meshs_data.emplace_back(MeshData{vertex_buffes, index_buffers});
}

} // namespace RendererDemo
