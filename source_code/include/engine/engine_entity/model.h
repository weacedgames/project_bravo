#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
#include <cmath>

#include <glad/glad.h> 
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "mesh.h"
#include "shader.h"



class Model
{
private:
    Assimp::Importer import;

    std::string modelPath;
    std::vector<Texture> textures_loaded;
    std::vector<Mesh> meshes;
    std::string directory;
    bool gammaCorrection;

    void loadModel(std::string const &path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false);
    std::vector<Texture> loadMaterialTextures(aiMaterial *mat,aiTextureType type, std::string typeName);

private:
    std::vector<Vertex> boundingBox;
    std::vector<unsigned int> boundingBoxIndices;

    float x_min;
    float x_max;
    float y_min;
    float y_max;
    float z_min;
    float z_max;

public:

    ////////////////////////////////////////////////////////////////////////////
    // START Animation
    ////////////////////////////////////////////////////////////////////////////
    aiAnimation* animation = nullptr;
    const aiScene* scene = nullptr;
    
    std::vector<int> boneIDs;
    std::vector<float> weights;
    
    std::map<std::string, int> boneMap;
    std::vector<glm::mat4> boneOffsets;
    ////////////////////////////////////////////////////////////////////////////
    // END Animation
    ////////////////////////////////////////////////////////////////////////////

public:
    int assetModelID;
    Model(std::string const &path, int setId);

    void create_boundingBox();
public:
    void draw(Shader &shader);
    void drawBoundingBox();
    std::string returnModelPath();
    std::vector<Vertex> returnBoundingBox();
};

#endif