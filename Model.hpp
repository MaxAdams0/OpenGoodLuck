#ifndef MODEL_CLASS_H
#define MODEL_CLASS_H

#include <string>
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.hpp"
#include "Shader.hpp"

class Model
{
public:
	Model(const char* path);
	void Draw(Shader& shader);
private:
	// Model data
	std::vector<Mesh> meshes;
	std::string directory;
	std::vector<TextureStruct> textures_loaded;

	void Load(std::string path);
	void ProcessNode(aiNode* node, const aiScene* scene);
	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<TextureStruct> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
	unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma = false);
};


#endif