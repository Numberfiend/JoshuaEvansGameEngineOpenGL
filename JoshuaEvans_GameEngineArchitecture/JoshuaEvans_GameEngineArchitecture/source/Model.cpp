#pragma once
#include "Model.h"

namespace GE {
	bool Model::loadFromFile(const char* filename) {
		std::vector<Vertex> loadedVertices;
		Assimp::Importer imp;
		const aiScene* pScene = imp.ReadFile(filename, aiProcessPreset_TargetRealtime_Quality | aiProcess_FlipUVs);
		if (!pScene) {
			return false;
		}

		for (int Meshidx = 0; Meshidx < pScene->mNumMeshes; Meshidx++) {
			const aiMesh* mesh = pScene->mMeshes[Meshidx];

			for (int faceIdx = 0; faceIdx < mesh->mNumFaces; faceIdx++) {
				const aiFace& face = mesh->mFaces[faceIdx];

				for (int vertIdx = 0; vertIdx < 3; vertIdx++) {
					const aiVector3D* pos = &mesh->mVertices[face.mIndices[vertIdx]];

					const aiVector3D uv = mesh->mTextureCoords[0][face.mIndices[vertIdx]];
					loadedVertices.push_back(Vertex(pos->x, pos->y, pos->z, uv.x, uv.y));

					
				}
			}
		}
		numVertices = loadedVertices.size();
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(Vertex), loadedVertices.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		return true;
	}
}