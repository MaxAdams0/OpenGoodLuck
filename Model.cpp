#include "Model.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Model::Model(const char* path)
{
	Load(path);
}

void Model::Draw(Shader& shader) {
	for (unsigned int i = 0; i < meshes.size(); i++) {
		meshes[i].Draw(shader);
	}
}

void Model::Load(std::string path)
{
	Assimp::Importer import;
	// aiProcess_Triangulate will convert any face with more than 3 points into a triangle (which OpenGL expects)
	// aiProcess_FlipUVs makes all texture flip on the y axis when required
	const aiScene * scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
		return;
	}
	directory = path.substr(0, path.find_last_of('/'));

	ProcessNode(scene->mRootNode, scene);
}

void Model::ProcessNode(aiNode* node, const aiScene* scene)
{
	// process all the node's meshes (if any)
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(ProcessMesh(mesh, scene));
	}
	// then do the same for each of its children
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		ProcessNode(node->mChildren[i], scene);
	}
}

Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<TextureStruct> textures;

	// Process a vertices of the Mesh
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex new_vert;
		// Assimp's file structure doesn't mesh well with glm, so we have to manually insert data
		glm::vec3 vecP; // Position vector
		vecP.x = mesh->mVertices[i].x; // mVertices is the vertex position array
		vecP.y = mesh->mVertices[i].y;
		vecP.z = mesh->mVertices[i].z;
		new_vert.pos = vecP;

		glm::vec3 vecN; // Normal vector
		vecN.x = mesh->mNormals[i].x;
		vecN.y = mesh->mNormals[i].y;
		vecN.z = mesh->mNormals[i].z;
		new_vert.norm = vecN;

		if (mesh->mTextureCoords[0]) { // if mesh contains tex coords 
			glm::vec2 vecT; // Texture Coordinate vector
			vecT.x = mesh->mTextureCoords[0][i].x;
			vecT.y = mesh->mTextureCoords[0][i].y;
			new_vert.texc = vecT;
		}
		else {
			new_vert.texc = glm::vec2(0.0f, 0.0f);
		}

		vertices.push_back(new_vert);
	}

	// Process indices of a Mesh
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i]; // Face # i of Mesh
		for (unsigned int j = 0; j < face.mNumIndices; j++) {
			// Add all (3) indices of Mesh. Should only ever be 3 bc of aiProcess_Triangulate
			indices.push_back(face.mIndices[j]); 
		}
	}

	// Process material (Textures) of a Mesh
	if (mesh->mMaterialIndex >= 0) // no idea why it is inclusive to 0
	{
		aiMaterial* mat = scene->mMaterials[mesh->mMaterialIndex];

		std::vector<TextureStruct> diffMaps = LoadMaterialTextures(mat, aiTextureType_DIFFUSE, "tex_diff");
		textures.insert(textures.end(), diffMaps.begin(), diffMaps.end());

		std::vector<TextureStruct> specMaps = LoadMaterialTextures(mat, aiTextureType_SPECULAR, "tex_spec");
		textures.insert(textures.end(), specMaps.begin(), specMaps.end());
	}

	return Mesh(vertices, indices, textures);
}

std::vector<TextureStruct> Model::LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
{
	std::vector<TextureStruct> textures;
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		bool skip = false;
		for (unsigned int j = 0; j < textures_loaded.size(); j++)
		{
			if (std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
			{
				textures.push_back(textures_loaded[j]);
				skip = true;
				break;
			}
		}
		if (!skip)
		{   // if texture hasn't been loaded already, load it
			TextureStruct texture;
			texture.id = TextureFromFile(str.C_Str(), directory);
			texture.type = typeName;
			texture.path = str.C_Str();
			textures.push_back(texture);
			textures_loaded.push_back(texture); // add to loaded textures
		}
	}
	return textures;
}

unsigned int Model::TextureFromFile(const char* path, const std::string& directory, bool gamma)
{
	std::string filename = std::string(path);
	filename = directory + '/' + filename;

	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "TextureStruct failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}