#ifndef CONFIG_LOAD_H
#define CONFIG_LOAD_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <filesystem>

#include "entity.h"
#include "shader.h"
#include "model.h"
#include "camera.h"
#include "sprite.h"
#include "image.h"

class ConfigLoad
{
public:
    std::vector<Model*> loadModels();
    std::vector<Sprite*> loadSprites();
    std::vector<Shader*> loadShaders();
};

#endif