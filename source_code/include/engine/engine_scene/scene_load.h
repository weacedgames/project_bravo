#ifndef SCENE_LOAD_H
#define SCENE_LOAD_H

#include <string>
#include <fstream>
#include <filesystem>
#include <vector>

#include "entity.h"
#include "shader.h"
#include "model.h"
#include "camera.h"

class SceneLoad
{
private:
    std::string loadShaderVertexDir(std::string path_root_directory, std::string shaderDir);
    std::string loadShaderFragmentDir(std::string path_root_directory, std::string shaderDir);
    std::string loadModelDir(std::string path_root_directory, std::string modelDir);

public:
    std::vector<Shader*> loadShaders();
    std::vector<Model*> loadModels();
    std::vector<std::vector<std::string>> loadEntities();
    std::vector<Entity*> generateEntities(std::vector<std::vector<std::string>> files, std::vector<Shader*> loaded_shaders, std::vector<Model*> loaded_models, std::vector<Sprite*> loaded_sprites, std::vector<Geometry*> loaded_geometry, Camera* camera);
};

#endif